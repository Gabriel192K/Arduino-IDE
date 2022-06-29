#include "PCF8575.h"

/*********************************************
Function: PCF8575()
Purpose:  Initialize PCF8575 class
Input:    Pointer to TwoWire class and address of PCF8575
Return:   None
*********************************************/
PCF8575::PCF8575(TwoWire* wire, const uint8_t address)
{
	_wire = wire;       // Copy wire pointer
	_address = address; // Copy address
}

/*********************************************
Function: begin()
Purpose:  Initialize PCF8575
Input:    None
Return:   Return 1 if succesfully connected with PCF8575
*********************************************/
uint8_t PCF8575::begin(void)
{
	_wire->begin();                         // Begin I2C bus
	_wire->beginTransmission(_address);     // Begin transmission
	return (_wire->endTransmission() == 0); // Return 1 if transmission was successful
}

/*********************************************
Function: pinMode()
Purpose:  Set pinMode
Input:    Pin and mode
Return:   None
*********************************************/
void PCF8575::pinMode(uint8_t pin, uint8_t mode)
{
	if      (mode == IN)  _modeBuffer |= (1 << pin);  // If mode is INPUT set the bit inside the buffer
	else if (mode == OUT) _modeBuffer &= ~(1 << pin); // If mode is OUTPUT clear the bit inside the buffer
	_wire->beginTransmission(_address);               // Begin transmission
	_wire->write(_modeBuffer & 0xFF);                 // Write LSB of the buffer
	_wire->write(_modeBuffer >> 8);                   // Write MSB of the buffer
	_wire->endTransmission();                         // End transmission
}

/*********************************************
Function: digitalWrite()
Purpose:  Write data to PCF8575
Input:    Pin and state
Return:   None
*********************************************/
void PCF8575::digitalWrite(uint8_t pin, uint8_t state)
{
	if      (state == ON)  _dataOUTBuffer |= (1 << pin);  // If state is ON set the bit inside the buffer
	else if (state == OFF) _dataOUTBuffer &= ~(1 << pin); // If state is OFF clear the bit inside the buffer
	_wire->beginTransmission(_address);                   // Begin transmission
	_wire->write(_dataOUTBuffer & 0xFF);                  // Write LSB of the buffer
	_wire->write(_dataOUTBuffer >> 8);                    // Write MSB of the buffer
	_wire->endTransmission();                             // End transmission
}

/*********************************************
Function: digitalRead()
Purpose:  Read data from PCF8575
Input:    Pin
Return:   State of the pin (either 0 or 1)
*********************************************/
uint8_t PCF8575::digitalRead(uint8_t pin)
{
	_wire->beginTransmission(_address);                   // Begin transmission
	_wire->endTransmission();                             // End transmission
	_wire->requestFrom(_address, (uint8_t)2);             // Request 2 bytes
	_dataINBuffer = _wire->read() | (_wire->read() << 8); // Read LSB and MSB
	return ((_dataINBuffer >> pin) & 1);                  // Return state of pin inside the buffer
}
