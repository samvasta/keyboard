// matrix.h

#ifndef _MATRIX_h
#define _MATRIX_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "common.h"

#define MATRIX_ROWS 4
#define MATRIX_COLS 16

//Real way
//#define MATRIX_ROW_PINS { 33, 34, 32, 31 }
//#define MATRIX_COL_PINS { 30, 29, 35, 28, 27, 37, 38, 39, 36, 14, 15, 16, 26, 17, 18, 19 }

//flip
#define MATRIX_ROW_PINS { 33, 34, 32, 31 }
#define MATRIX_COL_PINS { 19, 18, 17, 26, 16, 15, 14, 36, 39, 38, 37, 27, 28, 35, 29, 30 }

#if (MATRIX_COLS <= 8)
	typedef  uint8_t    matrix_row_t;
#elif (MATRIX_COLS <= 16)
	typedef  uint16_t   matrix_row_t;
#elif (MATRIX_COLS <= 32)
	typedef  uint32_t   matrix_row_t;
#else
#error "MATRIX_COLS: invalid value"
#endif

#define KEY_CODE_META_START			0x6000
#define KEY_CODE_LCD_START			0x6100
#define KEY_CODE_ENCODER_START		0x6200
#define KEY_CODE_MACROS_START		0x6300
#define KEY_CODE_UNICODE_START		0x6400
#define KEY_CODE_DYN_MACRO_START	0x6500
#define KEY_CODE_FN_START			0x6600
#define KEY_CODE_SHIFTED_CHAR		0x6700

enum custom_keycodes {
	KEY_NO = KEY_CODE_META_START,					//Opaque No-Op
	KEY_TRANSPARENT,			//Transparent key
	KEY_LCD_CONTROL_A = KEY_CODE_LCD_START,
	KEY_LCD_CONTROL_B,
	KEY_LCD_CONTROL_C,
	KEY_LCD_CONTROL_D,
	KEY_ENCODER_L_SWITCH = KEY_CODE_ENCODER_START, //switch (press down) on left encoder
	KEY_ENCODER_R_SWITCH,  //switch (press down) on right encoder
	KEY_COPY = KEY_CODE_MACROS_START,
	KEY_CUT,
	KEY_PASTE,
	KEY_UNICODE_TOGGLE = KEY_CODE_UNICODE_START,
	DYN_REC_START1 = KEY_CODE_DYN_MACRO_START,
	DYN_REC_START2,
	DYN_REC_STOP,
	DYN_MACRO_PLAY1,
	DYN_MACRO_PLAY2,
	DYN_MACRO_RANGE,
	KEY_FN = KEY_CODE_FN_START,
	KEY_FN_TOGGLE = KEY_CODE_FN_START | 0x10,
	KEY_JMP = KEY_CODE_FN_START | 0x20
};

#define REC_DYN1 DYN_REC_START1 //Start/stop recording dynamic macro 1 (See custom logic in dynamic_macro.h)
#define REC_DYN2 DYN_REC_START2 //Start/stop recording dynamic macro 2 (See custom logic in dynamic_macro.h)
#define DYN1 DYN_MACRO_PLAY1
#define DYN2 DYN_MACRO_PLAY2

#define U_TGL KEY_UNICODE_TOGGLE

#define LCD_A KEY_LCD_CONTROL_A
#define LCD_B KEY_LCD_CONTROL_B
#define LCD_C KEY_LCD_CONTROL_C
#define LCD_D KEY_LCD_CONTROL_D
#define ENC_L KEY_ENCODER_L_SWITCH
#define ENC_R KEY_ENCODER_R_SWITCH

#define S(kc)		((kc & 0x00ff) | KEY_CODE_SHIFTED_CHAR)

#define KEY_GRV  KEY_TILDE
#define KEY_EXLM S(KEY_1)
#define KEY_AT   S(KEY_2)
#define KEY_HASH S(KEY_3)
#define KEY_DLR  S(KEY_4)
#define KEY_PERC S(KEY_5)
#define KEY_CIRC S(KEY_6)
#define KEY_AMPR S(KEY_7)
#define KEY_ASTR S(KEY_8)
#define KEY_LPRN S(KEY_9)
#define KEY_RPRN S(KEY_0)

#define ______ KEY_TRANSPARENT


// Momentary switch layer - 256 layer max
#define MO(layer) (KEY_FN | (layer & 0xFF))

//16 Cols (0 - F)
//4 Rows  (0 - 3)
//prefix legend:
//  k - normal Key
//  t - Thumb key
//  e - Encoder switch
//Have to transpose "list" of rows into a list of columns b/c I screwed up the diode direction
#define KEYMAP(                                                                                         \
         k00, k01, k02, k03, k04, k05,                                k0a, k0b, k0c, k0d, k0e, k0f,     \
         k10, k11, k12, k13, k14, k15,                                k1a, k1b, k1c, k1d, k1e, k1f,     \
         k20, k21, k22, k23, k24, k25,   t26,    t27,   t28,   t29,   k2a, k2b, k2c, k2d, k2e, k2f,     \
         k30, k31, k32, k33, k34, k35,   t36,    t37,   t38,   t39,   k3a, k3b, k3c, k3d, k3e, k3f      \
)                                                                                                       \
{                                                                                                       \
        {k00,    k10,   k20, k30},	\
        {k01,    k11,   k21, k31},	\
        {k02,    k12,   k22, k32},	\
        {k03,    k13,   k23, k33},	\
        {k04,    k14,   k24, k34},	\
        {k05,    k15,   k25, k35},	\
        {ENC_L,  LCD_A, t26, t36},	\
        {ENC_R,  LCD_B, t27, t37},	\
        {KEY_NO, LCD_C, t28, t38},	\
        {KEY_NO, LCD_D, t29, t39},	\
        {k0a,    k1a,   k2a, k3a},	\
        {k0b,    k1b,   k2b, k3b},	\
        {k0c,    k1c,   k2c, k3c},	\
        {k0d,    k1d,   k2d, k3d},	\
        {k0e,    k1e,   k2e, k3e},	\
        {k0f,    k1f,   k2f, k3f}	\
}



#define DEBOUNCING_DELAY 5
#define false 0

#ifdef __cplusplus
	extern "C" {
#endif
	void setup_matrix();
	void scan_matrix();

#ifdef __cplusplus
}
#endif
#endif

