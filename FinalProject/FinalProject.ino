/***********************************************************************
 * BME 354L Final Project
 * Group 5: Halsey Friedel, Jayson Garmizo, Josh Lewis, Arlens Zeqollari
 ***********************************************************************/

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
PID myPID(&readTemp,&turnItOn,&threshold,5,0,3,DIRECT);

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

// Initialize Statistics
double DesiredPeakTemp[] = {
  0,0,0,0,0,0  };
double ActualPeakTemp[] = {
  0,0,0,0,0,0  };
double PercentError[] = {
  0,0,0,0,0,0  };

void setup()
{
  // Setup LCD
  lcd.begin(16, 2);

  // Setup Input/Output Pins
  pinMode(inpin,INPUT);
  pinMode(outpin,OUTPUT);

  // Setup PID
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  // Get User Input Values

  double region1start = getTemp();
  double region1end = UserInput(3,130,170,1);
  double region1slope = UserInput(1,1,4,2);
  double region1time = (region1end-region1start)/region1slope;

  double region2start = region1end;
  double region2end = region2start;
  double region2slope = 0;
  double region2time = UserInput(3,60,120,3);

  double region3start = region2end;
  double region3end = UserInput(3,197,237,5);
  double region3slope = UserInput(1,1,4,4);
  double region3time = (region3end-region3start)/region3slope;

  double region4start = region3end;
  double region4slope = region3slope;
  double region4time = UserInput(2,45,75,6)/2;
  double region4end = region4slope*region4time + region4start;

  double region5start = region4end;
  double region5end = region3end;
  double region5time = region4time;
  double region5slope = (region5end-region5start)/region5time;

  double region6start = region5end;
  double region6end = region1start;
  double region6slope = -UserInput(1,1,4,7);
  double region6time = (region6end-region6start)/region6slope;

  // Review User Input Values
  int ready1 = review(1,region1start,region1end,region1slope,region1time);
  while (ready1==0){
    region1start = getTemp();
    region1end = UserInput(3,130,170,1);
    region1slope = UserInput(1,1,4,2);
    region1time = (region1end-region1start)/region1slope;
    ready1 = review(1,region1start,region1end,region1slope,region1time);
  }
  int ready2 = review(2,region2start,region2end,region2slope,region2time);
  while (ready2==0){
    region2start = region1end;
    region2end = region2start;
    region2slope = 0;
    region2time = UserInput(3,60,120,3);
    ready2 = review(2,region2start,region2end,region2slope,region2time);
  }
  int ready3 = review(3,region3start,region3end,region3slope,region3time);
  while (ready3==0){
    region3start = region2end;
    region3end = UserInput(3,197,237,5);
    region3slope = UserInput(1,1,4,4);
    region3time = (region3end-region3start)/region3slope;
    ready3 = review(3,region3start,region3end,region3slope,region3time);
  }
  int ready4 = review(4,region4start,region4end,region4slope,region4time);
  while (ready4==0){
    region4start = region3end;
    region4slope = region3slope;
    region4time = UserInput(2,45,75,6)/2;
    region4end = region4slope*region4time + region4start;
    ready4 = review(4,region4start,region4end,region4slope,region4time);
  }
  int ready5 = review(5,region5start,region5end,region5slope,region5time);
  while (ready5==0){
    region5start = region4end;
    region5end = region3end;
    region5time = region4time;
    region5slope = (region5end-region5start)/region5time;
    ready5 = review(5,region5start,region5end,region5slope,region5time);
  }
  int ready6 = review(6,region6start,region6end,region6slope,region6time);
  while (ready6==0){
    region6start = region5end;
    region6end = region1start;
    region6slope = -UserInput(1,1,4,7);
    region6time = (region6end-region6start)/region6slope;
    ready6 = review(6,region6start,region6end,region6slope,region6time);
  }

  // Ready To Start
  readyToStart();

  // Control System: Region 1
  control(1,region1start,region1end,region1slope,region1time,500);

  // Control System: Region 2
  control(2,region2start,region2end,region2slope,region2time,500);

  // Control System: Region 3
  control(3,region3start,region3end,region3slope,region3time,500);

  // Control System: Region 4
  control(4,region4start,region4end,region4slope,region4time,500);

  // Control System: Region 5
  control(5,region5start,region5end,region5slope,region5time,500);

  // Control System: Region 6
  control(6,region6start,region6end,region6slope,region6time,500);

  // Finished Screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Finished!");
  delay(3000);

  // Compute Statistics
  Statistics(DesiredPeakTemp,ActualPeakTemp,PercentError);
}


