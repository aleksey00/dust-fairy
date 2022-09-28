#include "TempSensor.h"
#include "startLCD.h"

Adafruit_Si7021 tempsensor = Adafruit_Si7021();                   // define temp sensor

bool enableHeater = false;
uint8_t loopCnt = 0;


void tempSetup()                                                   // setup tempSensor
{
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");
  
  if (!tempsensor.begin())                                        // check temp sens functionality
  {          
    // Serial.println("Did not find Si7021 tempsensor!");
    // while (true);
    lcd[0].setCursor(0, 3);
    lcd[0].print(F("Check Temp Sensor"));
  }

  Serial.print("Found model ");
  switch(tempsensor.getModel()) 
  {
    case SI_Engineering_Samples:
      Serial.print("SI engineering samples"); break;
    case SI_7013:
      Serial.print("Si7013"); break;
    case SI_7020:
      Serial.print("Si7020"); break;
    case SI_7021:
      Serial.print("Si7021"); break;
    case SI_UNKNOWN:
    default:
      Serial.print("Unknown");
  }
  Serial.print(" Rev(");
  Serial.print(tempsensor.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(tempsensor.sernum_a, HEX); Serial.println(tempsensor.sernum_b, HEX);
}


void tempReading(int n, int line)
{

  lcd[n].setCursor(0, line);
  lcd[n].print(tempsensor.readTemperature(), 1);
  lcd[n].print(char(223));                                        // print the unit" ℃ "
  lcd[n].print("C ");

  float tempF = 1.8 * tempsensor.readTemperature() + 32.0;        // convert to F

  lcd[n].print(tempF, 1);  
  lcd[n].print("F ");  
  lcd[n].print(tempsensor.readHumidity(), 1);
  lcd[n].print("%");
    
  if (tempsensor.readHumidity() >= 60 && ++loopCnt == 30)         // if humidity is over 60 and loop count is 30 then Heater is on
  {
    enableHeater = !enableHeater;
    tempsensor.heater(enableHeater);
    
    if (tempsensor.isHeaterEnabled())                             // check is the heater on?
    {
      lcd[0].setCursor(19,3); 
      lcd[0].print(char(2));                                      // indicating heater is on
    }
    else 
    {
      lcd[0].setCursor(19,3); 
      lcd[0].print(" ");                                          // clear heater symbol
    }  
    loopCnt = 0;
  }

  if (tempsensor.readHumidity() < 60)                             // if humidity is less than 60 then heater is off
  {
    enableHeater = false;
    tempsensor.heater(enableHeater);

    if (tempsensor.isHeaterEnabled())                             // check is the heater on?
    {
      lcd[0].setCursor(19,3);                                     
      lcd[0].print(char(2));                                      // indicating heater is on
    }
    else 
    {
      lcd[0].setCursor(19,3); 
      lcd[0].print(" ");                                          // clear heater symbol
    } 
  }

}




void fanOn (int solenoid, int offTemp, int onTemp)
{
  if (tempsensor.readTemperature() < offTemp) 
  {
    digitalWrite(solenoid, LOW);
  }
  if (tempsensor.readTemperature() >= onTemp) 
  {
    digitalWrite(solenoid, HIGH);
  }
}
