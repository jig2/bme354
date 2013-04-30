/*

 Control System:
 - controls the heater
 - provides user output
 
 */

int inpin = A5;
int outpin = 2;

// include the library code
#include <LiquidCrystal.h>

#include <PID_v1.h>

double readTemp, threshold, turnItOn;
PID myPID(&readTemp,&turnItOn,&threshold,2,.1,5,DIRECT);

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
  double adc_in = analogRead(0);
  // map ADC reading (range = 0:1023) onto voltage value (range = 0V:5V)
  double voltage_in = adc_in/1023*5;

  // based on the measured thresholds from Objective 3, determines what button is being pushed
  if (voltage_in > vSELECT) return btnNONE;
  if (voltage_in < vRIGHT) return btnRIGHT;
  if (voltage_in < vUP) return btnUP;
  if (voltage_in < vDOWN) return btnDOWN;
  if (voltage_in < vLEFT) return btnLEFT;
  if (voltage_in < vSELECT) return btnSELECT;
  return btnNONE;
}

// assign input values

double region1start = 25;
double region1end = 150;
double region1slope = 2;
double region1time = (region1end-region1start)/region1slope;

double region2start = region1end;
double region2end = region2start;
double region2slope = 0;
double region2time = 90;

double region3start = region2end;
double region3end = 217;
double region3slope = 2;
double region3time = (region3end-region3start)/region3slope;

double region4start = region3end;
double region4slope = region3slope;
double region4time = 30;
double region4end = region4slope*region4time + region4start;

double region5start = region4end;
double region5end = region3end;
double region5time = region4time;
double region5slope = (region5end-region5start)/region5time;

double region6start = region5end;
double region6end = region1start;
double region6slope = -3;
double region6time = (region6end-region6start)/region6slope;

void setup()
{
  lcd.begin(16, 2);

  pinMode(inpin,INPUT);
  pinMode(outpin,OUTPUT);

  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  // region 1
  double region1iterations = 100;
  double region1delay = round(region1time/region1iterations*1000);

  for (int i = 1; i <= region1iterations; i++) {
    double readVal = (double) analogRead(inpin);

    Serial.begin(9600);
    Serial.println(readVal);

    double readVolt = readVal/1023*5;
    readTemp = readVolt/(4.5-0)*(300-0);

    threshold = region1start + region1slope*region1delay/1000*i; 

    myPID.Compute();

    analogWrite(outpin,turnItOn);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Desired: ");
    lcd.setCursor(0,1);
    lcd.print("Actual: ");
    lcd.setCursor(9,0);
    lcd.print(threshold);
    lcd.setCursor(8,1);
    lcd.print(readTemp);

    delay(region1delay);
  }

  // region 2

  double region2iterations = 100;
  double region2delay = round(region2time/region2iterations*1000);

  for (int i = 1; i <= region2iterations; i++) {
    double readVal = (double) analogRead(inpin);

    Serial.begin(9600);
    Serial.println(readVal);

    double readVolt = readVal/1023*5;
    readTemp = readVolt/(4.5-0)*(300-0);

    threshold = region2start + region2slope*region2delay/1000*i;

    myPID.Compute();

    analogWrite(outpin,turnItOn);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Desired: ");
    lcd.setCursor(0,1);
    lcd.print("Actual: ");
    lcd.setCursor(9,0);
    lcd.print(threshold);
    lcd.setCursor(8,1);
    lcd.print(readTemp);

    delay(region2delay);
  }

  // region 3

  double region3iterations = 100;
  double region3delay = round(region3time/region3iterations*1000);

  for (int i = 1; i <= region3iterations; i++) {
    double readVal = (double) analogRead(inpin);

    Serial.begin(9600);
    Serial.println(readVal);

    double readVolt = readVal/1023*5;
    readTemp = readVolt/(4.5-0)*(300-0);

    threshold = region3start + region3slope*region3delay/1000*i;

    myPID.Compute();

    analogWrite(outpin,turnItOn);


    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Desired: ");
    lcd.setCursor(0,1);
    lcd.print("Actual: ");
    lcd.setCursor(9,0);
    lcd.print(threshold);
    lcd.setCursor(8,1);
    lcd.print(readTemp);

    delay(region3delay);
  }

  // region 4

  double region4iterations = 100;
  double region4delay = round(region4time/region4iterations*1000);

  for (int i = 1; i <= region4iterations; i++) {
    double readVal = (double) analogRead(inpin);

    Serial.begin(9600);
    Serial.println(readVal);

    double readVolt = readVal/1023*5;
    readTemp = readVolt/(4.5-0)*(300-0);

    threshold = region4start + region4slope*region4delay/1000*i;

    myPID.Compute();

    analogWrite(outpin,turnItOn);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Desired: ");
    lcd.setCursor(0,1);
    lcd.print("Actual: ");
    lcd.setCursor(9,0);
    lcd.print(threshold);
    lcd.setCursor(8,1);
    lcd.print(readTemp);

    delay(region4delay);
  }

  // region 5

  double region5iterations = 100;
  double region5delay = round(region5time/region5iterations*1000);

  for (int i = 1; i <= region5iterations; i++) {
    double readVal = (double) analogRead(inpin);

    Serial.begin(9600);
    Serial.println(readVal);

    double readVolt = readVal/1023*5;
    readTemp = readVolt/(4.5-0)*(300-0);

    threshold = region5start + region5slope*region5delay/1000*i;

    myPID.Compute();

    analogWrite(outpin,turnItOn);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Desired: ");
    lcd.setCursor(0,1);
    lcd.print("Actual: ");
    lcd.setCursor(9,0);
    lcd.print(threshold);
    lcd.setCursor(8,1);
    lcd.print(readTemp);

    delay(region5delay);
  }

  // region 6

  double region6iterations = 100;
  double region6delay = round(region6time/region6iterations*1000);

  for (int i = 1; i <= region6iterations; i++) {
    double readVal = (double) analogRead(inpin);

    Serial.begin(9600);
    Serial.println(readVal);

    double readVolt = readVal/1023*5;
    readTemp = readVolt/(4.5-0)*(300-0);

    threshold = region6start + region6slope*region6delay/1000*i;

    myPID.Compute();

    analogWrite(outpin,turnItOn);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Desired: ");
    lcd.setCursor(0,1);
    lcd.print("Actual: ");
    lcd.setCursor(9,0);
    lcd.print(threshold);
    lcd.setCursor(8,1);
    lcd.print(readTemp);

    delay(region6delay);
  }

}




