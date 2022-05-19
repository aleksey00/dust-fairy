#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "LCD_Init.h"
#include "TempSensor.h"
#include "solenoids.h"
#include "PressureSensor.h"

void setup(){

  lcd.init();
  lcd.backlight();

  pinMode(solenoid1, OUTPUT);
  pinMode(solenoid2, OUTPUT);
  pinMode(solenoid3, OUTPUT);
  pinMode(solenoid4, OUTPUT);
  pinMode(vacuum, OUTPUT);

  firstRun(300, 300, 1000); //SensOpen, SensClose, Vacuum solenoid

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

  float tempCAv;
  float tempFAv;
  float pressureValueAverage;
  tempCAv = averager(tempC, 20);  
  tempFAv = averager(tempF, 100);
  pressureValueAverage = averager(pressureValue, 100);

  infoDisplay(tempCAv, tempFAv, pressureValueAverage);

}

void gateDelay(){

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
  lcd.setCursor(0, 1); // set the cursor to column 0, line 1
  lcd.print("Time Run: ");
  long timeRun = ((millis()/1000));
  lcd.print(timeRun);

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

void firstRun(int sensOpen, int sensClose, int vacTest){

  lcd.print("Intializing.  ");
  delay(300);
  lcd.setCursor(0,0);
  lcd.print("Intializing.. ");
  delay(300);
  lcd.setCursor(0,0);
  lcd.print("Intializing...");
  delay(300);    
  lcd.clear();
  lcd.print("Run Test Started");
  delay(500);

  lcd.setCursor(0,1);
  lcd.print("Valve 1: CLOSE");
  Serial.println("Vavle 1: CLOSE");
  digitalWrite(solenoid1, HIGH);
  delay(sensOpen);
  lcd.setCursor(9,1);
  lcd.print("OPEN ");
  Serial.println("Vavle 1: OPEN \n");
  digitalWrite(solenoid1, LOW);
  delay(sensClose);

  lcd.setCursor(0,1);
  lcd.print("Valve 2: CLOSE");
  Serial.println("Vavle 2: CLOSE");
  digitalWrite(solenoid2, HIGH);
  delay(sensOpen);
  lcd.setCursor(9,1);
  lcd.print("OPEN ");
  Serial.println("Vavle 2: OPEN \n");
  digitalWrite(solenoid2, LOW);
  delay(sensClose);

  lcd.setCursor(0,1);
  lcd.print("Valve 3: CLOSE");
  Serial.println("Vavle 3: CLOSE");
  digitalWrite(solenoid3, HIGH);
  delay(sensOpen);
  lcd.setCursor(9,1);
  lcd.print("OPEN ");
  Serial.println("Vavle 3: OPEN \n");
  digitalWrite(solenoid3, LOW);
  delay(sensClose);

  lcd.setCursor(0,1);
  lcd.print("Valve 4: CLOSE");
  Serial.println("Vavle 4: CLOSE");
  digitalWrite(solenoid4, HIGH);
  delay(sensOpen);
  lcd.setCursor(9,1);
  lcd.print("OPEN ");
  Serial.println("Vavle 4: OPEN \n");
  digitalWrite(solenoid4, LOW);
  delay(sensClose);

  lcd.setCursor(0,1);
  lcd.print("Dust Collector: ON");
  Serial.println("Dust Collector: ON");
  digitalWrite(vacuum, HIGH);
  delay(vacTest);
  lcd.setCursor(16,1);
  lcd.print("OFF");
  Serial.println("Dust Collector: OFF \n");
  digitalWrite(vacuum, LOW);
  delay(400);

  lcd.clear();
  lcd.print("Run Test Complete");
  delay(500);    
  lcd.clear();

}

