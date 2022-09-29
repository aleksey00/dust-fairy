#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include <Wire.h>
#include "Arduino.h"

/*
  solenoid sensor at A2 and main sensor at A4      
*/

const byte pressureInput = A2;                      // analog input pin for the Solenoid base pressure transducer
const byte pressureInputMain = A4;                  // analog input pin for the Main system pressure transducer
const int pressureZero = 98.6;                      // analog reading of pressure transducer at 0psi
const int pressureMax = 921.6;                      // analog reading of pressure transducer at 100psi
const int pressuretransducermaxPSI = 300;           // psi value of transducer being used

extern float pressureSensorRead(bool sensorNum);    // main sys = A4, solenoids = A2

#endif