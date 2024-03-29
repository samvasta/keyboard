﻿// 
// 
// 

#include "keymap.h"
#include "common.h"
#include "matrix.h"
#include "keylayouts.h"



#define BASE_LAYER 0x0		//FN			(0 btns)
#define LAYER_1    0x1		//FN 1			(1 btns) *
#define LAYER_2    0x2		//FN   2		(1 btns) *
#define LAYER_3    0x3		//FN 1 2		(2 btns) **
#define LAYER_4    0x4		//FN     3		(1 btns) *
#define LAYER_5    0x5		//FN 1   3		(2 btns) **
#define LAYER_6    0x6		//FN   2 3		(2 btns) **
#define LAYER_7    0x7		//FN 1 2 3		(3 btns) ***
#define LAYER_8    0x8		//FN       4	(1 btns) *
#define LAYER_9    0x9		//FN 1     4	(2 btns) **
#define LAYER_A    0xA		//FN   2   4	(2 btns) **
#define LAYER_B    0xB		//FN 1 2   4	(3 btns) ***
#define LAYER_C    0xC		//FN     3 4	(2 btns) **
#define LAYER_D    0xD		//FN 1   3 4	(3 btns) ***
#define LAYER_E    0xE		//FN   2 3 4	(3 btns) ***
#define LAYER_F    0xF		//FN 1 2 3 4	(4 btns) ****

#define FN(l) (KEY_FN | (l & 0xf))
#define TO(l) (KEY_FN_TOGGLE | (l & 0xf))
#define JMP(l) (KEY_JMP | (l & 0xf))


const static uint16_t keymaps[][MATRIX_COLS][MATRIX_ROWS] = {	//Add 1 to MATRIX_COLS for the LCD buttons column

	/*
	BASE LAYER (no FN)
	Left Hand                                                 L. Thumb  L. Thumb          R. Thumb  R. Thumb    Right Hand
	┌────────┬────────┬────────┬────────┬────────┬────────┐  ┌────────┐┌────────┐                              ┌────────┬────────┬────────┬────────┬────────┬────────┐
	│  ESC   │    Q   │   W    │   E    │   R    │   T    │  │ ROT.L* ││ ROT.R* │                              │    Y   │   U    │   I    │    O   │   P    │ BKSPC  │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤├────────┤        ┌────────┐┌────────┐  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│  TAB   │    A   │   S    │   D    │   F    │   G    │  │ LCD_A  ││ LCD_B  │        │ LCD_C  ││ LCD_D  │  │    H   │   J    │   K    │    L   │   ;    │ ENTER  │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤├────────┤        ├────────┤├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│  SHIFT │    Z   │   X    │   C    │   V    │   B    │  │ TOG 1  ││ TOG 4  │        │ TOG 8  ││ TOG 2  │  │    N   │   M    │   , <  │  . >   │   / ?  │ R SHFT │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤├────────┤        ├────────┤├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│  CTL   │  GUI   │  ALT   │ REC. 1 │  SPACE │  SPACE │  │  FN 1  ││  FN 4  │        │  FN 8  ││  FN 2  │  │ SPACE  │ SPACE  │ REC. 2 │  ALT   │  GUI   │  CTL   │
	└────────┴────────┴────────┴────────┴────────┴────────┘  └────────┘└────────┘        └────────┘└────────┘  └────────┴────────┴────────┴────────┴────────┴────────┘

	*ROT.L and ROT.R are push switches on rotary encoders (left and right)

	*/
	[BASE_LAYER] = KEYMAP(
		KEY_ESC,   KEY_Q,    KEY_W,    KEY_E,     KEY_R,   KEY_T,                                      KEY_Y,   KEY_U,   KEY_I,     KEY_O,    KEY_P,      KEY_BSPC,
		KEY_TAB,   KEY_A,    KEY_S,    KEY_D,     KEY_F,   KEY_G,                                      KEY_H,   KEY_J,   KEY_K,     KEY_L,    KEY_SCLN,   KEY_ENTER,
		KEY_LSFT,  KEY_Z,    KEY_X,    KEY_C,     KEY_V,   KEY_B,   TO(1),  TO(4),    TO(8),  TO(2),   KEY_N,   KEY_M,   KEY_COMMA, KEY_DOT,  KEY_SLASH,  KEY_RSFT,
		KEY_LCTL,  KEY_LGUI, KEY_LALT, REC_DYN1, KEY_SPC, KEY_SPC,  FN(1),  FN(4),    FN(8),  FN(2),   KEY_SPC, KEY_SPC, REC_DYN2,  KEY_RALT, KEY_RGUI,   KEY_RCTL
	),


	/*
	LAYER 1 (FN 1)
	Left Hand                                                 L. Thumb                              R. Thumb    Right Hand
	┌────────┬────────┬────────┬────────┬────────┬────────┐                                                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
	│        │ XXXXXX │ XXXXXX │ XXXXXX │  HOME  │ PG.UP  │                                                    │ XXXXXX │ BKSPC  │   UP   │  DEL   │ INSERT │ PRTSCR │
	├────────┼────────┼────────┼────────┼────────┼────────┤                                                    ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │SHFT+TAB│ L CTL  │ L ALT  │   END  │ PG.DN  │                                                    │ XXXXXX │ LEFT   │  DOWN  │  RIGHT │ XXXXXX │        │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ┌────────┐┌────────┐        ┌────────┐┌────────┐  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │ XXXXXX │ XXXXXX │ XXXXXX │ XXXXXX │ XXXXXX │  │        ││        │        │        ││        │  │ XXXXXX │ CUT    │  COPY  │ PASTE  │ XXXXXX │        │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤├────────┤        ├────────┤├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │        │        │        │        │        │  │        ││        │        │        ││        │  │        │        │        │        │        │        │
	└────────┴────────┴────────┴────────┴────────┴────────┘  └────────┘└────────┘        └────────┘└────────┘  └────────┴────────┴────────┴────────┴────────┴────────┘

	*ROT.L and ROT.R are push switches on rotary encoders (left and right)

	*/
	[LAYER_1] = KEYMAP(
		______, KEY_NO,     KEY_NO,   KEY_NO,   KEY_HOME, KEY_PGUP,                                        KEY_NO , KEY_BSPC, KEY_UP,   KEY_DEL,   KEY_INS, KEY_PSCR,
		______, S(KEY_TAB), KEY_LCTL, KEY_LALT, KEY_END,  KEY_PGDN,                                        KEY_NO , KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_NO , ______,
		______, KEY_NO,     KEY_NO,   KEY_NO,   KEY_NO,   KEY_NO,    ______, ______,     ______,  ______,  KEY_NO , KEY_CUT,  KEY_COPY, KEY_PASTE, KEY_NO , ______,
		______, ______,     ______,   ______,   ______,   ______,    ______, ______,     ______,  ______,  ______,  ______,   ______,   ______,    ______,  ______
	),

	/*
	LAYER 2 (FN 2)
	Left Hand                                                 L. Thumb         R. Thumb    Right Hand
	┌────────┬────────┬────────┬────────┬────────┬────────┐  ┌────────┐       ┌────────┐  ┌────────┬────────┬────────┬────────┬────────┬────────┐
	│  ` ~   │    !   │    @   │   #    │   $    │   %    │  │        │       │        │  │   ^    │   &    │   *    │   (    │    )   │        │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │ XXXXXX │    |   │   _    │   +    │   {    │  │        │       │        │  │   }    │   "    │   <    │   >    │   ?    │        │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │ XXXXXX │    \   │   -    │   =    │   [    │  │        │       │        │  │   ]    │   '    │   ,    │   .    │   /    │        │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │        │        │        │        │        │  │        │       │        │  │        │        │        │        │        │        │
	└────────┴────────┴────────┴────────┴────────┴────────┘  └────────┘       └────────┘  └────────┴────────┴────────┴────────┴────────┴────────┘

	*ROT.L and ROT.R are push switches on rotary encoders (left and right)

	*/
	[LAYER_2] = KEYMAP(
		KEY_GRV, KEY_EXLM, KEY_AT ,        KEY_HASH,	 KEY_DLR,    KEY_PERC,                                            KEY_CIRC   , KEY_AMPR,    KEY_ASTR,    KEY_LPRN,   KEY_RPRN,     JMP(0),
		______,  KEY_NO  , S(KEY_BSLASH) , S(KEY_UNDS), S(KEY_EQL), S(KEY_LBRC) ,                                        S(KEY_RBRC), S(KEY_QUOT), S(KEY_COMM), S(KEY_DOT), S(KEY_SLASH), ______,
		______,  KEY_NO  , KEY_BSLASH,     KEY_UNDS,    KEY_EQL,    KEY_LBRC ,    ______, ______,     ______,  ______,   KEY_RBRC   , KEY_QUOT ,   KEY_COMM,    KEY_DOT,    KEY_SLASH,    ______,
		______,  ______  ,  ______, ______ ,     ______,     ______ ,      ______, ______,     ______,  ______,   ______     , ______ ,     ______ ,     ______ ,    ______ ,      ______
	),


	/*
	LAYER 3 (FN 1+2)
	Left Hand                                                 L. Thumb         R. Thumb    Right Hand
	┌────────┬────────┬────────┬────────┬────────┬────────┐  ┌────────┐       ┌────────┐  ┌────────┬────────┬────────┬────────┬────────┬────────┐
	│        │ VOL-   │  MUTE  │  VOL+  │ XXXXXX │ XXXXXX │  │ ROT.L* │       │ ROT.R* │  │ XXXXXX │  F1    │  F2    │  F3    │  F4    │    F5  │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │  <<    │   > || │  >>    │ XXXXXX │ XXXXXX │  │        │       │        │  │ XXXXXX │  F6    │  F7    │  F8    │  F9    │   F10  │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │ XXXXXX │ XXXXXX │ XXXXXX │ XXXXXX │ XXXXXX │  │        │       │        │  │ XXXXXX │  F11   │  F12   │  F13   │  F14   │   F15  │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │        │        │        │        │        │  │        │       │        │  │        │        │        │        │        │        │
	└────────┴────────┴────────┴────────┴────────┴────────┘  └────────┘       └────────┘  └────────┴────────┴────────┴────────┴────────┴────────┘

	*ROT.L and ROT.R are push switches on rotary encoders (left and right)

	*/
	[LAYER_3] = KEYMAP(
		______, KEY_VOLD, KEY_MUTE, KEY_VOLU, KEY_NO , KEY_NO ,                                          KEY_NO , KEY_F1 , KEY_F2 , KEY_F3 , KEY_F4 , ______,
		______, KEY_MPRV, KEY_MPLY, KEY_MNXT, KEY_NO , KEY_NO ,                                          KEY_NO , KEY_F5 , KEY_F6 , KEY_F7 , KEY_F8 , ______,
		______, KEY_NO ,  KEY_NO ,  KEY_NO ,  KEY_NO , KEY_NO ,   ______, ______,     ______,  ______,   KEY_NO , KEY_F9 , KEY_F10, KEY_F11, KEY_F12, ______,
		______, ______,   ______,   ______,   ______,  ______,    ______, ______,     ______,  ______,   ______,  ______,  ______,  ______,  ______,  ______
	),

	/*
	LAYER 4 (FN 4)
	Left Hand                                                 L. Thumb         R. Thumb    Right Hand
	┌────────┬────────┬────────┬────────┬────────┬────────┐  ┌────────┐       ┌────────┐  ┌────────┬────────┬────────┬────────┬────────┬────────┐
	│        │        │ NUMLCK │ U TGL  │ L ALT  │        │  │ ROT.L* │       │ ROT.R* │  │ NUM 0  │ NUM 1  │ NUM 2  │ NUM 3  │ NUM 4  │ NUM 5  │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │   *    │   /    │   _    │   +    │ NUM .  │  │        │       │        │  │   x    │ NUM 6  │ NUM 7  │ NUM 8  │ NUM 9  │    A   │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │        │        │   -    │   =    │        │  │        │       │        │  │   #    │    B   │    C   │    D   │   E    │    F   │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │        │        │        │        │        │  │        │       │        │  │        │        │        │        │        │        │
	└────────┴────────┴────────┴────────┴────────┴────────┘  └────────┘       └────────┘  └────────┴────────┴────────┴────────┴────────┴────────┘

	*ROT.L and ROT.R are push switches on rotary encoders (left and right)
	
	*/
	[LAYER_4] = KEYMAP(
		______, ______,   KEY_NUM_LOCK, U_TGL,     KEY_LALT,    ______,                                      KEY_P0,    KEY_P1,   KEY_P2,   KEY_P3,   KEY_P4,   KEY_P5,
		______, KEY_ASTR, KEY_SLASH,    KEY_UNDS,  KEYPAD_PLUS, KEY_PDOT,                                    KEY_X,     KEY_P6,   KEY_P7,   KEY_P8,   KEY_P9,   S(KEY_A),
		______, ______,   ______,       KEY_MINUS, KEY_EQL,     ______,   ______, ______,    ______, ______, KEY_HASH,  S(KEY_B), S(KEY_C), S(KEY_D), S(KEY_E), S(KEY_F),
		______, ______,   ______,       ______,    ______,      ______,   ______, ______,    ______, ______, ______,    ______,   ______,   ______,   ______,   ______
	),  

	/*
	LAYER 5 (FN 1+4)
	Left Hand                                                 L. Thumb         R. Thumb    Right Hand
	┌────────┬────────┬────────┬────────┬────────┬────────┐  ┌────────┐       ┌────────┐  ┌────────┬────────┬────────┬────────┬────────┬────────┐
	│        │        │        │        │        │        │  │ ROT.L* │       │ ROT.R* │  │        │        │        │        │        │        │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │        │        │        │        │        │  │        │       │        │  │        │        │        │        │        │        │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │        │        │        │        │        │  │        │       │        │  │        │        │        │        │        │        │
	├────────┼────────┼────────┼────────┼────────┼────────┤  ├────────┤       ├────────┤  ├────────┼────────┼────────┼────────┼────────┼────────┤
	│        │        │        │        │        │        │  │        │       │        │  │        │        │        │        │        │        │
	└────────┴────────┴────────┴────────┴────────┴────────┘  └────────┘       └────────┘  └────────┴────────┴────────┴────────┴────────┴────────┘

	*ROT.L and ROT.R are push switches on rotary encoders (left and right)

	*/
	[LAYER_5] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 2+4
	[LAYER_6] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 1+2+4
	[LAYER_7] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 8
	[LAYER_8] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 1+8
	[LAYER_9] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 2+8
	[LAYER_A] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 1+2+8
	[LAYER_B] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 4+8
	[LAYER_C] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 1+4+8
	[LAYER_D] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 2+4+8
	[LAYER_E] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	),

	//FN 1+2+4+8
	[LAYER_F] = KEYMAP(
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,                                          ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______,
		______, ______, ______, ______, ______, ______,   ______, ______,     ______,  ______,   ______, ______, ______, ______, ______, ______
	)
};



