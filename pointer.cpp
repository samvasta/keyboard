// 
// 
// 

#include "pointer.h"
#include "usb_serial.h"
#include "Mouse.h"

#define MOUSE_MULT 5

uint16_t pointer_x_min;
uint16_t pointer_y_min;
uint16_t pointer_x_max;
uint16_t pointer_y_max;

uint16_t pointer_x_center;
uint16_t pointer_y_center;

uint16_t pointer_x_dead;
uint16_t pointer_y_dead;
uint16_t pointer_x_dead_percent;
uint16_t pointer_y_dead_percent;



void setup_pointer() {
	pointer_x_min = 140;
	pointer_y_min = 150;

	pointer_x_max = 810;
	pointer_y_max = 810;

	pointer_x_dead = 25;
	pointer_y_dead = 50;

	pointer_x_center = 485;
	pointer_y_center = 475;

	pointer_x_dead_percent = (pointer_x_dead) / (pointer_x_max - pointer_x_min);
	pointer_y_dead_percent = (pointer_y_dead) / (pointer_y_max - pointer_y_min);
}

uint64_t lastprint = 0;
void scan_pointer() {
	uint16_t x = analogRead(POINTER_HORIZ);
	uint16_t y = analogRead(POINTER_VERT);

	float x_percent = (float)(x - pointer_x_min) / (float)(pointer_x_max - pointer_x_min);
	float y_percent = (float)(y - pointer_y_min) / (float)(pointer_y_max - pointer_y_min);
	
	if (abs((int32_t)x - (int32_t)pointer_x_center) <= pointer_x_dead) {
		x_percent = 0.5;
	}
	else if (x_percent < 0) {
		x_percent = 0;
	}
	else if (x_percent > 1) {
		x_percent = 1;
	}
	else {
		if (x_percent < 0.5) {
			x_percent = x_percent * (0.5 / (0.5 - pointer_x_dead_percent));
		}
		else {
			x_percent = (x_percent-2*pointer_x_dead_percent) * (0.5 / (0.5 - pointer_x_dead_percent));
		}
	}

	if (abs((int32_t)y - (int32_t)pointer_y_center) <= pointer_y_dead) {
		y_percent = 0.5;
	}
	else if (y_percent < 0) {
		y_percent = 0;
	}
	else if (y_percent > 1) {
		y_percent = 1;
	}
	else {
		if (y_percent < 0.5) {
			y_percent = y_percent * (0.5 / (0.5 - pointer_y_dead_percent));
		}
		else {
			y_percent = (y_percent - 2 * pointer_y_dead_percent) * (0.5 / (0.5 - pointer_y_dead_percent));
		}
	}

	//center on 0
	x_percent -= 0.5f;
	y_percent -= 0.5f;

	float magnitude = sqrtf(x_percent*x_percent + y_percent * y_percent);

	//give it a nice curve

	float xNormalized = 0;
	float yNormalized = 0;
	if (magnitude > 0) {
		xNormalized = x_percent / magnitude;
		yNormalized = y_percent / magnitude;
	}

	//if (millis() - lastprint > 50) {
	//	Serial.printf("%01f\t%01f\n", x_percent * 100, y_percent * 100);
	//	//Serial.printf("%01f\t%01f\n", xNormalized * MOUSE_MULT, yNormalized * MOUSE_MULT);
	//	lastprint = millis();
	//}
	
	Mouse.move(x_percent * MOUSE_MULT, y_percent * MOUSE_MULT);
}

void set_pointer_x_min(uint16_t min) {
	pointer_x_min = min;
}

void set_pointer_y_min(uint16_t min) {
	pointer_y_min = min;
}

void set_pointer_x_max(uint16_t max) {
	pointer_x_max = max;
}

void set_pointer_y_max(uint16_t max) {
	pointer_y_max = max;
}

void set_pointer_x_center(uint16_t center){
	pointer_x_center = center;
}

void set_pointer_y_center(uint16_t center) {
	pointer_y_center = center;
}

void set_pointer_x_dead_zone(uint16_t dead) {
	pointer_x_dead = dead;
}
void set_pointer_y_dead_zone(uint16_t dead){
	pointer_y_dead = dead;
}