/*

This exercise completes Objective 4

Objective 4: Create a stopwatch that
1. Accepts user inputs to set the desired length of time in Min:Sec format.
2. Counts down to zero and blinks the LCD once the time has reached zero.
3. Allows the user to start and stop the time.

How the stopwatch works:
- On the "Select Minute" screen, press the UP and DOWN buttons to change the number of minutes, and then press SELECT once you're done.
- On the "Select Second" screen, press the UP and DOWN buttons to change the number of seconds, and then press SELECT once you're done.
- On the "Ready?" screen, press the SELECT button when you want the stop watch to start counting down.
- When the stopwatch is running, press the SELECT button to stop the stopwatch, and press the SELECT button again to continue running the stopwatch.
- When the time has reached zero, the "Done!" message will blink, and the system will reset after 10 seconds.

*/

// include the library code
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define button signifiers
#define btnNONE 0
#define btnSELECT 1
#define btnLEFT 2
#define btnDOWN 3
#define btnUP 4
#define btnRIGHT 5

// define voltage thresholds for each button (obtained from Objective 3)
#define vSELECT 3.5
#define vLEFT 2.5
#define vDOWN 1.5
#define vUP 0.75
#define vRIGHT 0.25

// reads what button is being pushed
int read_button()
{
  // obtain ADC reading from analog pin A0
  float adc_in = analogRead(0);
  // map ADC reading (range = 0:1023) onto voltage value (range = 0V:5V)
  float voltage_in = adc_in/1023*5;

  // based on the measured thresholds from Objective 3, determines what button is being pushed
  if (voltage_in > vSELECT) return btnNONE;
  if (voltage_in < vRIGHT) return btnRIGHT;
  if (voltage_in < vUP) return btnUP;
  if (voltage_in < vDOWN) return btnDOWN;
  if (voltage_in < vLEFT) return btnLEFT;
  if (voltage_in < vSELECT) return btnSELECT;
  return btnNONE;
}

void setup()
{
  lcd.begin(16, 2);
}

void loop()
{

  // initializes the program
  int minute = 0;  // number of minutes
  int second = 0;  // number of seconds
  String minuteString = "00";  // minutes string used on display
  String secondString = "00";  // seconds string used on display

  lcd.clear();
  lcd.print(minuteString + ":" + secondString + " Select Min");

  int button_in = btnNONE;

  // select minute value

  while (0 != 1){  // runs until break at end of while loop is reached (when the SELECT button is pressed)
    button_in = read_button();
    switch (button_in)
    {
    case btnNONE:
      {
        break;
      }
    case btnUP:  // increases minute value by one
      {
        minute = minute + 1;
        if (minute<10)
        {
          minuteString = "0" + String(minute);
        } 
        else if (minute<60) {
          minuteString = String(minute);
        } 
        else {
          minute = 0;
          minuteString = "00";
        }
        lcd.clear();
        lcd.print(minuteString + ":" + secondString + " Select Min");
        delay(400);
        break;
      }
    case btnDOWN: // decreases minute value by one
      {
        minute = minute - 1;
        if (minute<0){
          minute = 59;
          minuteString = "59";
        } 
        else if (minute<10)
        {
          minuteString = "0" + String(minute);
        } 
        else {
          minuteString = String(minute);
        }
        lcd.clear();
        lcd.print(minuteString + ":" + secondString + " Select Min");
        delay(400);
        break;
      }
    }
    if (button_in == btnSELECT) break; // when the SELECT button is pressed, done changing the minutes value
  }

  // select second value

  lcd.clear();
  lcd.print(minuteString + ":" + secondString + " Select Sec");
  delay(500);

  while (0 != 1){  // runs until break at end of while loop is reached (when the SELECT button is pressed)
    button_in = read_button();
    switch (button_in)
    {
    case btnNONE:
      {
        break;
      }
    case btnUP: // increases second value by one
      {
        second = second + 1;
        if (second<10)
        {
          secondString = "0" + String(second);
        } 
        else if (second<60) {
          secondString = String(second);
        } 
        else {
          second = 0;
          secondString = "00";
        }
        lcd.clear();
        lcd.print(minuteString + ":" + secondString + " Select Sec");
        delay(400);
        break;
      }
    case btnDOWN: // decreases second value by one
      {
        second = second - 1;
        if (second<0){
          second = 59;
          secondString = "59";
        } 
        else if (second<10)
        {
          secondString = "0" + String(second);
        } 
        else {
          secondString = String(second);
        }
        lcd.clear();
        lcd.print(minuteString + ":" + secondString + " Select Sec");
        delay(400);
        break;
      }
    }
    if (button_in == btnSELECT) break;  // when the SELECT button is pressed, done changing the seconds value
  }

  // is the user ready

  lcd.clear();
  lcd.print(minuteString + ":" + secondString + " Ready?");
  delay(500);

  while (0 != 1){  // runs until break at end of while loop is reached (when the SELECT button is pressed)
    button_in = read_button();
    if (button_in == btnSELECT) break;  // when the SELECT button is pressed, ready to start running the stopwatch
  }
  
  // run the stopwatch
  
  delay(400);
  lcd.clear();
  lcd.print(minuteString + ":" + secondString + " Go!");

  // changes minute and second values accordingly
  while (minute >= 0) {
    while (second >= 0) {
      lcd.clear();
      lcd.print(minuteString + ":" + secondString + " Go!");

      // if the SELECT button isn't pressed, the stopwatch continues to run, and a second is decreased after 10 iterations of 100 ms delays
      // if the SELECT button is pressed, then the stopwatch is stopped, and continues to be stopped until the SELECT button is pressed again
      for (int i = 1; i <= 10; i++) {  // if stopwatch not stopped, a second is decreased after 10 iterations of 100 ms delays
        button_in = read_button();
        if (button_in == btnSELECT) {  // if the stopwatch is stopped
          lcd.clear();
          lcd.print(minuteString + ":" + secondString + " Stopped");
          delay(400);
          
          button_in = read_button();
          while (button_in != btnSELECT) {  // continues to be stopped until the SELECT button is pressed again
            delay(100);
            button_in = read_button();
          }
          delay(400);
          
        } else {
          lcd.clear();
          lcd.print(minuteString + ":" + secondString + " Go!");
          delay(100);
        }
      }

      second = second - 1;  // decreases second value by one
      if (second==0 && minute==0) break; // stops stopwatch if no time left
      if (second<10)
      {
        secondString = "0" + String(second);
      } 
      else {
        secondString = String(second);
      }

    }
    if (second==0 && minute==0) break;  // stops stopwatch if no time left
    minute = minute - 1; // when there are no more seconds, convert one minute into sixty seconds, and decrease minute value by one
    if (minute<10)
    {
      minuteString = "0" + String(minute);
    } 
    else { 
      minuteString = String(minute);
    }
    second = 59;
    secondString = "59";
  }

  // when there is no more time, flash a done message on the screen
  for (int i = 1; i<=10; i++) {
    lcd.clear();
    lcd.print("00:00 Done!");
    delay(200);
    lcd.clear();
    delay(200);

  }

  lcd.clear();
  lcd.print("00:00 Done!");
  delay(1000);

  // program then restarts
}
