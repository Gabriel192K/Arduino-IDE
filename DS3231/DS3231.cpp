#include "DS3231.h"

/*********************************************
Function: DS3231()
Purpose:  Copy I2C object
Input:    Pointer to I2C object
Return:   None
*********************************************/
DS3231::DS3231(TwoWire* wire)
{
	_wire = wire;
}

/*********************************************
Function: begin()
Purpose:  Begin I2C communication with DS3231
Input:    None
Return:   None
*********************************************/
void DS3231::begin(void)
{
	_wire->begin();
}

/*********************************************
Function: getTime()
Purpose:  Get values of hour, minute and second
Input:    Pointers to hour, minute and second
Return:   None
*********************************************/
void DS3231::getTime(uint8_t* hour, uint8_t* minute, uint8_t* second)
{
	_wire->beginTransmission(DS3231_ADDRESS);
	_wire->write(DS3231_SECOND_REGISTER);
	_wire->endTransmission();
	_wire->requestFrom(DS3231_ADDRESS, (uint8_t)3);
	*second = bcdToDec(_wire->read() & ~DS3231_STOP_CLOCK_BIT);
	*minute = bcdToDec(_wire->read());
	*hour   = bcdToDec(_wire->read());
	_wire->endTransmission();
}

/*********************************************
Function: getDate()
Purpose:  Get values of date, month and year
Input:    Pointers to date, month and year
Return:   None
*********************************************/
void DS3231::getDate(uint8_t* year, uint8_t* month, uint8_t* date)
{
	_wire->beginTransmission(DS3231_ADDRESS);
	_wire->write(DS3231_DATE_REGISTER);
	_wire->endTransmission();
	_wire->requestFrom(DS3231_ADDRESS, (uint8_t)3);
	*date  = bcdToDec(_wire->read());
	*month = bcdToDec(_wire->read());
	*year  = bcdToDec(_wire->read());
	_wire->endTransmission();
}

void DS3231::getDayOfWeek(char* dayOfWeek)
{
	const char days[7][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	uint8_t index;
	_wire->beginTransmission(DS3231_ADDRESS);
	_wire->write(DS3231_DAY_REGISTER);
	_wire->endTransmission();
	_wire->requestFrom(DS3231_ADDRESS, (uint8_t)1);
	memcpy(dayOfWeek, days[bcdToDec(_wire->read()) - (uint8_t)1], (uint8_t)10);
	_wire->endTransmission();
}

void DS3231::getInternalTemperature(int8_t* internalTemperature)
{
	_wire->beginTransmission(DS3231_ADDRESS);
	_wire->write(DS3231_TEMP_HIGH_REGISTER);
	_wire->endTransmission();
	_wire->requestFrom(DS3231_ADDRESS, (uint8_t)2);
	*internalTemperature = ((((short)_wire->read() << (uint8_t)8) | (short)_wire->read()) >> (uint8_t)6) >> 2;
	_wire->endTransmission();
}

/*********************************************
Function: bcdToDec()
Purpose:  Convert binary coded decimal to decimal
Input:    Value of bcd
Return:   Value of dec
*********************************************/
uint8_t DS3231::bcdToDec(uint8_t bcd)
{
	return (((bcd / (uint8_t)16) * (uint8_t)10) + (bcd % (uint8_t)16));
}

/*********************************************
Function: decToBcd()
Purpose:  Convert decimal to binary coded decimal
Input:    Value of dec
Return:   Value of bcd
*********************************************/
uint8_t DS3231::decToBcd(uint8_t dec)
{
	return (((dec / (uint8_t)10) * (uint8_t)16) + (dec % (uint8_t)10));
}