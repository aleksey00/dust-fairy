#ifndef FIRSTRUN_H
#define FIRSTRUN_H

#include <Arduino.h>
#include "startLCD.h"
#include "solenoids.h"

/* testRun used in setup */
extern void testRun();           // run in setup() to activate relays and open all gates by default

/* firstRunFunc uses testRunEven and testRunNotEven methods */
extern void firstRunFunc(int n, int sensOpen, int sensClose, int vacTest);  // sequential solenoid test uses testRunEven() and testRunNotEven
extern void testRunEven(int n, char value, int time);                       // test run of even relays (lcd, HIGH or LOW, delay)
extern void testRunNotEven(int n, char value, int time);                    // test run of non-even relays (lcd, HIGH or LOW, delay)

/* printAllAnalog function is not used */
extern void printAllAnalog();    // function designed to test real time value in Analog inputs
#endif