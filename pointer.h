// pointer.h

#ifndef _POINTER_h
#define _POINTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define POINTER_HORIZ 9
#define POINTER_VERT 8

void setup_pointer();
void scan_pointer();

void set_pointer_x_min(uint16_t);
void set_pointer_y_min(uint16_t);
void set_pointer_x_max(uint16_t);
void set_pointer_y_max(uint16_t);

void set_pointer_x_center(uint16_t);
void set_pointer_y_center(uint16_t);

void set_pointer_x_dead_zone(uint16_t);
void set_pointer_y_dead_zone(uint16_t);

#endif

