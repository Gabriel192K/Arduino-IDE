/*
PCF8574 Library
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

#ifndef PCF8574_H
#define PCF8574_H
#include <Wire.h>

#define PCF8574_LIB_VER "1.1"

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

typedef enum : uint8_t
{
	PCF8574_MODEL  = 0,
	PCF8574A_MODEL = 1
}PCF_MODEL;

class PCF8574
{
	public:
		PCF8574(TwoWire* wire, PCF_MODEL model, const uint8_t address);
		uint8_t begin(void);
		void    pinMode(const uint8_t pin, const uint8_t mode);
		void    digitalWrite(const uint8_t pin, const uint8_t state);
		uint8_t digitalRead(const uint8_t pin);
	private:
		TwoWire* _wire;
		uint8_t _address;
		uint8_t _dataOUTBuffer, _dataINBuffer, _modeBuffer;
		PCF_MODEL _model;
};

#endif
