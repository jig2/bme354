// Define Input/Output Pins
int inpin = A5;
int outpin = 2;

// LCD and PID Libraries
#include <LiquidCrystal.h>
#include <PID_v1.h>

// initialize LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Initializie PID
double readTemp, threshold, turnItOn;
PID myPID(&readTemp,&turnItOn,&threshold,2,.1,5,DIRECT);

// Define Button Signifiers
#define btnNONE 0
#define btnSELECT 1
#define btnLEFT 2
#define btnDOWN 3
#define btnUP 4
#define btnRIGHT 5

// Define Voltage Thresholds for each Button
#define vSELECT 3.5
#define vLEFT 2.5
#define vDOWN 1.5
#define vUP 0.75
#define vRIGHT 0.25

void setup()
{
  lcd.begin(16, 2);

  pinMode(inpin,INPUT);
  pinMode(outpin,OUTPUT);

  myPID.SetMode(AUTOMATIC);
}

/*
Part I. User Input
 */

// Get Input Values

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

double DesiredPeakTemp[] = {0,0,0,0,0,0};
double ActualPeakTemp[] = {0,0,0,0,0,0};
double PercentError[] = {0,0,0,0,0,0};

/*
Part II. Control System
 */

void loop()
{
  // region 1
  control(1,region1start,region1end,region1slope,region1time,500);

  // region 2
  control(2,region2start,region2end,region2slope,region2time,500);
  
  // region 3
  control(3,region3start,region3end,region3slope,region3time,500);
  
  // region 4
  control(4,region4start,region4end,region4slope,region4time,500);
  
  // region 5
  control(5,region5start,region5end,region5slope,region5time,500);
  
  // region 6
  control(6,region6start,region6end,region6slope,region6time,500);

  // finished
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Finished!");
  delay(3000);
  
  // statistics
  Statistics(DesiredPeakTemp,ActualPeakTemp,PercentError);
}
