// mousehandler.h

#ifndef _MOUSEHANDLER_h
#define _MOUSEHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define VSCROLL_SLOW 1
#define VSCROLL_FAST 3

#define HSCROLL_SLOW 3
#define HSCROLL_FAST 7

void toggleScrollSpeedH();
void toggleScrollSpeedV();

void scrollUp();
void scrollDown();
void scrollLeft();
void scrollRight();
#endif

