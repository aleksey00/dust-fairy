#include "pressureSensor.h"

float pressureValue = 0.0;                           // variable to store the value coming from the pressure transducer

float pressureSensorRead(bool sensorNum)             // boolean false=sensor Manifold true=sensor Main system
{ 
  if(sensorNum == 0)                                 // Select for Solenoid Manifold sensor
  {
    pressureValue = analogRead(pressureInput);       // reads value from input pin and assigns to variable
  }

  if(sensorNum == 1)                                 // Select for Main System Sensor
  {
    pressureValue = analogRead(pressureInputMain);   // Main system sensor
  }

  pressureValue = ((pressureValue - pressureZero) * pressuretransducermaxPSI) / (pressureMax - pressureZero);     //conversion equation to convert analog reading to psi
  return pressureValue;
}