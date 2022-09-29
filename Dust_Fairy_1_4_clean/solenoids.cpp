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

void analogPinsSetup() {                      // Analog pin initiated INPUT 2, 4  
  for (int thisPin = 0; thisPin < pinCount; thisPin++) 
  {
    pinMode(analogPins[thisPin], INPUT);
    // Serial feedback
    Serial.print("Analog pin: A");
    Serial.print(analogPins[thisPin]);
    Serial.println(" INPUT");
  }
}

void digitalPinsSetup(int first, int last) {  // Digital pins initiated 41-53 Digital OUTPUT
  for (byte pin = first; pin <= last; pin++)      
  {  
    pinMode(pin, OUTPUT);
    //  Serial feedback 
    Serial.print("Digital pin: ");
    Serial.print(pin);
    Serial.println(" OUTPUT");
  }  
}


void digitalPinsInputSetup(bool serial) {       // Digital pin initiated INPUT array digitalInput 36,37,12
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
    default:
      for (int thisPin = 41; thisPin <= 51; thisPin++) // turn all solenoids off except 52(OK/STOP)
      {
        digitalWrite(thisPin, LOW);
      }        
  }
}


/* serial input via USB to test gates */

void gates(int n, int inByte){

    if (Serial.available() > 0) {

    int inByte = Serial.read();      
    int time = 100;
    
    // do something different depending on the character received.
    // The switch statement expects single number values for each case; in this
    // example, though, you're using single quotes to tell the controller to get
    // the ASCII value for the character. For example 'a' = 97, 'b' = 98,
    // and so forth:

    switch (inByte) {
      case 'a':
        // lcd[n].clear();
        // lcd[n].setCursor(0, line);
        // lcd[n].print("Gate 1 ");
        // lcd[n].print(char(6));
        // lcd[n].print(char(8));
        // lcd[n].print(char(5));
        // lcd[n].print(char(7));
        // Serial.print("Case a");
        // digitalWrite(41, HIGH);
        // lcdClear(n, 0);
        solenoidTest(n, 0, 0, 41, "E. 8\"", 1); // LCD, row, line, solenoid, text, isopen
        delay(time);
        gates(1, 0);
        break;
      case 'b':
        solenoidTest(n, 0, 0, 50, "E. 8\"", 0); // LCD, row, line, solenoid, text, isopen
        // lcd[n].clear();
        // lcd[n].setCursor(0, line);
        // lcd[n].print("Gate 1 ");
        // lcd[n].print(char(6));
        // lcd[n].print(char(4));
        // lcd[n].print(char(9));
        // lcd[n].print(char(7));
        // digitalWrite(42, HIGH);
        delay(time);
        gates(1, 0);
        break;
      case 'c':
        solenoidTest(n, 9, 0, 43, "4\"", 1); // LCD, row, line, solenoid, text, isopen
        delay(time);
        gates(1, 0);
        break;
      case 'd':
        solenoidTest(n, 9, 0, 48, "4\"", 0); // LCD, row, line, solenoid, text, isopen
        delay(time);
        gates(1, 0);
        break;
      case 'e':
        solenoidTest(n, 15, 0, 45, "5\"", 1); // LCD, row, line, solenoid, text, isopen
        delay(time);
        gates(1, 0);
        break;
      case 'f':
        solenoidTest(n, 15, 0, 46, "5\"", 0); // LCD, row, line, solenoid, text, isopen
        delay(time);
        break;
      case 'g':                                 // open Edgebander
        solenoidTest(n, 0, 0, 41, "E. 8\"", 1); // LCD, row, line, solenoid, text, isopen // open
        solenoidTest(n, 9, 0, 43, "4\"", 1);    // LCD, row, line, solenoid, text, isopen // open
        solenoidTest(n, 15, 0, 45, "5\"", 1);   // LCD, row, line, solenoid, text, isopen // open
        delay(time);
        gates(1, 0);
        break;
      case 'h':                                 // close Edgebander
        solenoidTest(n, 0, 0, 50, "E. 8\"", 0); // LCD, row, line, solenoid, text, isopen // close
        solenoidTest(n, 9, 0, 48, "4\"", 0);    // LCD, row, line, solenoid, text, isopen // close
        solenoidTest(n, 15, 0, 46, "5\"", 0);   // LCD, row, line, solenoid, text, isopen // close
        delay(time);
        gates(1, 0);
        break;
      case 'i':
        solenoidTest(n, 0, 1, 47, "T.Saw", 1); // LCD, row, line, solenoid, text, isopen
        // solenoidTest(n, 9, 1, 43, "Manual  ", 1); // LCD, row, line, solenoid, text, isopen
        lcd[n].setCursor(9,1);
        lcd[n].print("Manual: ");
        lcd[n].print(" NO");
        // solenoidTest(n, 15, 0, 45, "5\"", 0); // LCD, row, line, solenoid, text, isopen
        // digitalWrite(46, HIGH);
        delay(time);
        gates(1, 0);
        break;
      case 'j':
        solenoidTest(n, 0, 1, 44, "T.Saw", 0); // LCD, row, line, solenoid, text, isopen
        lcd[n].setCursor(9,1);
        lcd[n].print("Manual: ");
        lcd[n].print(" NO");      
        delay(time);
        gates(1,0);
        break;
      case 'k':
        lcd[n].setCursor(0,2);
        lcd[n].print("Dust Collector:");
        lcd[n].setCursor(15, 2);
        lcd[n].print(" ON  ");
        digitalWrite(53, HIGH);
        // vacOperate(1, 1);
        // dustCollector('1');
        delay(time);
        gates(1, 0);
        break;
      case 'l':
        lcd[n].setCursor(0,2);
        lcd[n].print("Dust Collector:");
        lcd[n].setCursor(15, 2);
        lcd[n].print("  OFF");
        digitalWrite(53, LOW);
        delay(time);
        break;
      case 'm':                                 // open Edgebander, close Table-Saw
        solenoidTest(n, 0, 0, 41, "E. 8\"", 1); // LCD, row, line, solenoid, text, isopen // open
        solenoidTest(n, 9, 0, 43, "4\"", 1);    // LCD, row, line, solenoid, text, isopen // open
        solenoidTest(n, 15, 0, 45, "5\"", 1);   // LCD, row, line, solenoid, text, isopen // open
        solenoidTest(n, 0, 1, 44, "T.Saw", 0);  // LCD, row, line, solenoid, text, isopen // close
        delay(time);
        gates(1, 0);
        break;
      case 'n':                                 // close Edgebander, open Table-Saw
        solenoidTest(n, 0, 0, 50, "E. 8\"", 0); // LCD, row, line, solenoid, text, isopen // close
        solenoidTest(n, 9, 0, 48, "4\"", 0);    // LCD, row, line, solenoid, text, isopen // close
        solenoidTest(n, 15, 0, 46, "5\"", 0);   // LCD, row, line, solenoid, text, isopen // close
        solenoidTest(n, 0, 1, 47, "T.Saw", 1);  // LCD, row, line, solenoid, text, isopen // open
        delay(time);
        gates(1, 0);
        break;
      case 'o':                                 // open ALL
        solenoidTest(n, 0, 0, 41, "E. 8\"", 1); // LCD, row, line, solenoid, text, isopen // open
        solenoidTest(n, 9, 0, 43, "4\"", 1);    // LCD, row, line, solenoid, text, isopen // open
        solenoidTest(n, 15, 0, 45, "5\"", 1);   // LCD, row, line, solenoid, text, isopen // open
        solenoidTest(n, 0, 1, 47, "T.Saw", 1);  // LCD, row, line, solenoid, text, isopen // open
        digitalWrite(49, HIGH);
        delay(time);
        gates(1, 0);
        break;
      case 'p':
        lcd[n].setCursor(0,2);
        lcd[n].print("Dust Collector");
        lcd[n].setCursor(15, 2);
        lcd[n].print("  OFF");
        digitalWrite(53, LOW);
        delay(time);
        break;
      case 'x':
        for (int thisPin = 41; thisPin <= 52; thisPin++) 
        {
          digitalWrite(thisPin, LOW);
        }
        break;
      default:
        // turn all realys off:
        for (int thisPin = 41; thisPin <= 52; thisPin++) 
        {
          digitalWrite(thisPin, LOW);
        }        
        Serial.print("End");
        Serial.print("\n");
    }
  }
}

void manualOverrride(int n, int inByte){
  if (Serial.available() > 0) {

    int inByte = Serial.read();      
    int time = 100;
    
    // do something different depending on the character received.
    // The switch statement expects single number values for each case; in this
    // example, though, you're using single quotes to tell the controller to get
    // the ASCII value for the character. For example 'a' = 97, 'b' = 98,
    // and so forth:

    switch (inByte) {
      case 'a':
        lcd[n].setCursor(9,1);
        lcd[n].print("Manual:");
        lcd[n].print("  NO");      
        gates(1, 'n');
        break;
      case 'b':
        lcd[n].setCursor(9,1);
        lcd[n].print("Manual:");
        lcd[n].print("YES ");      
        gates(1, 'm');
        break;
      // default:
        
    }
  }
  
}

