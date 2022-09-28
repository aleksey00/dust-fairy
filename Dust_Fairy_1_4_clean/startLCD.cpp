#include "startLCD.h"

// graphic icons
byte fire[8] = {0x08,0x04,0x14,0x0A,0x1A,0x1F,0x0E,0x04};
byte thermometer[8] = {0x04,0x0A,0x0A,0x0A,0x1B,0x11,0x1B,0x0E};
byte checkers[8] = {0x0A,0x15,0x0A,0x15,0x0A,0x15,0x0A,0x15};
byte checkersIn[8] = {0x15,0x0A,0x15,0x0A,0x15,0x0A,0x15,0x0A};
byte leftC[8] = {0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x1F};
byte rightC[8] = {0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x1F};
byte open[8] = {0x1F,0x11,0x11,0x11,0x11,0x11,0x11,0x1F};
byte close[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
byte leftOpen[8] = {0x1F,0x10,0x17,0x17,0x17,0x17,0x10,0x1F};
byte rightClose[8] = {0x1F,0x01,0x1D,0x1D,0x1D,0x1D,0x01,0x1F};

/*           
 *   // hd44780_I2Cexp lcd0(0x26, 20, 4);
 *   // hd44780_I2Cexp lcd1(0x27, 20, 4);          
 */
 
hd44780_I2Cexp lcd[2];    // auto locate & configure up to 16 displays
int NumLcd;		            // number of LCD displays found.

int lcdClearPass = 0;

void lcdSetup() {

  for(NumLcd = 0; NumLcd < 2; NumLcd++)     // If begin fails, then assume we have no more displays
	{
		if(lcd[NumLcd].begin(20, 4) != 0)
			break;
	}

	if(NumLcd == 0)                           // no LCD devices found, blink the onboard LED if possible
	{
		// fatalError(1); // this never returns
	}

	for(int n = 0; n < NumLcd; n++)           // Label the display with its instance number and i2c address
	{
		lcd[n].setCursor(0, 0);
		lcd[n].print("LCD:");
		lcd[n].print(n);

		lcd[n].print(" (0x");
		lcd[n].print(lcd[n].getProp(hd44780_I2Cexp::Prop_addr), HEX);
		lcd[n].print(")");
    // delay(500);
    lcd[n].clear();
    
    lcd[n].createChar(0, fire);              // custom character fire
    lcd[n].createChar(1, thermometer);       // custom character thermometer
    lcd[n].createChar(2, checkers);          // custom character checkers
    lcd[n].createChar(3, checkersIn);        // custom character checkers
    lcd[n].createChar(4, leftC);             // custom character leftC
    lcd[n].createChar(5, rightC);            // custom character rightC
    lcd[n].createChar(6, open);              // custom character open
    lcd[n].createChar(7, close);             // custom character close
    lcd[n].createChar(8, leftOpen);          // custom character leftOpen
    lcd[n].createChar(9, rightClose);        // custom character rightClose
	}

}

void lcdClear(int n, int line) // needs work. once run lcdClearPass=0;
{
  lcd[n].setCursor(0, line);  
  if(lcdClearPass == 0)
  {
    for(int i = 0; i < 20; i++)
    {
      lcd[n].print(F(" "));
      lcdClearPass++;
    }
  lcdClearPass = 0;
  }
}

void dashedLine(int n, int len) 
{
  int i;
  for (i = 0; i < len; i++) {
    lcd[n].print(F("*"));
  }
}



/************* Warning Message Function *************/

unsigned long messageTime = 0;                        // initial message Time 
unsigned long delayTime = 1000;                       // delay for message

void warningMessage(int n, String text, float value)  // LCD, any text(1-20ch), any value
{
  int stringLength = text.length();                   // measure text lenght
  int starCount = (((20 - (stringLength)) / 2) - 1);  // 20 - lenght of text/2 - 1 for 0-19 adjust

  if( millis() - messageTime > delayTime )            // will clear LCD if 1sec passed
  {
    lcd[n].clear();
    messageTime = millis();
  }

  humanTime(0, millis(), 0, "t", 0);                  // LCD, millis(), LCD line, text, show // time to LCD _humanTime.

  

  lcd[n].setCursor(0, 0);                               // row 1
  dashedLine(n,20);                                     // 20 asterix in row

  lcd[n].setCursor(0, 1);                               // row 2
  dashedLine(n,starCount);                              // calculated stars + _ + text + _
  lcd[n].print(F(" "));
  lcd[n].print(text);
  lcd[n].print(F(" "));

  if (stringLength % 2) {                               //check if odd, then add 1 star
    starCount = starCount + 1;
  }
  dashedLine(n,starCount);                              // calculated stars

  lcd[n].setCursor(0, 2);                               // row 3
  dashedLine(n,20);

  lcd[n].setCursor(8, 3);                               // row 4
  lcd[n].print(value, 2);                               // print value on the bottom row
  
 
  delay(delayTime);                                     // delay, I hate the delay funciton!

  lcd[n].clear();

}










// void infoDisplay(float tempCAv, float tempFAv, float psi) {
//   long display_time = millis();
//   //DISPLAY 1
//   //LINE 1
//   tempDisplay(tempCAv, tempFAv);

//   // while (millis() - display_time < 100) { //freezing up system
//   //   asm("");
//   // }

//   //LINE 2
//   // Time Run Display
//   // lcd.setCursor(0, 1); // set the cursor to column 0, line 1
//   // lcd.print("Time Run: ");
//   // long timeRun = ((millis()/1000));
//   // lcd.print(timeRun);

  

//   //LINE 3


//   //LINE 4
//   //Pressure Sensor Display
  
// }


void lowTempCheck(float temp, int value) 
{
  if (temp <= value) {
    warningMessage(0,"TEMP LOW", temp);
  }
}

void highTempCheck(float temp, int value) 
{
  if (temp >= value) {
    warningMessage(0,"TEMP HIGH", temp);
  }
}

void lowPressureCheck(float pressure, int value) 
{
  if (pressure > 0 && pressure < value) {
    warningMessage(0,"PRESSURE LOW", pressure);
    digitalWrite(52, HIGH);
  }
  if (pressure < 0){
    pressureDisplay(0, "Check 5V Pwr", 0, 1);            // LCD, psi, LCD line // psi to LCD _startLCD.
    pressureDisplay(0, "Check 5V Pwr", 0, 2);            // LCD, psi Main, LCD line // psi to LCD _startLCD.
    digitalWrite(52, HIGH);
    delay(200);
  }
}

void lowPressureWarning(int n,float pressure)
{
    if (pressure < 5){
    // lcd[n].home();
    lcd[n].setCursor(0, 0);
    dashedLine(n, 20); // lcd[n].print("********************");
 
    lcd[n].setCursor(0, 1);
    dashedLine(n, 3); // lcd[n].print("***");
    lcd[n].print(F(" PRESSURE LOW "));
    dashedLine(n, 3); // lcd[n].print("***");
    
    lcd[n].setCursor(0, 2);
    dashedLine(n, 20); // lcd[n].print("********************");
    
    lcd[n].setCursor(5, 3);
    lcd[n].print(F("PSI: "));
    lcd[n].print(pressure,2);
    delay(1000);
  }
}

void pressureDisplay(int n, String input, float psi, int line)
{
  
  lcd[n].setCursor(0, line);        // sets cursor to column 0, row 0
  // lcd[n].print(F("Pres."));         // prints label
  if (input != 0 ){
    lcd[n].print(input);            // text
  }
  // lcd[n].setCursor(12, line);
  lcd[n].print(psi, 1);             // prints pressure value to lcd[n] screen, 1 digit on float
  lcd[n].print(F("  "));            // to clear the display after large values or negatives
  lcd[n].setCursor(17, line);
  lcd[n].print(F("psi"));           // prints label after value

}



/* 
  solenoidTest function activates given solenoid, bool isopen designed to show infographic on LCD, rest of LCD parameters inculde LCD#, row#, line# and passed text along with soelnoid 
*/
void solenoidTest(int n, int row, int line, int solenoid, String text, bool isopen)  // LCD, row, line, solenoid, text, isopen
{
  lcd[n].setCursor(row, line);        // row, line of lcd
  lcd[n].print(text);                 // passed text
  if (isopen == 1)                    // display open gate
  {
    lcd[n].print(char(4));            // leftC
    lcd[n].print(char(5));            // rightC
    lcd[n].print(char(7));            // close
  } 
  else                                // display closed gate
  {
    lcd[n].print(char(8));            // leftOpen
    lcd[n].print(char(9));            // rightClose
    lcd[n].print(" ");                // empty space to clear previous state
  }
  digitalWrite(solenoid, HIGH);       // activate relay
}


void systemOK(int pressureInput, int pressureInputMain, int value1, int value2) // toggle between OK/STOP lights, checks pressure of 2 sensors
{
  if (pressureInput >= value1 && pressureInputMain >= value2)   // if both sensors below values trigger STOP light with relay
  {
    digitalWrite(52, LOW);                                      // STOP light on relay 52
  }
}