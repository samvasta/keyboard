
#include "Wire.h"
#include "TimeUtil.h"
#include "TimeLib.h"
#include "DS1307RTC.h"

time_t getTeensy3Time() {
	return Teensy3Clock.get();
}

bool isInitialized = false;
void ensureRtcInitialized() {
	if (!isInitialized) {
		setSyncProvider(getTeensy3Time);
		if (timeStatus() != timeSet) {
			Serial.println("Unable to sync with the RTC");
		}
		else {
			Serial.println("RTC has set the system time");
			setTime(13, 23, 45, 30, 4, 2019);
			Serial.println(getTimeStr());
		}
	}
}

static char currentTimeStr[15];
char* getTimeStr() {
	sprintf(currentTimeStr, "%s, %d:%d %s", dayShortStr(weekday()), hourFormat12(), minute(), isAM() ? "a" : "p");
	return currentTimeStr;
}


uint8_t editHour;
uint8_t editMinute;
uint8_t editSecond;
uint8_t editDay;
uint8_t editMonth;
uint8_t editYear;

void beginTimeEdit() {
	editHour = hour();
	editMinute = minute();
	editSecond = second();
	editDay = day();
	editMonth = month();
	editYear = year();
}

void incHour() {
	++editHour;
	while (editHour >= 24) {
		editHour -= 24;
	}
}
void decHour() {
	--editHour;
	while (editHour < 0) {
		editHour += 24;
	}
}

void incMin() {
	++editMinute;
	while (editMinute >= 60) {
		editMinute -= 60;
	}
}
void decMin() {
	--editMinute;
	while (editMinute < 0) {
		editMinute += 60;
	}
}

void incSec() {
	++editSecond;
	while (editSecond >= 60) {
		editSecond -= 60;
	}
}
void decSec() {
	--editSecond;
	while (editSecond < 0) {
		editSecond += 60;
	}
}

void incDay() {
	++editDay;
	while (editDay > 31) {
		editDay -= 31;
	}
}
void decDay() {
	--editMonth;
	while (editMonth < 1) {
		editMonth += 31;
	}
}

void incMonth() {
	++editMonth;
	while (editMonth > 12) {
		editMonth -= 12;
	}
}
void decMonth() {
	--editMonth;
	while (editMonth < 1) {
		editMonth += 12;
	}
}

void incYear() {
	++editYear;
	if (editYear > 9999) {
		editYear = 9999;
	}
}
void decYear() {
	--editYear;
	if (editYear < 1970) {
		editYear =1970;
	}
}

void commitTimeEdit() {
	setTime(editHour, editMinute, editSecond, editDay, editMonth, editYear);
}