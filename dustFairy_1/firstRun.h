#include <Arduino.h>

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
  // Serial.println("Vavle 1: CLOSE");
  digitalWrite(solenoid1, HIGH);
  delay(sensOpen);
  lcd.setCursor(9,1);
  lcd.print("OPEN ");
  // Serial.println("Vavle 1: OPEN \n");
  digitalWrite(solenoid1, LOW);
  delay(sensClose);

  lcd.setCursor(0,1);
  lcd.print("Valve 2: CLOSE");
  // Serial.println("Vavle 2: CLOSE");
  digitalWrite(solenoid2, HIGH);
  delay(sensOpen);
  lcd.setCursor(9,1);
  lcd.print("OPEN ");
  // Serial.println("Vavle 2: OPEN \n");
  digitalWrite(solenoid2, LOW);
  delay(sensClose);

  lcd.setCursor(0,1);
  lcd.print("Valve 3: CLOSE");
  // Serial.println("Vavle 3: CLOSE");
  digitalWrite(solenoid3, HIGH);
  delay(sensOpen);
  lcd.setCursor(9,1);
  lcd.print("OPEN ");
  // Serial.println("Vavle 3: OPEN \n");
  digitalWrite(solenoid3, LOW);
  delay(sensClose);

  lcd.setCursor(0,1);
  lcd.print("Valve 4: CLOSE");
  // Serial.println("Vavle 4: CLOSE");
  digitalWrite(solenoid4, HIGH);
  delay(sensOpen);
  lcd.setCursor(9,1);
  lcd.print("OPEN ");
  // Serial.println("Vavle 4: OPEN \n");
  digitalWrite(solenoid4, LOW);
  delay(sensClose);

  lcd.setCursor(0,1);
  lcd.print("Dust Collector: ON");
  // Serial.println("Dust Collector: ON");
  digitalWrite(vacuum, HIGH);
  delay(vacTest);
  lcd.setCursor(16,1);
  lcd.print("OFF");
  // Serial.println("Dust Collector: OFF \n");
  digitalWrite(vacuum, LOW);
  delay(400);

  lcd.clear();
  lcd.print("Run Test Complete");
  delay(500);    
  lcd.clear();

}