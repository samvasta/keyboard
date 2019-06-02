// 
// 
// 

#include "encoders.h"
#include "core_pins.h"
#include "common.h"
#include "usb_serial.h"
#include "lcd.h"
#include "mousehandler.h"

int8_t last_encoder_states[NUMBER_OF_ENCODERS] = { 0 };
int8_t encoder_values[NUMBER_OF_ENCODERS] = { 0 };

/*
  Encoder logic description (because it took me a while to figure out)

-------------------------------------------------------------------------------
  COUNTER-CLOCKWISE diagram

  Rule 1.a) When A changes, it is equal to B
  Rule 1.b) When B changes, it is opposite of A

  A
		________      ________      ________
		|      |      |      |      |      |
		|      |      |      |      |      |
  ______|      |______|      |______|      |


  B
	 ________      ________      ________
	 |      |      |      |      |      |
	 |      |      |      |      |      |
  ___|      |______|      |______|      |___


-------------------------------------------------------------------------------
  CLOCKWISE diagram

  Rule 2.a) When A changes, it is opposite of B
  Rule 2.b) When B changes, it is equal to A

  A
		________      ________      ________
		|      |      |      |      |      |
		|      |      |      |      |      |
  ______|      |______|      |______|      |


  B
  ____      ________      ________      ______
	 |      |      |      |      |      |
	 |      |      |      |      |      |
	 |______|      |______|      |______|

-------------------------------------------------------------------------------


	IDX         OLD AB        NEW AB        enc_states    DESCRIPTION                                 REASON FOR ENC_STATE VALUE
	0  (0x0)    LL            LL             0            (no change from old state, do nothing)
	1  (0x1)    LL            LH            -1            B changes to opposite of A                  Rule 1.b    (CCW)
	2  (0x2)    LL            HL             1            A changes to opposite of B                  Rule 2.a    (CW)
	3  (0x3)    LL            HH             0            (Both change, cannot determine)
	4  (0x4)    LH            LL             1            B changes to equal A                        Rule 2.b    (CW)
	5  (0x5)    LH            LH             0            (no change from old state, do nothing)
	6  (0x6)    LH            HL             0            (Both change, cannot determine)
	7  (0x7)    LH            HH            -1            A changes to equal B                        Rule 1.a    (CCW)
	8  (0x8)    HL            LL            -1            A changes to equal B                        Rule 1.a    (CCW)
	9  (0x9)    HL            LH             0            (Both change, cannot determine)
	10 (0xA)    HL            HL             0            (no change from old state, do nothing)
	11 (0xB)    HL            HH             1            B changes to equal A                        Rule 2.b    (CW)
	12 (0xC)    HH            LL             0            (Both change, cannot determine)
	13 (0xD)    HH            LH             1            A changes to opposite of B                  Rule 2.a    (CW)
	14 (0xE)    HH            HL            -1            B changes to opposite of A                  Rule 1.b    (CCW)
	15 (0xF)    HH            HH             0            (no change from old state, do nothing)

  Interesting to note: vertical symmetry of the table in the "REASON..."" column
*/
static const int8_t enc_states[] = { 0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0 };

void setup_encoders() {
	for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
		setPinInputHigh(ENCODERS_LINE_A[i]);
		setPinInputHigh(ENCODERS_LINE_B[i]);

		last_encoder_states[i] = 0;
		encoder_values[i] = 0;
	}
}

void scan_encoders() {
	for (int i = 0; i < NUMBER_OF_ENCODERS; i++) {
		//Prev state is still in the left-most 2 bits. Move it over 2 to make room for the next state
		last_encoder_states[i] <<= 2;

		//Read pin A and B into the 2 left-most bits where B is in the left-most bit and A is in the second-to-left-most bit
		last_encoder_states[i] |= ((readPin(ENCODERS_LINE_A[i]) << 0) | (readPin(ENCODERS_LINE_B[i]) << 1));

		//look up value using state table (see giant comment above)
		encoder_values[i] += enc_states[last_encoder_states[i] & 0xf];

		if (encoder_values[i] >= ENCODER_RESOLUTION) {
			onEncoder(i, true);
		}
		else if (encoder_values[i] <= -ENCODER_RESOLUTION) {
			onEncoder(i, false);
		}

		encoder_values[i] %= ENCODER_RESOLUTION;
	}
}

int32_t encValues[] = { 0,0 };
void onEncoder(uint8_t encNum, bool clockwise) {
	if (clockwise) {
		++encValues[encNum];
		if (encNum == 0) {
			scrollDown();
		}
		else if (encNum == 1) {
			scrollRight();
		}
	}
	else {
		--encValues[encNum];
		if (encNum == 0) {
			scrollUp();
		}
		else if (encNum == 1) {
			scrollLeft();
		}
	}
}

void on_encoder_l_pressed() {
	toggleScrollSpeedV();
	Serial.println("L Pressed");
}

void on_encoder_r_pressed() {
	toggleScrollSpeedH();
	Serial.println("R Pressed");
}

void on_encoder_l_released() {
	Serial.println("L Released");
}

void on_encoder_r_released() {
	Serial.println("R Released");
}