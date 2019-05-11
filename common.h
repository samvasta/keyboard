#ifndef _COMMON_h
#define _COMMON_h

#include "core_pins.h"


typedef signed char        int8_t;
typedef short              int16_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long long uint64_t;
#define bool boolean

#define wait_us(us) delayMicroseconds(us)

#define setPinOutput(pin) pinMode(pin, OUTPUT) 
#define setPinInput(pin) pinMode(pin, INPUT) 
#define setPinInputHigh(pin) pinMode(pin, INPUT_PULLUP) 

#define writePinLow(pin) digitalWrite(pin, LOW)
#define writePinHigh(pin) digitalWrite(pin, HIGH)

#define readPin(pin) digitalRead(pin)


#endif