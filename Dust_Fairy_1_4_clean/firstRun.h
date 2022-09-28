#ifndef FIRSTRUN_H
#define FIRSTRUN_H

#include <Arduino.h>
#include "startLCD.h"
#include "solenoids.h"
#include "startLCD.h"

extern void firstRunFunc(int n, int sensOpen, int sensClose, int vacTest);
extern void testRunEven(int n, char value, int time);
extern void testRunNotEven(int n, char value, int time);
extern void something(int n, int solenoid);
extern void testRun();

#endif