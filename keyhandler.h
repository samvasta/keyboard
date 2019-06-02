// keyhandler.h

#ifndef _KEYHANDLER_h
#define _KEYHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "common.h"
#include "matrix.h"

/* key matrix position */
typedef struct {
	uint8_t row;
	uint8_t col;
} keypos_t;

/* key event */
typedef struct {
	keypos_t key;
	bool     pressed;
} keyevent_t;

#define COLUMNS {}
#define ROWS {}

void initMatrix();
void processMatrixState(matrix_row_t * matrix);

/* Key event container for recording */
typedef struct {
	keyevent_t  event;
} keyrecord_t;

void preProcessKey(keyevent_t e);
void processKey(keyevent_t e);
void press(uint16_t keyCode);
void release(uint16_t keyCode);
void pressRelease(uint16_t keyCode, bool isPressed);
void unpressAllOnLayer(uint8_t newLayer, uint8_t oldLayer);
uint16_t getKeyCode(uint8_t row, uint8_t col, uint8_t layer);

uint8_t getLayerStatus();

#endif

