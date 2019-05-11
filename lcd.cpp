// 
// 
// 

#include "lcd.h"

#include "SPI.h"
#include "Wire.h"
#include "ILI9341_t3.h"
#include "fonts/font_Quattrocento-Bold.h"
#include "fonts/font_Quattrocento-Regular.h"
#include "fonts/font_QuattrocentoSans-Regular.h"
#include "EEPROM.h"
#include "persist.h"
#include "TimeUtil.h"
#include "LayerIndicator.h"


#define TFT_CS 10
#define TFT_DC  9
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CLK 13
#define TFT_RST 8

#define WELCOME_MESSAGE "hello sam."

static ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);


volatile uint16_t bg = ILI9341_WHITE;
volatile uint16_t fg = ILI9341_BLACK;
volatile uint16_t accentMid = 0x49A5;
volatile uint16_t accentLight = 0x8B6C;
volatile uint16_t accentDark = 0x2104;

volatile uint8_t accentIdx;
volatile bool themeMode;

volatile float brightness;
float old_brightness;

bool isRefreshing;
bool needsLayerRedraw;

ILI9341_t3 *getTft() {
	return &tft;
}

void setup_lcd() {
	needsLayerRedraw = true;

	isRefreshing = false;
	tft.begin();
	delay(5);
	tft.setRotation(1);

	brightness = EEPROM.read(ADDR_BRIGHTNESS);
	setDarkMode(EEPROM.read(ADDR_DARK_THEME));
	setAccentIdx(EEPROM.read(ADDR_ACCENT_IDX));

	old_brightness = brightness;
	
	drawStartScreen();
}

void displayWelcome() {
	tft.setFont(Quattrocento_24);
	tft.setTextColor(fg);
	drawTextCentered(WELCOME_MESSAGE, (tft.height() - 20) / 2);
	
	tft.drawFastHLine(70, (tft.height() / 2) + 16, 173, accentMid);
	tft.drawFastHLine(69, (tft.height() / 2) + 17, 174, accentMid);
	tft.drawFastHLine(68, (tft.height() / 2) + 18, 176, accentMid);
}

void drawStartScreen() {
	isRefreshing = true;
	tft.fillScreen(bg);

	displayWelcome();

	isRefreshing = false;
}

int16_t getCoord(float x);

uint32_t i = 0;
void update_lcd(uint64_t delta) {
	analogWrite(8, (uint8_t)brightness);

	if (isRefreshing) {
		//Skip this frame if we're drawing elsewhere
		return;
	}

	int16_t oldB = getCoord(old_brightness);
	int16_t newB = getCoord(brightness);

	tft.fillCircle(30+old_brightness, 200 -100 * (oldB / 255.0f), 3, accentDark);
	tft.fillCircle(30+brightness, 200 - 100*(newB/255.0f), 3, accentLight);

	tft.setFont(QuattrocentoSans_10);
	tft.setCursor(40, 60);
	tft.fillRect(40, 60, 50, 22, bg);
	tft.print(brightness);
	tft.setCursor(40, 72);
	tft.print(getCoord(brightness));
	old_brightness = brightness;

	drawLayerInfo(tft.width()-INDICATOR_WIDTH+1, -1);

	tft.fillRect(8, 8, 90, 20, bg);
	tft.setFont(QuattrocentoSans_14);
	tft.setCursor(8, 8);
	tft.print(getTimeStr());
}


void onLayerChanged(uint8_t newLayer) {
	Serial.printf("Layer changed\n");
	needsLayerRedraw = true;
	setLayerIndicator(newLayer);
}


void inc_brightness() {
	float step = getBrightnessStep(brightness);
	brightness += step;
	if (brightness > 255.0f) {
		brightness = 255.0f;
	}
}

void dec_brightness() {
	float step = getBrightnessStep(brightness);
	brightness -= step;
	if (brightness < 0.0f) {
		brightness = 0.0f;
	}
}

float getBrightnessStep(float current) {
	return powf(2, brightness / 50.0f);
}

int16_t getCoord(float x) {
	return (int16_t)(log2f(x) * 50.0f);
}

void saveLcdSettings() {
	EEPROM.write(ADDR_BRIGHTNESS, brightness);
	EEPROM.write(ADDR_DARK_THEME, themeMode);
	EEPROM.write(ADDR_ACCENT_IDX, accentIdx);
}

void on_lcd_a_pressed() {

}

void on_lcd_b_pressed() {

}

void on_lcd_c_pressed() {

}

void on_lcd_d_pressed() {

}

void on_lcd_a_released() {

}

void on_lcd_b_released() {

}

void on_lcd_c_released() {

}

void on_lcd_d_released() {

}

void nextAccent() {
	if (accentIdx < ACCENT_OPTIONS_COUNT - 1) {
		setAccentIdx(accentIdx + 1);
	}
	else {
		setAccentIdx(0);
	}
}

void prevAccent() {
	if (accentIdx > 0) {
		setAccentIdx(accentIdx - 1);
	}
	else {
		setAccentIdx(ACCENT_OPTIONS_COUNT-1);
	}
}

bool isDarkMode() { return themeMode; }

void setDarkMode(boolean isDark)
{
	themeMode = isDark;
	if (themeMode)	{
		bg = COL_DARK;
		fg = COL_LIGHT;
	}
	else {
		fg = COL_DARK;
		bg = COL_LIGHT;
	}

	drawStartScreen();
}

void setAccentIdx(uint16_t idx) {
	accentIdx = idx;
	accentMid = ACCENT_OPTIONS[accentIdx].mid;
	accentLight = ACCENT_OPTIONS[accentIdx].light;
	accentDark = ACCENT_OPTIONS[accentIdx].dark;

	drawStartScreen();
}

void drawTextButton(uint8_t left, char str[]) {

}

void drawTextCentered(char *text, int y) {
	tft.setCursor((tft.width() - tft.strPixelLen(text)) / 2, y);
	tft.print(text);
}

void drawTextAlignRight(char *text, int y) {
	tft.setCursor(tft.width() - tft.strPixelLen(text), y);
	tft.print(text);
}

uint16_t getForegroundCol() {
	return fg;
}
uint16_t getBackgroundCol() {
	return bg;
}
uint16_t getAccentLightCol() {
	return accentLight;
}
uint16_t getAccentMidCol() {
	return accentMid;
}
uint16_t getAccentDarkCol() {
	return accentDark;
}