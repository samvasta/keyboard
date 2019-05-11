// lcd.h

#ifndef _LCD_h
#define _LCD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifdef __cplusplus

#include "ILI9341_t3.h"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define BTN_HEIGHT 22
#define BTN_TOP_BORDER_HEIGHT 2
#define BTN_TOP SCREEN_WIDTH-BTN_HEIGHT+BTN_TOP_BORDER_HEIGHT

#define BTN_A_LEFT 0
#define BTN_A_WIDTH 79
	//2 px border
#define BTN_B_LEFT 81
#define BTN_B_WIDTH 78
	//2 px border
#define BTN_C_LEFT 161
#define BTN_C_WIDTH 78
	//2 px border
#define BTN_D_LEFT 241
#define BTN_D_WIDTH 79

#define SCREEN_USABLE_HEIGHT SCREEN_HEIGHT-BTN_HEIGHT

#define COL_ERROR 0xB004
#define COL_LIGHT 0xFFFF
#define COL_DARK  0x0000

struct AccentOption {
	char name[8];
	uint16_t mid;
	uint16_t light;
	uint16_t dark;
};

#define ACCENT_OPTIONS_COUNT 2
const AccentOption ACCENT_OPTIONS[] = {
	{"purple", 0x79FE, 0xB4FB, 0x30D2},
	{"yellow", 0xFE45, 0xFE10, 0xFC60}
};

ILI9341_t3 *getTft();

void drawTextCentered(char[], int y);
void drawTextAlignRight(char[], int y);

uint16_t getForegroundCol();
uint16_t getBackgroundCol();
uint16_t getAccentLightCol();
uint16_t getAccentMidCol();
uint16_t getAccentDarkCol();


void drawStartScreen();

void displayWelcome();
bool isDarkMode();
void setDarkMode(boolean);
void setAccentIdx(uint16_t);
void saveLcdSettings();
void draw_text_button(uint8_t, char[]);

void setup_lcd();

void update_lcd(uint64_t);

void onLayerChanged(uint8_t newLayer);

float getBrightnessStep(float current);
void inc_brightness();
void dec_brightness();

void nextAccent();
void prevAccent();

void on_lcd_a_pressed();
void on_lcd_b_pressed();
void on_lcd_c_pressed();
void on_lcd_d_pressed();

void on_lcd_a_released();
void on_lcd_b_released();
void on_lcd_c_released();
void on_lcd_d_released();

extern "C" {
#endif


#ifdef __cplusplus
}
#endif
#endif

