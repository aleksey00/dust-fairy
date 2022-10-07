#include "solenoids.h"

int analogPins[] = { 2, 4 };                  // an array of Analog Input pins analogPinsSetup()
int pinCount = 2;                             // amount of analog pins in array analogPinsSetup()

int digitalInput[] = { 35, 37, 39 };          // an array of digital Input pins digitalPinsInputSetup()
int digitalInputpinCount = 3;                 // amount of dgital input pins digitalPinsInputSetup()

/* 
   OPEN:          CLOSE:
    41 - E 8"      50 - E 8"
    43 - E 4"      48 - E 4"
    45 - E 6"      46 - E 6"
    47 - T 6"      44 - T 6"
    49 - empty     42 - empty

   Analog Input:
    2 - Solenoid Manifold
    4 - Main Pipeworks

   Digital Input:
    35 - table saw
    37 - manual button
    39 - edgebander
*/

void analogPinsSetup()                        // Analog pin initiated INPUT 2, 4  
{                      
  for (int thisPin = 0; thisPin < pinCount; thisPin++) 
  {
    pinMode(analogPins[thisPin], INPUT);
    // Serial feedback
    Serial.print("Analog pin: A");
    Serial.print(analogPins[thisPin]);
    Serial.println(" INPUT");
  }
}

void digitalPinsSetup(int first, int last)   // Digital pins initiated 41-53 Digital OUTPUT
{  
  for (byte pin = first; pin <= last; pin++)      
  {  
    pinMode(pin, OUTPUT);
    //  Serial feedback 
    Serial.print("Digital pin: ");
    Serial.print(pin);
    Serial.println(" OUTPUT");
  }  
}

void digitalPinsInputSetup(bool serial)      // Digital pin initiated INPUT array digitalInput 36,37,12
{       
  for (int thisPin = 0; thisPin < digitalInputpinCount; thisPin++) 
  {
    pinMode(digitalInput[thisPin], INPUT);
    // Serial feedback
    if(serial == 1) {    
      Serial.print("Digital pin: ");
      Serial.print(digitalInput[thisPin]);
      Serial.println(" INPUT");}
  }
}

void gateTest(int n, int val)                   // method to activate gates with visual feedback to LCD
{
  switch(val)
  {
    case 1:                                     // open Edgebander, close Table-Saw
      solenoidTest(n, 0, 0, 41, "E. 8\"", 1);   // LCD, row, line, solenoid, text, isopen // open
      solenoidTest(n, 9, 0, 43, "4\"", 1);      // LCD, row, line, solenoid, text, isopen // open
      solenoidTest(n, 15, 0, 45, "5\"", 1);     // LCD, row, line, solenoid, text, isopen // open
      solenoidTest(n, 0, 1, 44, "T.Saw", 0);    // LCD, row, line, solenoid, text, isopen // close
      delay(100);
      gateTest(1, 0);
      break;
    case 2:                                     // close Edgebander, open Table-Saw
      solenoidTest(n, 0, 0, 50, "E. 8\"", 0);   // LCD, row, line, solenoid, text, isopen // close
      solenoidTest(n, 9, 0, 48, "4\"", 0);      // LCD, row, line, solenoid, text, isopen // close
      solenoidTest(n, 15, 0, 46, "5\"", 0);     // LCD, row, line, solenoid, text, isopen // close
      solenoidTest(n, 0, 1, 47, "T.Saw", 1);    // LCD, row, line, solenoid, text, isopen // open
      delay(100);
      gateTest(1, 0);
      break;
    case 3:                                     // open ALL
      solenoidTest(n, 0, 0, 41, "E. 8\"", 1);   // LCD, row, line, solenoid, text, isopen // open
      solenoidTest(n, 9, 0, 43, "4\"", 1);      // LCD, row, line, solenoid, text, isopen // open
      solenoidTest(n, 15, 0, 45, "5\"", 1);     // LCD, row, line, solenoid, text, isopen // open
      solenoidTest(n, 0, 1, 47, "T.Saw", 1);    // LCD, row, line, solenoid, text, isopen // open
      digitalWrite(49, HIGH);
      delay(100);
      gateTest(1, 0);
      break;
    case 4:                                     // open only TableSaw
      solenoidTest(n, 0, 1, 47, "T.Saw", 1);    // LCD, row, line, solenoid, text, isopen // open
      delay(100);
      gateTest(1, 0);
      break;
    default:
      for (int thisPin = 41; thisPin <= 50; thisPin++) // turn all solenoids off except 52(OK/STOP) and 51(cooling fan)
      {
        digitalWrite(thisPin, LOW);
      }        
  }
}