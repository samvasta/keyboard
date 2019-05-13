// 
// 
// 

#include "KeyboardLedIndicators.h"
#include "lcd.h"



void drawLedIndicators(int16_t x, int16_t y, uint8_t status) {
	//Serial.printf("Drawing layers\n");
	ILI9341_t3 *tft = getTft();
	tft->drawRect(x, y, LED_INDICATOR_WIDTH, LED_INDICATOR_HEIGHT, getForegroundCol());
	tft->fillRect(x + 1, y + 1, LED_INDICATOR_WIDTH - 2, LED_INDICATOR_HEIGHT - 2, getBackgroundCol());

	tft->setFont(QuattrocentoSans_10);
	tft->setCursor(x + 13, y + 4);
	tft->print("NUM");
	tft->setCursor(x + 13, y + 18);
	tft->print("CAPS");
	tft->setCursor(x + 13, y + 32);
	tft->print("SCROLL");

	//Num Lock
	if ((status & 0x01)) {
		tft->fillCircle(x + 6, y + 9, 3, getAccentMidCol());
		tft->drawCircle(x + 6, y + 9, 4, getForegroundCol());
	}
	//Caps Lock
	if ((status & 0x02)) {
		tft->fillCircle(x + 6, y + 23, 3, getAccentMidCol());
		tft->drawCircle(x + 6, y + 23, 4, getForegroundCol());
	}

	//Scroll Lock
	if ((status & 0x04)) {
		tft->fillCircle(x + 6, y + 37, 3, getAccentMidCol());
		tft->drawCircle(x + 6, y + 37, 4, getForegroundCol());
	}
}