// 
// 
// 
#include "Arduino.h"
#include "common.h"
#include "keyhandler.h"
#include "keymap.cpp"
#include "usb_serial.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "encoders.h"
#include "lcd.h"

matrix_row_t matrix_prev[MATRIX_ROWS];
uint8_t led_status = 0;

volatile uint8_t prevLayer;
volatile uint8_t layer;
keyevent_t pressedState[MATRIX_ROWS * MATRIX_COLS];
volatile uint16_t modifiers = 0;

void initMatrix() {

	for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
		for (uint8_t c = 0; c < MATRIX_COLS; c++) {
			pressedState[r*MATRIX_COLS + c] =
			{
				.key = { r, c },
				.pressed = 0
			};
		}
	}
}

void processMatrixState(matrix_row_t * matrix) {

	matrix_row_t matrix_row;
	matrix_row_t matrix_change[MATRIX_ROWS];
	uint32_t curTime = millis();
	for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
		matrix_row = matrix[r];
		matrix_change[r] = matrix_prev[r] ^ matrix_row;

		for (uint8_t c = 0; c < MATRIX_COLS; c++) {
			if ((matrix_change[r] >> c) & 1) {
				bool isPressed = ((matrix_row >> c) & 1);

				keyevent_t* e = &pressedState[r * MATRIX_COLS + c];

				if (e->pressed != isPressed) {
					e->pressed = isPressed;
				}
				preProcessKey(*e);

				// record a processed key
				matrix_prev[r] ^= ((matrix_row_t)1 << c);
			}
		}
	}

	Keyboard.set_modifier(modifiers);

	for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
		for (uint8_t c = 0; c < MATRIX_COLS; c++) {
			if ((matrix_change[r] >> c) & 1) {
				processKey(pressedState[r * MATRIX_COLS + c]);
			}
		}
	}

	prevLayer = layer;
	Keyboard.send_now();
}

void preProcessKey(keyevent_t e) {
	//Resolve the layer, then resolve the modifiers & keys
	uint16_t code = getKeyCode(e.key.row, e.key.col, layer);
	if (code == KEY_NO) {
		return;
	}

	if (code >= 0xF000) {
		//standard code
		//Nothing to pre-process
	}
	else if (code >= 0xE000) {
		//Modifier
		if (e.pressed) {
			modifiers |= code & 0x00ff;
		}
		else {
			modifiers &= ~(code & 0x00ff);
		}
	}
	else if (code >= 0xE200 && e.pressed) {
		//System code
		//Nothing to pre-process
	}
	else if (code >= 0xE400 && e.pressed) {
		//Media code
		//Nothing to pre-process
	}
	else if (code >= KEY_CODE_META_START) {
		if (code >= KEY_CODE_SHIFTED_CHAR) {
			//Nothing to pre-process
		}
		else if (code > KEY_CODE_FN_START) {
			bool isToggle = (code & KEY_FN_TOGGLE) == KEY_FN_TOGGLE;
			if (e.pressed && !isToggle) {
				layer |= (code & 0xff);
			}
			else if(!e.pressed) {
				if (isToggle) {
					uint8_t toggleCode = (code & 0x0f) << 4;
					layer ^= toggleCode;
				}
				else {
					layer &= ~(code & 0xff);
				}
			}
			onLayerChanged(layer);
			Serial.printf("New active layer: %02x\n", layer);
		}
		else if (code >= KEY_CODE_DYN_MACRO_START) {
			//Nothing to pre-process
		}
		else if (code >= KEY_CODE_UNICODE_START) {
			//Nothing to pre-process
		}
		else if (code >= KEY_CODE_MACROS_START && e.pressed) {
			//send macros immediately
			//Nothing to pre-process
		}
		else {
			//LCD or encoder btn
			//Nothing to pre-process
		}
	}
}


void processKey(keyevent_t e) {
	//Resolve the layer, then resolve the modifiers & keys
	uint16_t oldCode = getKeyCode(e.key.row, e.key.col, prevLayer);
	uint16_t code = getKeyCode(e.key.row, e.key.col, layer);
	if (code == KEY_NO) {
		return;
	}

	if (code >= 0xF000) {
		//standard code
		if (e.pressed) {
			Keyboard.press(code);
		}
		else {
			Keyboard.release(oldCode);
		}
	}
	else if (code >= 0xE000) {
		//Modifiers handled in pre-process step
	}
	else if (code >= 0xE200 && e.pressed) {
		//System code
	}
	else if (code >= 0xE400 && e.pressed) {
		//Media code
	}
	else if (code >= KEY_CODE_META_START) {
		if (code >= KEY_CODE_SHIFTED_CHAR) {
			if (e.pressed) {
				modifiers = 0xFF & MODIFIERKEY_LEFT_SHIFT;
				Keyboard.set_modifier(modifiers);
				Keyboard.press((code & 0xff) | 0xf000);
				Serial.printf("pressing shifted key %04x\n", code & 0xf0ff);
			}
			else {
				modifiers = 0;
				Keyboard.set_modifier(modifiers);
				Keyboard.release((oldCode & 0xff) | 0xf000);
			}
		}
		else if (code > KEY_CODE_FN_START) {
			//Layers handled in pre-process step
		}
		else if (code >= KEY_CODE_DYN_MACRO_START) {
			//TODO
		}
		else if (code >= KEY_CODE_UNICODE_START) {
			//TODO
		}
		else if (code >= KEY_CODE_MACROS_START && e.pressed) {
			//send macros immediately
			switch (code) {
			case KEY_COPY:
				//sendKey((KEY_C & 0xff), (0xFF & MODIFIERKEY_LEFT_CTRL));
				break;
			case KEY_CUT:
				//sendKey((KEY_X & 0xff), (0xFF & MODIFIERKEY_LEFT_CTRL));
				break;
			case KEY_PASTE:
				//sendKey((KEY_V & 0xff), (0xFF & MODIFIERKEY_LEFT_CTRL));
				break;
			}
		}
		else {
			if (e.pressed) {
				switch (code) {
				case LCD_A: on_lcd_a_pressed(); return;
				case LCD_B: on_lcd_b_pressed(); return;
				case LCD_C: on_lcd_c_pressed(); return;
				case LCD_D: on_lcd_d_pressed(); return;
				case ENC_L: on_encoder_l_pressed(); return;
				case ENC_R: on_encoder_r_pressed(); return;
				}
			}
			else {
				switch (code) {
				case LCD_A: on_lcd_a_released(); return;
				case LCD_B: on_lcd_b_released(); return;
				case LCD_C: on_lcd_c_released(); return;
				case LCD_D: on_lcd_d_released(); return;
				case ENC_L: on_encoder_l_released(); return;
				case ENC_R: on_encoder_r_released(); return;
				}
			}
		}
	}
}

uint16_t getKeyCode(uint8_t row, uint8_t col, uint8_t layer) {
	uint16_t code = KEY_NO;

	uint8_t currentLayer = (layer ^ (layer >> 4)) & 0xf;

	for (uint8_t try_count = 0; currentLayer >= 0 && try_count < 255; try_count++) {
		code = keymaps[currentLayer][col][row];
		if (code == KEY_TRANSPARENT) {
			--currentLayer;
		}
		else if ((code & 0xfff0) == KEY_JMP) {
			Serial.printf("jumping from layer %d to %d (code=%04x)\n", currentLayer, (code & 0xf), code, KEY_JMP);
			currentLayer = code & 0xf;
		}
		else {
			return code;
		}
	}

	return code;
}