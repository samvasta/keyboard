#pragma once

#ifndef _KEYHANDLER_h
#define _KEYHANDLER_h

time_t getTeensy3Time();

void ensureRtcInitialized();
char *getTimeStr();

void beginTimeEdit();

void incHour();
void decHour();

void incMin();
void decMin();

void incSec();
void decSec();

void incDay();
void decDay();

void incMonth();
void decMonth();

void incYear();
void decYear();

void commitTimeEdit();
#endif