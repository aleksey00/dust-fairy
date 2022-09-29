#include <Wire.h>
#include "startLCD.h"
#include "solenoids.h"
#include "TempSensor.h"
#include "pressureSensor.h"
#include "firstRun.h"
#include "vacuum.h"
#include "humanTime.h"

/* 
   OPEN:          CLOSE:
    41 - E 8"      50 - E 8"
    43 - E 4"      48 - E 4"
    45 - E 6"      46 - E 6"
    47 - T 6"      44 - T 6"
    49 - empty     42 - empty

   Analog Input:
    2 - Solenoid Manifold Pressure Sensor
    4 - Main Pipeworks Pressure Sensor

   Digital Input:
    35 - edgebander
    37 - manual button
    39 - table saw
*/

const byte button1 = 13;
const byte button2 = 12;
int delayFlag = 0;

void setup() {

  Wire.begin();              // Initialize the Wire library and join the I2C bus
  Serial.begin(9600);        // Initialize Serial Connection

  lcdSetup();                // Initialize I2C LCD screens _startLCD.
  tempSetup();               // Initialize I2C temp Sensor _tempSensor.

  digitalPinsSetup(41,53);   // Initialize Digital Pins INPUT 41 - 53 _solenoids.
  analogPinsSetup();         // Initialize Analog Pins IPNUT 2, 4 _solenoids.
  digitalPinsInputSetup(1);  // bool Serial feedback // Initialize Digital Pins INPUT 35, 37, 39

  testRun();                 // activate all close solenoids then all open solenoids and give OK light after

  // firstRunFunc(0,200,200,700);    // int LCD, int sensOpen, int sensClose, int vacTest
}


void printAllAnalog()             // function designed to test real time value in Analog inputs
{
  for (byte i = 0; i < NUM_ANALOG_INPUTS; i++) 
  {
    Serial.print('A');
    Serial.print(i);
    Serial.print('=');
    Serial.print(analogRead(A0+i));
    Serial.print(' ');
  }
  Serial.println();
}


void loop() {
    
  // printAllAnalog();                                               // Read real-time analog values

  /* Pressure sensors */
  float pressureValue = pressureSensorRead(0);                    // sensor for solenoid manifold base
  float pressureValueMain = pressureSensorRead(1);                // sensor for the main system

/*  temporarily disbled average values for pressure    */
  // float pressureValueAverage;                                     // averager for baseplate sensor
  // float pressureValueAverageMain;                                 // averager for main system sensor

  // pressureValueAverage = averager(pressureValue, 10);             // 200 (10)
  // pressureValueAverageMain = averager(pressureValueMain, 100);    // 200 (10)

  lowPressureCheck(pressureValue, 28);                     // (set to 30)psi value, <= value // warning message if press is less than 40 _startLCD.
  lowPressureCheck(pressureValueMain, 80);                 // (set to 60)psi value, <= value // warning message if press is less than 60 in main _startLCD.

  highTempCheck(tempsensor.readTemperature(), 60);                // temp value, >= value // warning message when temp is over 60 _startLCD.
  lowTempCheck(tempsensor.readTemperature(), 15);                 // temp value, <= value // warning message when temp below 15 _startLCD.

  fanOn(51, 35, 40);                                              // (solenoid, off temp, on temp) turn on fan if temp is over 50 and off when drops below 30 _tempSensor.
  systemOK(pressureValue, pressureValueMain, 28, 80);             // int pressureInput, int pressureInputMain, int value1, int value2 // keep green light on _startLCD

  // LCD 0
  humanTime(0, millis(), 0, "t", 1);                                 // LCD, millis(), LCD line, text, show // time to LCD _humanTime.
  pressureDisplay(0, "Solenoids:  ", pressureValue, 1);           // LCD, psi, LCD line, show // psi to LCD _startLCD.
  pressureDisplay(0, "Main pipe: ", pressureValueMain, 2);        // LCD, psi Main, LCD line, show // psi to LCD _startLCD.
  tempReading(0, 3);                                              // LCD, LCD line // temp to LCD  _tempSensor.

  // LCD 1
  // Edgebander Gates displayed via solenoidTest()
  // Table Saw gates displayed via solenoidTest() + Manual override displayed via manualOverrrideBluebutton()
  // Dust Collector ON/OFF displayed via vacOperate()
  // Dust Collector runtime displaeyed via vacuumFunction()

/* gates and manualOverride disblaed for testing */
  // gates(1, 'k');            // LCD, Serial input // switch case for solenoids _solenoids

  // manualOverrride(1, 'a');

  // dustCollector(8);         // Serial input // 



  vacuumFunction(1);


  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  // if (digitalRead(blueButton) == HIGH && buttonFlag == 2) 
  // {
  //   lcdClear(1, 3);
  //   vacOperate(0);
  //   buttonFlag = 0;
  //   // if(delayFlag == 0)
  //   // {
      
  //   // }
  // } 
  // else 
  // {
  //   if(buttonFlag == 0)
  //   {
  //     preMillis = curMillis;          // preMill=millis() curMillis = 0 // millis() = 0
  //     buttonFlag++;
  //   }
  //   curMillis = millis();
  //   unsigned long pressed = curMillis - preMillis;
  //   vacOperate(1);                    // vdust collection on with LCD info
  //   humanTime(1, pressed, 3);
  //   // vacOperate();

  // }

  // void vacOffDelay();

  // dustCollector(1);
}



// #pragma once










float averager(float inputValue, int averageAmt) {
  float averageValue = 0;
  for (int i = 0; i < averageAmt; i++) {
    averageValue = averageValue + inputValue;
    delay(1);
  }
  // averageValue = (averageValue * (averageAmt-1) + inputValue) / averageAmt;
  averageValue = averageValue / averageAmt;
  
  return averageValue;
}

int averagerInt(float inputValue, int averageAmt){
  int averageValue = round(inputValue);
  int counter = 0;
  for (int i = 0; i < averageAmt; i++){
    averageValue = averageValue + inputValue;
  }
  averageValue = averageValue / averageAmt;
  return averageValue;
}


void solenoidDA(int solenoid, int period) {
  digitalWrite(solenoid, HIGH);
  delay(period);
  digitalWrite(solenoid, LOW);
}

