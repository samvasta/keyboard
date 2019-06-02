// 
// 
// 

#include "lcd.h"
#include "Keyboard.h"
#include "SPI.h"
#include "Wire.h"
#include "ILI9341_t3.h"
#include "fonts/font_Quattrocento-Bold.h"
#include "fonts/font_Quattrocento-Regular.h"
#include "fonts/font_QuattrocentoSans-Regular.h"
#include "EEPROM.h"
#include "persist.h"
#include "TimeUtil.h"
#include "TimeLib.h"
#include "LayerIndicator.h"
#include "KeyboardLedIndicators.h"


#define TFT_CS 10
#define TFT_DC  9
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_CLK 13
#define TFT_RST 8

#define CLOCK_UPDATE_FREQ_MS 1000 * 10	//every 10 sec

#define NUM_WELCOME_MESSAGES 2
static const String WELCOME_MESSAGES[4][2] = {
	{"good morning", "hello sam"},
	{"good afternoon", "wecome back"},
	{"good evening", "keep it up!"},
	{"go to bed", "it's late"}
};

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
volatile uint8_t prevLedStatus = 0xff;

bool isRefreshing;
bool needsLayerRedraw;
bool needsLedStatusRedraw;
uint64_t lastClockUpdate;

ILI9341_t3 *getTft() {
	return &tft;
}

void setup_lcd() {
	lastClockUpdate = 0;
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

	String msg;
	int h = hour();
	if (h < 6 || h > 20) {
		msg = WELCOME_MESSAGES[3][random(0, 2)];
	}
	else if (h < 11) {
		msg = WELCOME_MESSAGES[0][random(0, 2)];
	}
	else if (h < 16) {
		msg = WELCOME_MESSAGES[1][random(0, 2)];
	}
	else {
		msg = WELCOME_MESSAGES[2][random(0, 2)];
	}
	
	char str[msg.length() + 1];
	strcpy(str, msg.c_str());

	drawTextCentered(str, (tft.height() - 20) / 2);
}

void drawStartScreen() {
	isRefreshing = true;
	tft.fillScreen(bg);

	displayWelcome();
	needsLedStatusRedraw = true;
	needsLayerRedraw = true;
	lastClockUpdate = 0;

	isRefreshing = false;
}

int16_t getCoord(float x);

void update_lcd(uint64_t delta) {
	analogWrite(8, (uint8_t)brightness);

	if (isRefreshing) {
		//Skip this frame if we're drawing elsewhere
		return;
	}

	old_brightness = brightness;

	if (needsLayerRedraw) {
		drawLayerInfo(tft.width()-LAYER_INDICATOR_WIDTH+1, -1);
		needsLayerRedraw = false;
	}

	needsLedStatusRedraw |= (keyboard_leds != prevLedStatus);
	if (needsLedStatusRedraw) {
		drawLedIndicators(tft.width() - LED_INDICATOR_WIDTH - LAYER_INDICATOR_WIDTH + 2, -1, keyboard_leds);
		prevLedStatus = keyboard_leds;
		needsLedStatusRedraw = false;
	}
	

	if (millis() - lastClockUpdate > CLOCK_UPDATE_FREQ_MS) {
		tft.fillRect(8, 8, 120, 20, bg);
		tft.setFont(QuattrocentoSans_14);
		tft.setCursor(8, 8);
		tft.print(getTimeStr());

		lastClockUpdate = millis();
	}
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
	saveLcdSettings();
}

void on_lcd_b_pressed() {
	setDarkMode(!isDarkMode());
}

void on_lcd_c_pressed() {
	prevAccent();
}

void on_lcd_d_pressed() {
	nextAccent();
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