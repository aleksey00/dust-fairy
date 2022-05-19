#include <Wire.h>
#include <Arduino.h>
//temperature sensor
const byte tempPin = A0;  //the thermistor
#define beta 4090         //the beta of the thermistor
#define resistance 10     //the value of the pull-up resistor

