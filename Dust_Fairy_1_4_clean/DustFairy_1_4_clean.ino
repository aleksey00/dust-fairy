/*
MIT License

Copyright (c) 2022 Aleksey Khoroshilov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software. 
Original sticker with Dust Fairy logo shall be placed on final build.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Wire.h>
#include "startLCD.h"         // lcdSetup(), lcdClear(), dashedLine(), warningMessage(), pressureDisplay(), lowTempCheck(), highTempCheck(), lowPressureCheck(), lowPressureWarning(), solenoidTest(), systemOK()
#include "solenoids.h"        // analogPinsSetup(), digitalPinsSetup(), gateTest(), gates(), manualOverrride()
#include "TempSensor.h"       // tempSensor(), tempReading(), fanOn()
#include "pressureSensor.h"   // pressureSensorRead()
#include "firstRun.h"         // firstRunFunc(), testRunEven(), testRunNotEven(), testRun()
#include "vacuum.h"           // vacOperate(), vacuumFunction()
#include "humanTime.h"        // humanTime(), humanTimeSerial()

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

   LCD 0
    Time ON displayed via humanTime()
    Solenoid plate pressure displayed via pressureDisplay()
    Main system pipe pressure displayed via pressureDisplay()
    Temperature displayed via tempReading()

   LCD 1
     Edgebander Gates displayed via solenoidTest()
     Table Saw gates displayed via solenoidTest() + Manual override displayed via manualOverrrideBluebutton()
     Dust Collector ON/OFF displayed via vacOperate()
     Dust Collector runtime displaeyed via vacuumFunction()
*/

void setup() {

  Wire.begin();              // Initialize the Wire library and join the I2C bus
  Serial.begin(9600);        // Initialize Serial Connection
  lcdSetup();                // Initialize I2C LCD screens _startLCD.
  tempSetup();               // Initialize I2C temp Sensor _tempSensor.
  digitalPinsSetup(41,53);   // Initialize Digital Pins INPUT 41 - 53 _solenoids.
  analogPinsSetup();         // Initialize Analog Pins IPNUT 2, 4 _solenoids.
  digitalPinsInputSetup(1);  // bool Serial feedback // Initialize Digital Pins INPUT 35, 37, 39
  testRun();                 // activate all close solenoids then all open solenoids and give OK light after
  
}

void loop() {
    
  /* Pressure sensors */
  float pressureValue = pressureSensorRead(0);              // sensor for solenoid manifold base
  float pressureValueMain = pressureSensorRead(1);          // sensor for the main system

  lowPressureCheck(pressureValue, 28);                      // (set to 30)psi value, <= value // warning message if press is less than 40 _startLCD.
  lowPressureCheck(pressureValueMain, 80);                  // (set to 60)psi value, <= value // warning message if press is less than 60 in main _startLCD.

  highTempCheck(tempsensor.readTemperature(), 60);          // temp value, >= value // warning message when temp is over 60 _startLCD.
  lowTempCheck(tempsensor.readTemperature(), 15);           // temp value, <= value // warning message when temp below 15 _startLCD.

  fanOn(51, 27, 29);                                        // (solenoid, off temp, on temp) turn on fan if temp is over 50 and off when drops below 30 _tempSensor.
  systemOK(pressureValue, pressureValueMain, 28, 80);       // int pressureInput, int pressureInputMain, int value1, int value2 // keep green light on _startLCD

  /* LCD 0 */
  humanTime(0, millis(), 0, "t", 1);                        // LCD, millis(), LCD line, text, show // time to LCD _humanTime.
  pressureDisplay(0, "Solenoids:  ", pressureValue, 1);     // LCD, psi, LCD line, show // psi to LCD _startLCD.
  pressureDisplay(0, "Main pipe: ", pressureValueMain, 2);  // LCD, psi Main, LCD line, show // psi to LCD _startLCD.
  tempReading(0, 3);                                        // LCD, LCD line // temp to LCD  _tempSensor.

  /* LCD 1
     Edgebander Gates displayed via solenoidTest()
     Table Saw gates displayed via solenoidTest() + Manual override displayed via manualOverrrideBluebutton()
     Dust Collector ON/OFF displayed via vacOperate()
     Dust Collector runtime displaeyed via vacuumFunction()
  */

  vacuumFunction(1);                                        // LCD // dust collection and gates operation
}

