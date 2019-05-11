// encoders.h

#ifndef _ENCODERS_h
#define _ENCODERS_h


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define NUMBER_OF_ENCODERS 2
#define ENCODER_RESOLUTION 2
const uint8_t ENCODERS_LINE_A[] = { 0, 2 };
const uint8_t ENCODERS_LINE_B[] = { 1, 3 };

void setup_encoders();
void scan_encoders();

void onEncoder(uint8_t encNum, bool clockwise);

void on_encoder_l_pressed();
void on_encoder_r_pressed();

void on_encoder_l_released();
void on_encoder_r_released();

#endif

