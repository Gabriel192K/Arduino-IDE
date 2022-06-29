#include "PCF8574.h"

PCF8574::PCF8574(TwoWire* wire, PCF_MODEL model, const uint8_t address)
{
	_wire= wire;
	_model = model;
	_address = address;
}

uint8_t PCF8574::begin(void)
{
	_wire->begin();
	_wire->beginTransmission(_address);
	return (_wire->endTransmission() == 0);
}

void PCF8574::pinMode(const uint8_t pin, const uint8_t mode)
{
	if      (mode == IN)  _modeBuffer |= (1 << pin);  // If mode is INPUT set the bit inside the buffer
	else if (mode == OUT) _modeBuffer &= ~(1 << pin); // If mode is OUTPUT clear the bit inside the buffer
	_wire->beginTransmission(_address);               // Begin transmission
	_wire->write(_modeBuffer);                        // Write buffer
	_wire->endTransmission();                         // End transmission
}

void PCF8574::digitalWrite(const uint8_t pin, const uint8_t state)
{
	if      (state == ON)  _dataOUTBuffer |= (1 << pin);  // If state is ON set the bit inside the buffer
	else if (state == OFF) _dataOUTBuffer &= ~(1 << pin); // If state is OFF clear the bit inside the buffer
	_wire->beginTransmission(_address);                   // Begin transmission
	_wire->write(_dataOUTBuffer);                         // Write buffer
	_wire->endTransmission();                             // End transmission
}

uint8_t PCF8574::digitalRead(const uint8_t pin)
{
	_wire->beginTransmission(_address);       // Begin transmission
	_wire->endTransmission();                 // End transmission
	_wire->requestFrom(_address, (uint8_t)2); // Request 2 bytes
	_dataINBuffer = _wire->read();            // Read buffer
	return ((_dataINBuffer >> pin) & 1);      // Return state of pin inside the buffer
}