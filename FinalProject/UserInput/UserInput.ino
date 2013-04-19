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

float PreheatThresh;
float slopeSoakThresh;
float SoakTimeThresh;
float PeakThresh;
float slopePeakThresh;
float ReflowTimeThresh;
float ReflowThresh;

void setup(){
lcd.begin(16,2);
lcd.clear();
PreheatThresh=Preheat();
slopeSoakThresh=selectSoakSlope();
SoakTimeThresh=SoakTime();
PeakThresh=PeakTemp();
slopePeakThresh=selectPeakSlope();
ReflowTimeThresh=ReflowTime();
ReflowThresh=selectReflowSlope();
}

void loop(){
lcd.clear;
Checking(PreheatThresh, slopeSoakThresh, SoakTimeThresh, PeakThresh, slopePeakThresh, ReflowTimeThresh, ReflowThresh);
delay(1000);
}

void Checking(float PreheatThresh, float slopeSoakThresh, float SoakTimeThresh, float PeakThresh, float slopePeakThresh, float ReflowTimeThresh, float ReflowThresh){
lcd.setCursor(0,0);
lcd.print('Soak Temp');
lcd.setCursor(0,1);
lcd.print(PreheatThresh);
delay(400);

lcd.setCursor(0,0);
lcd.print('Soak Slope');
lcd.setCursor(0,1);
lcd.print(slopeSoakThresh);
delay(400);

lcd.setCursor(0,0);
lcd.print('Soak Time');
lcd.setCursor(0,1);
lcd.print(SoakTimeThresh);
delay(400);

lcd.setCursor(0,0);
lcd.print('Reflow Temp');
lcd.setCursor(0,1);
lcd.print(PeakThresh);
delay(400);

lcd.setCursor(0,0);
lcd.print('Slope to Reflow');
lcd.setCursor(0,1);
lcd.print(slopePeakThresh);
delay(400);

lcd.setCursor(0,0);
lcd.print('Reflow Time');
lcd.setCursor(0,1);
lcd.print(ReflowTimeThresh);
delay(400);

lcd.setCursor(0,0);
lcd.print('Reflow Slope');
lcd.setCursor(0,1);
lcd.print(ReflowThresh);
delay(400);

lcd.setCursor(0,0);
lcd.print('OK?');
lcd.setCursor(0,1);
lcd.print('UP=YES DOWN=NO');

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
        break;
      }
    case btnDOWN:
      {
        setup();
      }
    }
}
