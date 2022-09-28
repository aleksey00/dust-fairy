#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Si7021.h>

extern Adafruit_Si7021 tempsensor;

extern bool enableHeater;
extern uint8_t loopCnt;

extern void tempSetup();                                       // temp Sensor main.ino > setup()
extern void tempReading(int n, int line);                      // LCD Number, LCD line  [88.8oC 88.8F 36.7% #]
extern void fanOn(int solenoid, int offTemp, int onTemp);      // relay#, disable temp, enable relay temp reading

#endif