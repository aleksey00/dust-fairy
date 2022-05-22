#include <Arduino.h>

int VD, VD1, VOR = 0; // vacuum integers
int GC, GC1 = 0; // gates integers
const unsigned long eventDelay = 10000; //10 sec
unsigned long vacStartTime = 0;
unsigned long vacOffRequest = 0;
unsigned long gateClosedTime, gateOpenedTime = 0;

// void vacDelay(float temp){ 

//   unsigned long currentTime = millis();
    
//   if ( temp > 29 && VD == 0 ){ //vacuum ON
//     vacStartTime = currentTime;
//     digitalWrite(vacuum, HIGH);
//     VD++;
//     VD1 = 0;
//     VOR = 0; // reset this value when gate opens for delay off function to work
//   }
  
//   if ( temp < 29 && VD1 == 0  ){ //vacuum OFF

//     if (VOR == 0){
//     vacOffRequest = currentTime;
//     VOR++;
//     }

//     if ( currentTime - vacStartTime >= eventDelay)  { //safety delay timer
//       if ( currentTime - vacOffRequest > eventDelay) { //turn off delay timer
//         digitalWrite(vacuum, LOW);
//         VD1++;
//         VD = 0;
//         VOR = 0;
//       }
//     }
//     // result=(val1>val2) ? val1 : val2;
//   }
// // gate cycle sketch
//   if ( temp > 29 && GC == 0 ){
//     digitalWrite(solenoid1, HIGH);
//     delay(100);
//     digitalWrite(solenoid1, LOW);
//     GC++;
//     GC1 = 0;
//   }
//   if (temp < 29 && GC1 == 0 && vacOffRequest <= currentTime){
//     digitalWrite(solenoid2, HIGH);
//     delay(100);
//     digitalWrite(solenoid2, LOW);
//     GC1++;
//     GC = 0;
//   }
//   if ((vacOffRequest <= currentTime) && VOR >=1 ){
//     solenoidDA(solenoid3, 100);
//   }

// }