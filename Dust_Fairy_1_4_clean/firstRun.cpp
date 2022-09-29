#include "firstRun.h"

// see pin layout in solenoids.h

void testRun()                               // print to LCD and activate all open gate solenoids
{
  digitalWrite(52, HIGH);                    // Red STOP light
  solenoidTest(1, 0, 0, 50, "E. 8\"", 0);    // LCD, row, line, solenoid, text, isopen
  solenoidTest(1, 9, 0, 48, "4\"", 0);       // LCD, row, line, solenoid, text, isopen
  solenoidTest(1, 15, 0, 46, "5\"", 0);      // LCD, row, line, solenoid, text, isopen
  solenoidTest(1, 0, 1, 44, "T.Saw", 0);     // LCD, row, line, solenoid, text, isopen
  digitalWrite(42, HIGH);
  delay(300);
  for (int pin = 41; pin <= 51; pin++)       // deactivate pins
  {
    digitalWrite(pin, LOW);
  }
  solenoidTest(1, 0, 0, 41, "E. 8\"", 1);    // LCD, row, line, solenoid, text, isopen
  solenoidTest(1, 9, 0, 43, "4\"", 1);       // LCD, row, line, solenoid, text, isopen
  solenoidTest(1, 15, 0, 45, "5\"", 1);      // LCD, row, line, solenoid, text, isopen
  solenoidTest(1, 0, 1, 47, "T.Saw", 1);     // LCD, row, line, solenoid, text, isopen
  digitalWrite(49, HIGH);
  vacOperate(1, 0);                          // LCD, on/off // vaccum off
  // first run bottom line of LCD 1
  lcd[1].setCursor(0,3);
  lcd[1].print(F("DUST FAIRY IS ALIVE!"));
  delay(800);                                // delay 

  for (int pin = 41; pin <= 53; pin++)       // deactivate ALL pins
  {
    digitalWrite(pin, LOW);
  }
  
}

/* Not used in the main program */

void firstRunFunc(int n, int sensOpen, int sensClose, int vacTest) {    // sequential solenoid test uses testRunEven() and testRunNotEven

  lcd[n].clear();

  testRunNotEven(n, HIGH, 300);
  testRunNotEven(n, LOW, 300);
  testRunEven(n, HIGH, 300);
  testRunEven(n, LOW, 300);

  lcd[n].print("Self Test Complete");
  delay(500);    
  lcd[n].clear();

  if (n == 0){
    lcd[n+1].clear();
  }
  if (n > 0){
    lcd[n-1].clear();
  }

}

void testRunEven(int n, char value, int time){                          // test run of even relays (lcd, HIGH or LOW, delay)
  for (byte pin = 41; pin <= 53; pin++)
  {
    if (pin % 2 == 0) 
    {
        lcd[n].setCursor(0,0);
        lcd[n].print("42 44 46 48 50 52");
        lcd[n].setCursor(0,1);
        lcd[n].print("Testing Relay: ");  
        lcd[n].print(pin);


      digitalWrite(pin, value);
      delay(time);
    }
  }
  lcd[n].clear();
}

void testRunNotEven(int n, char value, int time){                     // test run of non-even relays (lcd, HIGH or LOW, delay)
  for (byte pin = 41; pin <= 53; pin++)
  {
    if (pin % 2 != 0) 
    {
        lcd[n].setCursor(0,0);
        lcd[n].print("41 43 45 47 49 51 53");
        lcd[n].setCursor(0,1);
        lcd[n].print("Testing Relay: ");
        lcd[n].print(pin);
      
      digitalWrite(pin, value);
      delay(time);
    }
  }
  lcd[n].clear();
}

