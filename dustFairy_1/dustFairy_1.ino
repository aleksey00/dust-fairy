#include <EmonLib.h>
EnergyMonitor emon1;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "LCD_Init.h"
#include "TempSensor.h"
#include "solenoids.h"
#include "PressureSensor.h"
#include "firstRun.h"
#include "vacuum.h"

void setup(){

  lcd.init();
  lcd.backlight();

  pinMode(solenoid1, OUTPUT); //SawBlade Close
  pinMode(solenoid2, OUTPUT); //SawBlade Open
  pinMode(solenoid3, OUTPUT); //EdgeBander Close
  pinMode(solenoid4, OUTPUT); //EdgeBander Open
  pinMode(vacuum, OUTPUT); //Dust-collector solenoid

  // firstRun(150, 200, 1000); //SensOpen, SensClose, Vacuum solenoid
  // emon1.current(3, 69.1);  
  emon1.current(3, 111.1);  
}

void loop(){

  //***********************Temp Sensor Calc + Pin**************//
  long a = analogRead(tempPin);
  //the calculating formula of temperature
  float tempC = beta / (log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
  float tempF = 1.8 * tempC + 32.0;
  //***********************************************************//

  //pressure sensor begin
  pressureValue = analogRead(pressureInput); //reads value from input pin and assigns to variable
  pressureValue = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); //conversion equation to convert analog reading to psi

  // current sensor begin
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only

  lcd.setCursor(0,2);
  lcd.print((Irms)*122.3);
  lcd.print("     ");

  lcd.setCursor(6,2);
  lcd.print("Watt");

  lcd.setCursor(12,2);
  lcd.print(Irms);
  lcd.print("    ");
  lcd.setCursor(17,2);
  lcd.print("Amp");
  //current sensor END

  float tempCAv;
  float tempFAv;
  float pressureValueAverage;
  tempCAv = averager(tempC, 20);  // input, average sample
  tempFAv = averager(tempF, 100);
  pressureValueAverage = averager(pressureValue, 200);

  infoDisplay(tempCAv, tempFAv, pressureValueAverage);
  // gateDelay();
  humanTime();
  // lowPressureWarning(pressureValueAverage);
  lowPressureCheck(pressureValueAverage, -1); // low <=
  highTempCheck(tempCAv, 33); // high >=
  lowTempCheck(tempCAv, 15);

  vacDelay(tempCAv);

}

// #pragma once



void dashedLine(int len) {
  int i;
  for (i = 0; i < len; i++) {
    lcd.print("*");
  }
}

void warningMessage(String text, float value){
  int stringLength = text.length();
  int starCount = ((( 20 - (stringLength) ) /2 ) - 1);

  lcd.clear();
  lcd.setCursor(0,0);
  dashedLine(20);

  lcd.setCursor(0,1);
  dashedLine(starCount);
  lcd.print(" ");
  lcd.print(text);
  lcd.print(" ");

  if (stringLength%2){ //check if odd, then add 1 star
    starCount = starCount + 1;
  }
  dashedLine(starCount);

  lcd.setCursor(0,2);
  dashedLine(20);

  lcd.setCursor(8,3);    
  lcd.print(value,2);
  delay(1000);
  lcd.clear();    

}

void lowTempCheck(float temp, int value){
  if (temp <= value){
    warningMessage("TEMP LOW", temp);
  }
}

void highTempCheck(float temp, int value){
  if (temp >= value){
    warningMessage("TEMP HIGH", temp);
  }
}

void lowPressureCheck(float pressure, int value){
  if (pressure < value){
    warningMessage("PRESSURE LOW", pressure);
  }
}

// void lowPressureWarning(float pressure){
//     if (pressure < 5){
//     lcd.clear();
//     // lcd.home();
//     lcd.setCursor(0,0);
//     dashedLine(20);
//     // lcd.print("********************");
//     lcd.setCursor(0,1);
//     dashedLine(3);
//     lcd.print(" PRESSURE LOW ");
//     dashedLine(3);
//     lcd.setCursor(0,2);
//     dashedLine(20);
//     // lcd.print("********************");
//     lcd.setCursor(5,3);
//     lcd.print("PSI: ");    
//     lcd.print(pressure,2);
//     delay(1000);
//     lcd.clear();    
//   }
// }

void humanTime(){

  unsigned long times = millis();
  unsigned long millisec  = times % 100;
  unsigned long tseconds = times / 1000;
  unsigned long seconds = tseconds % 60;
  unsigned long tminutes = tseconds / 60;  
  unsigned long minutes = tminutes % 60;
  unsigned long thours = tminutes / 60;
  unsigned long hours = thours % 24;
  // lcd.setCursor(0,2); // line 3
  lcd.setCursor(0,1); // line 2
  lcd.print("Time ON: ");
    if(thours < 10){
    lcd.print("0");
    }
  lcd.print(thours);
  lcd.print(":");
    if(minutes < 10){
      lcd.print("0");
    }
  lcd.print(minutes);
  lcd.print(":");
    if(seconds < 10){
    lcd.print("0");
    }
  lcd.print(seconds);
  lcd.print(".");
  lcd.print(millisec);
 
}

void infoDisplay(float celcius, float fahrenheit, float psi ){
  //LINE 1
  //Temperature Display
  lcd.setCursor(0, 0); // set the cursor to column 0, line 0
  lcd.print("Temp");// Print a message of "Temp: "to the LCD.
  lcd.setCursor(5, 0);
  lcd.print(celcius);
  lcd.setCursor(10, 0);
  lcd.print(char(223));//print the unit" ℃ "
  lcd.setCursor(11, 0);
  lcd.print("C");
  lcd.setCursor(12, 0);
  lcd.print("(");
  lcd.setCursor(13, 0);
  lcd.print(fahrenheit);// Print a Fahrenheit temperature to the LCD.
  lcd.setCursor(18, 0);
  lcd.print("F)"); // Print the unit of the Fahrenheit temperature to the LCD.
  delay(100); //wait for 100 milliseconds
  
  //LINE 2
  //Time Run Display
  // lcd.setCursor(0, 1); // set the cursor to column 0, line 1
  // lcd.print("Time Run: ");
  // long timeRun = ((millis()/1000));
  // lcd.print(timeRun);

  //LINE 3

  
  //LINE 4
  //Pressure Sensor Display
  lcd.setCursor(0,3); //sets cursor to column 0, row 0
  lcd.print("Pressure:"); //prints label
  lcd.setCursor(12,3);
  lcd.print(psi, 1); //prints pressure value to lcd screen, 1 digit on float
  lcd.print("  "); //to clear the display after large values or negatives
  lcd.setCursor(17,3);
  lcd.print("psi"); //prints label after value
  
}

float averager (float inputValue, int averageAmt) {
  float averageValue = 0;
    for ( int i=0; i < averageAmt; i++ ) {
      averageValue = averageValue + inputValue;
    }
  averageValue = averageValue / averageAmt;
  return averageValue;
}



void solenoidSingleAction (int solenoid, bool status){
  if (status){
    status = "HIGH";
  } else {
    status = "LOW";
  }
  digitalWrite(solenoid, status);
}

void solenoidDA (int solenoid, int period){
  digitalWrite(solenoid, HIGH);
  delay(period);
  digitalWrite(solenoid, LOW);
}


void vacDelay(float temp){ 

  unsigned long currentTime = millis();
    
  if ( temp > 29 && VD == 0 ){ //vacuum ON
    vacStartTime = currentTime;
    digitalWrite(vacuum, HIGH);
    VD++;
    VD1 = 0;
    VOR = 0; // reset this value when gate opens for delay off function to work
  }
  
  if ( temp < 29 && VD1 == 0  ){ //vacuum OFF

    if (VOR == 0){
    vacOffRequest = currentTime;
    VOR++;
    }

    if ( currentTime - vacStartTime >= eventDelay)  { //safety delay timer
      if ( currentTime - vacOffRequest > eventDelay) { //turn off delay timer
        digitalWrite(vacuum, LOW);
        VD1++;
        VD = 0;
        VOR = 0;
      }
    }

    if (VD1 > 1){
      // VOR = 0;
    }
    // result=(val1>val2) ? val1 : val2;
  }


// gate cycle sketch
  if ( temp > 29 && GC == 0 ){
    digitalWrite(solenoid1, HIGH);
    delay(100);
    digitalWrite(solenoid1, LOW);
    GC++;
    GC1 = 0;
    gateOpenedTime = currentTime;
  }
  if ((temp < 29) && (GC1 == 0) && (vacOffRequest <= currentTime) && ( currentTime - gateOpenedTime > 3000)){
    digitalWrite(solenoid2, HIGH);
    delay(100);
    digitalWrite(solenoid2, LOW);
    GC1++;
    GC = 0;
    gateClosedTime = currentTime;
  }
  if ((vacOffRequest < currentTime) && VOR == 1 ){
    // solenoidDA(solenoid3, 20);
    // lcd.setCursor(0,2);
    // lcd.print(vacOffRequest);
    // lcd.print("   ");
    // lcd.print(VOR);
    // lcd.print("  ");
    // lcd.print(currentTime);
    // delay(100);
    // lcd.setCursor(0,2);
    // lcd.print("                   ");
  }

}
