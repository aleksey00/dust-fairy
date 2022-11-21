/* This file contains functions no longer used and other references no longer used */

// loop_DustFairy_clean.ino

/* gates and manualOverride disblaed for testing */
  // gates(1, 'k');            // LCD, Serial input // switch case for solenoids _solenoids

  // manualOverrride(1, 'a');

  // dustCollector(8);         // Serial input // 

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  // if (digitalRead(blueButton) == HIGH && buttonFlag == 2) 
  // {
  //   lcdClear(1, 3);
  //   vacOperate(0);
  //   buttonFlag = 0;
  //   // if(delayFlag == 0)
  //   // {
      
  //   // }
  // } 
  // else 
  // {
  //   if(buttonFlag == 0)
  //   {
  //     preMillis = curMillis;          // preMill=millis() curMillis = 0 // millis() = 0
  //     buttonFlag++;
  //   }
  //   curMillis = millis();
  //   unsigned long pressed = curMillis - preMillis;
  //   vacOperate(1);                    // vdust collection on with LCD info
  //   humanTime(1, pressed, 3);
  //   // vacOperate();

  // }

  // void vacOffDelay();

  // dustCollector(1);

  // _Dust_Fairy_clean.ino

  float averager(float inputValue, int averageAmt) {
  float averageValue = 0;
  for (int i = 0; i < averageAmt; i++) {
    averageValue = averageValue + inputValue;
    delay(1);
  }
  // averageValue = (averageValue * (averageAmt-1) + inputValue) / averageAmt;
  averageValue = averageValue / averageAmt;
  
  return averageValue;
}

int averagerInt(float inputValue, int averageAmt){
  int averageValue = round(inputValue);
  int counter = 0;
  for (int i = 0; i < averageAmt; i++){
    averageValue = averageValue + inputValue;
  }
  averageValue = averageValue / averageAmt;
  return averageValue;
}


void solenoidDA(int solenoid, int period) {
  digitalWrite(solenoid, HIGH);
  delay(period);
  digitalWrite(solenoid, LOW);
}

// setup() Dust_Fairy_clean.ino

  // firstRunFunc(0,200,200,700);    // int LCD, int sensOpen, int sensClose, int vacTest


