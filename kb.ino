// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       kb.ino
    Created:	1/29/2019 8:44:44 PM
    Author:     Sam Vasta
*/

// Define User Types below here or use a .h file
//
#include "pointer.h"
#include "lcd.h"
#include "encoders.h"
#include "matrix.h"
#include "TeensyThreads.h"
#include "TimeUtil.h"



#define LCD_UPDATE_FREQ_MILLIS 1000L / 10L	//30fps


// Define Function Prototypes that use User Types below here or use a .h file
//

//elapsedMillis is a special Teensyduino type: https://www.pjrc.com/teensy/td_timing_elaspedMillis.html
elapsedMillis since_lcd_refresh;



// Define Functions below here or use other .ino or cpp files
//

void lcd_loop() {

	setup_lcd();

	while (1) {
		if (since_lcd_refresh > LCD_UPDATE_FREQ_MILLIS)
		{
			//Serial.printf("Thread! %d\n", millis());
			update_lcd(since_lcd_refresh);
			since_lcd_refresh -= LCD_UPDATE_FREQ_MILLIS;
		}
		else {
			yield();
		}
	}
}

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);
	ensureRtcInitialized();
	setup_matrix();
	setup_encoders();
	setup_pointer();
	setPinOutput(6);
	threads.addThread(lcd_loop, 1);
}


int x = 0;
// Add the main program code into the continuous loop() function
void loop()
{
	scan_matrix();
	scan_encoders();
	scan_pointer();

	//Serial.printf("%s\n", getTimeStr());
}