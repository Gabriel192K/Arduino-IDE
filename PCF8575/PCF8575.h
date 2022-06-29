/*
PCF8575 Library
Created by: @Rotes Gabriel
Created at: 22 June 2022
Last Update 29 June 2022
Revision 1.0
- Implemented digitalWrite()
Revision 1.1
- Implemented digitalRead()
- Implemented partial pinMode()
- TODO: create conditions from write and read depending of pinMode()
*/

#ifndef PCF8575_H
#define PCF8575_H
#include <Wire.h>

const uint8_t LIB_VER[] = "1.1";

#ifndef ON
#define ON 1
#endif
#ifndef OFF
#define OFF 0
#endif
#ifndef IN
#define IN 1
#endif
#ifndef OUT
#define OUT 0
#endif

class PCF8575
{
	public:
		PCF8575(TwoWire* wire, const uint8_t address);
		uint8_t begin(void);
		void    pinMode(uint8_t pin, uint8_t mode);
		void    digitalWrite(uint8_t pin, uint8_t state);
		uint8_t digitalRead(uint8_t pin);
	protected:
		TwoWire* _wire;
		uint8_t _address;
		uint16_t _dataOUTBuffer, _dataINBuffer, _modeBuffer;
};


#endif
