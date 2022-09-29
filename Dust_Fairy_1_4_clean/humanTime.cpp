#include "humanTime.h"

void humanTime(int n, unsigned long times, int line, String text, bool visible) 
{
  unsigned long millisec, seconds, minutes, hours;
  if (text == "t") {
    text = "Time ON: ";
  }

  millisec = times % 100;         // how many millisec in seconds
  seconds = times / 1000;         // how many total seconds in millis()
  minutes = seconds / 60;         // how many total minutes
  hours = minutes / 60;           // how many total hours
  seconds = seconds % 60;         // how many seconds in minute
  minutes = minutes % 60;         // how many minutes in hour
  hours = hours % 24;             // how many hours in day 24
  
  if( visible == 1)
  {  
    lcd[n].setCursor(0, line);    // line
    lcd[n].print(text);           // passed text
    if (hours < 10) {             // if less 10 add 0 
      lcd[n].print(F("0"));
    }
    lcd[n].print(hours);
    lcd[n].print(F(":"));
    if (minutes < 10) {           // if less 10 add 0 
      lcd[n].print(F("0"));
    }
    lcd[n].print(minutes);
    lcd[n].print(F(":"));
    if (seconds < 10) {           // if less 10 add 0 
      lcd[n].print(F("0"));
    }
    lcd[n].print(seconds);
    lcd[n].print(F("."));
    if (millisec < 10) {          // if less 10 add 0 
      lcd[n].print(F("0"));
    }
    lcd[n].print(millisec);
  }
}


/* only Serial version */
void humanTimeSerial(unsigned long times) 
{
  // unsigned long times = millis();
  unsigned long millisec, seconds, minutes, hours;

  millisec = times % 100;         // how many millisec in seconds
  seconds = times / 1000;         // how many total seconds in millis()
  minutes = seconds / 60;         // how many total minutes
  hours = minutes / 60;           // how many total hours
  seconds = seconds % 60;         // how many seconds in minute
  minutes = minutes % 60;         // how many minutes in hour
  hours = hours % 24;             // how many hours in day 24
  
  Serial.print(F("Time ON: "));   // serial
  if (hours < 10) {               // if less 10 add 0 
    Serial.print(F("0"));         // serial
  }
  Serial.print(hours);            // serial
  Serial.print(F(":"));           // serial
  if (minutes < 10) {             // if less 10 add 0 
    Serial.print(F("0"));         // serial
  }
  Serial.print(minutes);          // serial
  Serial.print(F(":"));           // serial
  if (seconds < 10) {             // if less 10 add 0 
    Serial.print(F("0"));         // serial
  }
  Serial.print(seconds);          // serial
  Serial.print(F("."));           // serial
  if (millisec < 10) {            // if less 10 add 0 
    Serial.print(F("0"));         // serial
  }
  Serial.println(millisec);       // serial
}