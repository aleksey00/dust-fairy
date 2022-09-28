#ifndef STARTLCD_H
#define STARTLCD_H

#include "Arduino.h"
#include <Wire.h>                                 // include for Arduino functionality
#include <hd44780.h>                              // hd44780 library for I2C LCD
#include <hd44780ioClass/hd44780_I2Cexp.h>        // i2c expander i/o class header
#include "humanTime.h"


extern hd44780_I2Cexp lcd[2];                     // auto locate & configure up to 16 displays

extern void lcdSetup();                                                       // lcd in void setup()
extern void lcdClear(int n, int line);                                        // clear lcd line with spaces
extern void dashedLine(int n, int len);                                       // dashed line
extern void warningMessage(int n, String text, float value);                  // generic warning message
// extern void infoDisplay(float celcius, float fahrenheit, float psi);
// extern void tempDisplay(int n, float celcius, float fahrenheit, int line);    // temp dispaly C and F
extern void pressureDisplay(int n, String input, float psi, int line);        // LCD, text, PSI, line // pressure dispaly [Pressure:   88.8 psi]

extern void lowTempCheck(float temp, int value);
extern void highTempCheck(float temp, int value);
extern void lowPressureCheck(float pressure, int value);
extern void lowPressureWarning(int n,float pressure);


extern void solenoidTest(int n, int row, int line, int solenoid, String text, bool isopen);          // test function for lcd 1 display
extern void systemOK(int pressureInput, int pressureInputMain, int value1, int value2);     // light green OK light if pressures ok

#endif

/*           
 *   hd44780_I2Cexp lcd0(0x26, 20, 4);
 *   hd44780_I2Cexp lcd1(0x27, 20, 4);     
 *   thermistor address (0x40)
 */