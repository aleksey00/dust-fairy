#ifndef SOLENOIDS_H
#define SOLENOIDS_H

#include <Wire.h>
#include "Arduino.h"
#include "startLCD.h"
#include "humanTime.h"
#include "vacuum.h"

/*
solenoids, working pressure 14psi to 114psi
*/

const int solenoid1 = 44;  // SawBlade Close
const int solenoid2 = 45;  // SawBlade Open
const int solenoid3 = 46;  // EdgeBander Close
const int solenoid4 = 47;  // EdgeBander Open

const int gateE8Open = 41;                          // Endgebander 8" Gate Open Solenoid
const int gateE8Close = 50;                         // Endgebander 8" Gate Close Solenoid
const int gateE4Open = 43;                          // Endgebander 4" Gate Open Solenoid
const int gateE4Close = 48;                         // Endgebander 4" Gate Close Solenoid
const int gateE5Open = 45;                          // Endgebander 5" Gate Open Solenoid
const int gateE5Close = 46;                         // Endgebander 5" Gate Close Solenoid
const int gateTableSawOpen = 47;                    // Table Saw 5" Gate Open Solenoid
const int gateTableSawClose = 44;                   // Table Sae 5" Gate Close Solenoid
const int disabled = 42;                            // not used
const int disabled2 = 49;                           // not used
const int disabled3 = 51;                           // not used
const int disabled4 = 52;                           // OK/STOP lights NO/NC
const int vacuum = 53;                              // Dust-collector contactor ON/OFF solenoid

extern void gates(int n, int inByte);               // E. 8 port  O[O ]
extern void manualOverrride(int n, int inByte);     // 

extern void digitalPinsSetup(int first, int last);  // Digital pins initialization OUTPUT 41 -53
extern void analogPinsSetup();                      // Analog pins initialization INPUT 5, 11
extern void digitalPinsInputSetup(bool serial);     // Digital pins initializaion INPUT (serial feedback on/off)

extern void gateTest(int n, int val);  // test function for actual connections

#endif

// 12345678901234567890
// E. 8"port O[O ]X 
// E.trimmer
// E. 4"port
// Table Saw

// 12345678901234567890
// E. 8/4 O[X ]C O[X ]C
// E. Trimmer O[X ]C
// Table Saw O[X ]C
// Vacuum ONF  00:00:00

// 12345678901234567890
// E.8port 4port trimmr
// O[X ]C O[X ]C O[X ]C
// Table Saw O[X ]C
// Vacuum

// 12345678901234567890
// E. 8" XOOX E.4" XOOX
// E.trm XOOX TSaw XOOX
// Vacuum XOOX
// VACUUM T: 00:00:00.00

// 12345678901234567890
// 01234567890123456789
// E. 8"OOX 4"OOX PMOOX
// T.SawOOX Manual ONFF
// Dust Collector ONOFF
// RUN:Y:   00:00:00.00