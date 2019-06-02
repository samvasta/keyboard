// 
// 
// 

#include "mousehandler.h"


#include "Mouse.h"

bool isScrollFastH = false;
bool isScrollFastV = false;

uint8_t getScrollSpeedH() {
	if (isScrollFastH) {
		return HSCROLL_FAST;
	}
	return HSCROLL_SLOW;
}
uint8_t getScrollSpeedV() {
	if (isScrollFastV) {
		return VSCROLL_FAST;
	}
	return VSCROLL_SLOW;
}


void toggleScrollSpeedH() {
	isScrollFastH = !isScrollFastH;
}
void toggleScrollSpeedV() {
	isScrollFastV = !isScrollFastV;
}

void scrollUp() {
	Mouse.scroll(getScrollSpeedV(), 0);
}

void scrollDown() {
	Mouse.scroll(-getScrollSpeedV(), 0);
}

void scrollLeft() {
	Mouse.scroll(0, -getScrollSpeedH());

}

void scrollRight() {
	Mouse.scroll(0, getScrollSpeedH());

}