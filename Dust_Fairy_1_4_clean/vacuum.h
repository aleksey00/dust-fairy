#ifndef VACUUM_H
#define VACUUM_H

#include <Arduino.h>
#include <Wire.h>
#include "Arduino.h"
#include "solenoids.h"
#include "humanTime.h"


extern void vacOperate(int n, bool activate);                 // vac on function 1=vacuum on with lcd messade, 0=vacuum off with lcd message
extern void vacuumFunction(int n);                            // Dust Collector and gate automation for TS and EB

#endif



