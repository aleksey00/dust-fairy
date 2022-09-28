#include "vacuum.h"

// VacuumFunction
const byte blueButton = 37;                           // blue button pin
// int blueButtonState = 0;
unsigned long preMillis = millis();
unsigned long curMillis = 0;
int buttonFlag = 0;

const byte edgebanderAuto = 39;                       // edgebander opti pin
const byte tableSawAuto = 35;                         // table saw opti pin
int passFlagTS, passFlagBB, passFlagEB, passFlagEBTS = 0;


void vacOperate(int n, bool activate)         // activate dust collectot with info on LCD 1=on, 0=off
{
  if (activate == 1) {
    lcd[n].setCursor(0,2);
    lcd[n].print(F("Dust Collector: ON  "));
    digitalWrite(53, HIGH);
  }
  if (activate == 0) {
    lcd[n].setCursor(0,2);
    lcd[n].print(F("Dust Collector:  OFF"));
    digitalWrite(53, LOW);
  }
}


void vacuumFunction(int n)
{
  // pass all function to operate vacuum
  // if button is pressed then add "Manual ON"
  // LOW = activated, HIGH = not active
  if ( digitalRead(tableSawAuto) == LOW | digitalRead(edgebanderAuto) == LOW | digitalRead(blueButton) == LOW ) // table saw or edgebander or blue button active
  {
    if (curMillis == 0)                             // if first run then assign values to pre&curMillis
    {
      preMillis = millis();
      curMillis = millis();      
    }
    if (buttonFlag == 0)                            // if button was pressed already update preMillis value + button flag
    {
      preMillis = millis();
      buttonFlag = 1;                       
    }
    curMillis = millis();
    unsigned long pressed = curMillis - preMillis;  // timer value

    vacOperate(1, 1);                               // Turn On Vacuum
    humanTime(1, pressed, 3, "Runtime: ", 1);          // Display timer on


    if( digitalRead(blueButton) == LOW )       // blue button active only display info
    {    
      /* Manual override info LCD */
      lcd[n].setCursor(9,1);
      lcd[n].print("Manual ");
      lcd[n].print("YES ");

      passFlagBB = 0; // not sure if this needed //
    }

    if( digitalRead(tableSawAuto) == LOW )      // table saw active
    {    
      if( passFlagTS == 0 )
      { 
        gateTest(1, 2); // table saw
        passFlagTS++;
      }
    }

    if( digitalRead(edgebanderAuto) == LOW )    // edgebander active
    {    
      if( passFlagEB == 0 )
      { 
        gateTest(1, 1); // edgebander
        passFlagEB++;
        // passFlagTS = 0;
      }
    }
    
    if( digitalRead(edgebanderAuto) == LOW && digitalRead(tableSawAuto) == LOW ) // table saw + edgebander active
    {
      if( passFlagEBTS == 0 )
      { 
        gateTest(1, 3);         // all open
        passFlagEBTS = 1;
      }
    }

    // passFlagBB = 0;             // for blue button unsure if needed //

  }

  if (passFlagEBTS == 1)
  { 
    if( digitalRead(edgebanderAuto) == HIGH)
    {
      passFlagEB = 0;
      passFlagEBTS = 0;
      passFlagTS = 0;
    }

    if( digitalRead(tableSawAuto) == HIGH)
    {
      passFlagTS = 0;
      passFlagEBTS = 0;
      passFlagEB = 0;
    }
  }

  if ( (digitalRead(blueButton) == HIGH && digitalRead(edgebanderAuto) == HIGH && digitalRead(tableSawAuto) == HIGH) )
  {
    if(buttonFlag == 1)
    {
      vacOperate(1, 0);               // turn off dust collector
      buttonFlag = 0;
      lcd[n].setCursor(0,3);
      lcd[n].print("Last Run");

      passFlagTS = 0;
      passFlagEB = 0;
      passFlagEBTS = 0;

      gateTest(1,3);                  // all open
      passFlagBB++;

      // if(passFlagBB == 0) /// very quetionable but needed for gate to open after both machines turned on and off. 
      // {
      //   gateTest(1,3);                // all open
      //   passFlagBB++;
      // }
    }
  }

  if ( digitalRead(blueButton) == HIGH )
  {
      /* Manual override info LCD */
      lcd[n].setCursor(9,1);
      lcd[n].print("Manual ");
      lcd[n].print("  NO");
  }

}