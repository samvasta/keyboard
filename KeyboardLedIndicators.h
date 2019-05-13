// KeyboardLedIndicators.h

#ifndef _KEYBOARDLEDINDICATORS_h
#define _KEYBOARDLEDINDICATORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "ILI9341_t3.h"
#include "fonts/font_QuattrocentoSans-Regular.h"

#define LED_INDICATOR_WIDTH 70
#define LED_INDICATOR_HEIGHT 46

void drawLedIndicators(int16_t x, int16_t y, uint8_t status);

#endif

