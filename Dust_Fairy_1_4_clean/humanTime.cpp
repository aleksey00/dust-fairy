#include "humanTime.h"

// unsigned int hr, mins, sec;

// 	// convert total seconds to hours, mins, seconds
// 	mins =  secs / 60;	// how many total minutes
// 	hr = mins / 60;		  // how many total hours
// 	mins = mins % 60;	  // how many minutes within the hour
// 	sec = secs % 60;	  // how many seconds within the minute
		
// 	if(hr < 10)
// 		outdev.write('0');
// 	outdev.print((int)hr);
// 	outdev.write(':');
// 	if(mins < 10)
// 		outdev.write('0');
// 	outdev.print((int)mins);
// 	outdev.write(':');
// 	if(sec < 10)
// 		outdev.write('0');
// 	outdev.print((int)sec);

void humanTime(int n, unsigned long times, int line, String text, bool visible) 
{
  // unsigned long times = millis();
  unsigned long millisec, seconds, minutes, hours;
  if (text == "t") {
    text = "Time ON: ";
    }

  millisec = times % 100;       // how many millisec in seconds
  seconds = times / 1000;       // how many total seconds in millis()
  minutes = seconds / 60;       // how many total minutes
  hours = minutes / 60;         // how many total hours
  seconds = seconds % 60;       // how many seconds in minute
  minutes = minutes % 60;       // how many minutes in hour
  hours = hours % 24;           // how many hours in day 24
  
  if( visible == 1)
  {  
    lcd[n].setCursor(0, line);      // line
    lcd[n].print(text);
    Serial.print(F("Time ON: "));   // serial
    if (hours < 10) {               // if less 10 add 0 
      lcd[n].print(F("0"));
      Serial.print(F("0"));         // serial
    }
    lcd[n].print(hours);
    lcd[n].print(F(":"));
    Serial.print(hours);            // serial
    Serial.print(F(":"));           // serial
    if (minutes < 10) {             // if less 10 add 0 
      lcd[n].print(F("0"));
      Serial.print(F("0"));         // serial
    }
    lcd[n].print(minutes);
    lcd[n].print(F(":"));
    Serial.print(minutes);          // serial
    Serial.print(F(":"));           // serial
    if (seconds < 10) {             // if less 10 add 0 
      lcd[n].print(F("0"));
      Serial.print(F("0"));         // serial
    }
    lcd[n].print(seconds);
    lcd[n].print(F("."));
    Serial.print(seconds);          // serial
    Serial.print(F("."));           // serial
    if (millisec < 10) {            // if less 10 add 0 
      lcd[n].print(F("0"));
      Serial.print(F("0"));         // serial
    }
    lcd[n].print(millisec);
    Serial.println(millisec);       // serial
  }
}