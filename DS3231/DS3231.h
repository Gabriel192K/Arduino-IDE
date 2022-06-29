#ifndef DS3231_H
#define DS3231_H
#include <Wire.h>


// DS3231 address
#define DS3231_ADDRESS ((uint8_t)0x68)

// DS3231 registers
// ******************************************************************************************************************
#define DS3231_SECOND_REGISTER    ((uint8_t)0x00)
#define DS3231_MINUTE_REGISTER    ((uint8_t)0x01)
#define DS3231_HOUR_REGISTER      ((uint8_t)0x02)
#define DS3231_DAY_REGISTER       ((uint8_t)0x03)
#define DS3231_DATE_REGISTER      ((uint8_t)0x04)
#define DS3231_MONTH_REGISTER     ((uint8_t)0x05)
#define DS3231_YEAR_REGISTER      ((uint8_t)0x06)
#define DS3231_STATUS_REGISTER    ((uint8_t)0x0F)
#define DS3231_TEMP_HIGH_REGISTER ((uint8_t)0x11)
#define DS3231_TEMP_LOW_REGISTER  ((uint8_t)0x12)

// DS3231 register bits
// ******************************************************************************************************************
#define DS3231_STOP_CLOCK_BIT       ((uint8_t)0x80)
#define DS3231_TEMPERATURE_SIGN_BIT ((uint8_t)0x80)
#define DS3231_OSCILLATOR_STOP_BIT  ((uint8_t)0x80)

class DS3231
{
	public:
		DS3231(TwoWire* wire = &Wire);
		void begin(void);
		void getTime(uint8_t* hour, uint8_t* minute, uint8_t* second);
		void getDate(uint8_t* year, uint8_t* month, uint8_t* date);
		void getDayOfWeek(char* dayOfWeek);
		void getInternalTemperature(int8_t* internalTemperature);
	private:
		uint8_t bcdToDec(uint8_t bcd);
		uint8_t decToBcd(uint8_t dec);
		TwoWire* _wire;

};

#endif
