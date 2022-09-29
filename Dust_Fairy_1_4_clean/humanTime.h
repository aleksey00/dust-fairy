#ifndef HUMANTIME_H
#define HUMANTIME_H

#include "startLCD.h"
#include <Arduino.h>

extern void humanTime(int n, unsigned long times, int line, String text, bool visible); // LCD, millis(), LCD line, text, show // time to LCD 
extern void humanTimeSerial(unsigned long times);                                       // Serial time 

#endif