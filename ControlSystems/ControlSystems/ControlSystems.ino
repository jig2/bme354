/*

 Control Systems Tutorial
 Developing a Temperature Controller
 
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

int inpin = 1;
int outpin = 2;

float tempThresh;

void setup()
{
  pinMode(inpin,INPUT);
  pinMode(outpin,OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();

  tempThresh = selectTemp();


}

void loop()
{ 
  lcd.clear();  
  controlHeater(tempThresh);
  delay(1000);
}

void controlHeater(float tempThresh)
{
  float readval = analogRead(inpin);
  float voltage = readval/1023*5;
  float temperature = voltage/(4.5-0)*(300-0);

  lcd.setCursor(0,0);
  lcd.print("Current: ");
  lcd.setCursor(8,0);
  lcd.print(temperature,0);
  
  lcd.setCursor(0,1);
  lcd.print("Thresh: ");
  lcd.setCursor(7,1);
  lcd.print(tempThresh,0);

  if (temperature > tempThresh) {
    lcd.setCursor(11,1);
    lcd.write("High!");
    digitalWrite(outpin,LOW);
  } 
  else {
    lcd.setCursor(11,1);
    lcd.write("Low!");
    digitalWrite(outpin,HIGH);
  }

  if (temperature > 300) {
    lcd.setCursor(11,1);
    lcd.write("WAIT!");
    delay(9000); 
  }
}

float selectTemp()
{
  float tempThresh;

  int hundreds = 0;
  int tens = 0;
  int ones = 0;

  int place = 1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select A Temp");
  String tempString = String(hundreds) + String(tens) + String(ones);
  lcd.setCursor(0,1);
  lcd.print(tempString);


  while (0!=1) {

    int button_in = read_button();

    switch(button_in)
    {
    case btnNONE:
      {
        break;
      }
    case btnUP:
      {
        if (place==1) {
          if (hundreds<9) {
            hundreds = hundreds + 1;
          } 
          else {
            hundreds = 0;
          }
        }
        if (place==2) {
          if (tens<9) {
            tens = tens + 1;
          } 
          else {
            tens = 0;
          }
        }
        if (place==3) {
          if (ones<9) {
            ones = ones + 1;
          } 
          else {
            ones = 0;
          }
        }
        float tempThresh = hundreds*100 + tens*10 + ones;

        String tempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(tempString);
        delay(400);
        break;
      }
    case btnDOWN:
      {
        if (place==1) {
          if (hundreds>0) {
            hundreds = hundreds - 1;
          } 
          else {
            hundreds = 9;
          }
        }
        if (place==2) {
          if (tens>0) {
            tens = tens - 1;
          } 
          else {
            tens = 9;
          }
        }
        if (place==3) {
          if (ones>0) {
            ones = ones - 1;
          } 
          else {
            ones = 9;
          }
        }
        float tempThresh = hundreds*100 + tens*10 + ones;
        String tempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(tempString);
        delay(400);
        break;
      }
    case btnLEFT:
      {
        if (place == 1) {
          place = 3;
        } 
        else if (place == 2) {
          place = 1;
        } 
        else {
          place = 2;
        }
        float tempThresh = hundreds*100 + tens*10 + ones;
        String tempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(tempString);
        delay(400);
        break;
      }
    case btnRIGHT:
      {
        if (place == 1) {
          place = 2;
        } 
        else if (place == 2) {
          place = 3;
        } 
        else {
          place = 1;
        }
        float tempThresh = hundreds*100 + tens*10 + ones;
        String tempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(tempString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float tempThresh = hundreds*100 + tens*10 + ones;
        if (tempThresh>300 || tempThresh<20) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("You suck!");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          hundreds = 0;
          tens = 0;
          ones = 0;
          float tempThresh = hundreds*100 + tens*10 + ones;
          String tempString = String(hundreds) + String(tens) + String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Select A Temp");
          lcd.setCursor(0,1);
          lcd.print(tempString);
          delay(400);
        } else{
          return tempThresh;
        }
        break;
      }
    }
  }
}





