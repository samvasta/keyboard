#include "LayerIndicator.h"
#include "lcd.h"
#include "keyhandler.h"

uint8_t l;
void setLayerIndicator(uint8_t activeLayer) {
	l = activeLayer;
}
void drawLayerInfo(int16_t x, int16_t y) {
	//Serial.printf("Drawing layers\n");
	ILI9341_t3 *tft = getTft();
	uint8_t layers = l;// getLayerStatus();
	//tft->drawChar(x + 8, y, "0123456789ABCDEF"[layers & 0xf], getForegroundCol(), getBackgroundCol(), 24);
	tft->drawRect(x, y, INDICATOR_WIDTH, INDICATOR_HEIGHT, getForegroundCol());
	tft->fillRect(x+1, y+1, INDICATOR_WIDTH-2, INDICATOR_HEIGHT-2, getBackgroundCol());
	
	tft->setFont(Quattrocento_32_Bold);
	tft->setCursor(x+20, y+8);
	tft->print("0123456789ABCDEF"[layers & 0xf]);
	
	if (layers & 0x01) {
		tft->fillCircle(x + 8, y + 6, 3, getAccentMidCol());
		tft->drawCircle(x + 8, y + 6, 4, getForegroundCol());
	}
	
	if (layers & 0x02) {
		tft->fillCircle(x + 8, y + 16, 3, getAccentMidCol());
		tft->drawCircle(x + 8, y + 16, 4, getForegroundCol());
	}
	
	if (layers & 0x04) {
		tft->fillCircle(x + 8, y + 26, 3, getAccentMidCol());
		tft->drawCircle(x + 8, y + 26, 4, getForegroundCol());
	}
	
	if (layers & 0x08) {
		tft->fillCircle(x + 8, y + 36, 3, getAccentMidCol());
		tft->drawCircle(x + 8, y + 36, 4, getForegroundCol());
	}
}