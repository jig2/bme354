/********************
 * FUNCTION LIBRARY
 ********************/

/********************
 * 
 * control()
 * 
 ********************/
void control(int region,double startT, double endT, double slope, double time, double delayTime)
{ 
  double Iterations = round(time)/(delayTime/1000);

  for (int i = 1; i <= Iterations; i++) {

    readTemp = getTemp();
    //    if (readTemp > 300){
    //      shutDown();
    //    }
    threshold = startT + slope*delayTime/1000*i;

    if (readTemp > ActualPeakTemp[region-1]){
      ActualPeakTemp[region-1] = readTemp;
    }
    if (threshold > DesiredPeakTemp[region-1]){
      DesiredPeakTemp[region-1] = threshold;
    }
    PercentError[region-1] = PercentError[region-1] + (abs(readTemp-threshold)/threshold)*100/Iterations;

    myPID.Compute();
    digitalWrite(outpin,turnItOn);

    double timeElapsed = (i-1)*delayTime;
    double timeTotal = Iterations*delayTime;
    double timeLeftDouble = (timeTotal - timeElapsed)/10;
    int timeLeft = (int) timeLeftDouble;
    timeLeft = (timeLeft - (timeLeft % 100))/100;
    int minutesLeft = (timeLeft - (timeLeft % 60))/60;
    int secondsLeft = timeLeft % 60;

    LCD_ControlSystem(region,readTemp,threshold,minutesLeft,secondsLeft);
    delay(delayTime);
  }
}

/********************
 * 
 * getTemp()
 * 
 ********************/
double getTemp(){
  double readVal = (double) analogRead(inpin);
  double readTemp = 0.9907*readVal - 13.65;

  return readTemp;
}

/********************
 * 
 * LCD_ControlSystem()
 * 
 ********************/
void LCD_ControlSystem(int region,double readTemp,double threshold,int minutesLeft,int secondsLeft){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stage   D      C");
  lcd.setCursor(5,0);
  lcd.print(region);
  lcd.setCursor(9,0);
  if (threshold<100) {
    lcd.print("0");
    lcd.setCursor(10,0);
    lcd.print(threshold);
  } 
  else {
    lcd.print(threshold);
  }

  lcd.setCursor(0,1);
  lcd.print("TL  :   A      C");
  lcd.setCursor(2,1);
  if (minutesLeft<10) {
    lcd.print("0");
    lcd.setCursor(3,1);
    lcd.print(minutesLeft);
  } 
  else {
    lcd.print(minutesLeft);
  }
  lcd.setCursor(5,1);
  if (secondsLeft<10) {
    lcd.print("0");
    lcd.setCursor(6,1);
    lcd.print(secondsLeft);
  } 
  else {
    lcd.print(secondsLeft);
  }
  lcd.setCursor(9,1);
  if (readTemp<100) {
    lcd.print("0");
    lcd.setCursor(10,1);
    lcd.print(readTemp);
  } 
  else {
    lcd.print(readTemp);
  }
}

/********************
 * 
 * read_button()
 * 
 ********************/
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

/********************
 * 
 * review()
 * 
 ********************/

void review(int region, double tempStart, double tempEnd, double slope, double time){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Region");
  lcd.setCursor(8,0);
  lcd.print(region);
  lcd.setCursor(0,1);
  lcd.print("StartTemp      C");
  lcd.setCursor(9,1);
  lcd.print(tempStart);
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Region");
  lcd.setCursor(8,0);
  lcd.print(region);
  lcd.setCursor(0,1);
  lcd.print("EndTemp        C");
  lcd.setCursor(9,1);
  lcd.print(tempEnd);
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Region");
  lcd.setCursor(8,0);
  lcd.print(region);
  lcd.setCursor(0,1);
  lcd.print("Slope        C/s");
  lcd.setCursor(8,1);
  lcd.print(slope);
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Region");
  lcd.setCursor(8,0);
  lcd.print(region);
  lcd.setCursor(0,1);
  lcd.print("Time         sec");
  lcd.setCursor(7,1);
  lcd.print(time);
  delay(3000);
}

/********************
 * 
 * shutDown()
 * 
 ********************/
void shutDown()
{
  while (0!=1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Exceeded 300F!!!");
    lcd.setCursor(0,1);
    lcd.print("ShutDown & Reset");
    delay(1000);
  }
}

/********************
 * 
 * Statistics()
 * 
 ********************/
void Statistics(double* DesiredPeakTemp, double* ActualPeakTemp, double* PercentError){
  double DPT = 0;
  for (int i = 0; i <= 5; i++){
    if (DesiredPeakTemp[i] > DPT){
      DPT = DesiredPeakTemp[i];
    }
  }

  double APT = 0;
  for (int i = 0; i <= 5; i++){
    if (ActualPeakTemp[i] > APT){
      APT = ActualPeakTemp[i];
    }
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DesiredPeakTemp");
  lcd.setCursor(0,1);
  lcd.print(DPT);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ActualPeakTemp");
  lcd.setCursor(0,1);
  lcd.print(APT);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reg1PercentError");
  lcd.setCursor(0,1);
  lcd.print(PercentError[0]);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reg2PercentError");
  lcd.setCursor(0,1);
  lcd.print(PercentError[1]);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reg3PercentError");
  lcd.setCursor(0,1);
  lcd.print(PercentError[2]);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reg4PercentError");
  lcd.setCursor(0,1);
  lcd.print(PercentError[3]);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reg5PercentError");
  lcd.setCursor(0,1);
  lcd.print(PercentError[4]);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reg6PercentError");
  lcd.setCursor(0,1);
  lcd.print(PercentError[5]);
  delay(2000);
}

/********************
 * 
 * UserInput()
 * 
 ********************/
double UserInput(int numbers, double lowval, double highval, int name)
{
  double value;
  int hundreds, tens, ones, place;

  lcd.clear();
  lcd.setCursor(0,0);
  switch (name) {
  case 1:
    lcd.print("Region1TempFinal");
    break;
  case 2:
    lcd.print("Region1Slope");
    break;
  case 3:
    lcd.print("Region2Time");
    break;
  case 4:
    lcd.print("Region3Slope");
    break;
  case 5:
    lcd.print("Region3TempFinal");
    break;
  case 6:
    lcd.print("Region56Time");
    break;
  case 7:
    lcd.print("Region7Slope");
    break;
  }

  if (numbers==3){

    hundreds = 0;
    tens = 0;
    ones = 0;
    place = 1;

    value = hundreds*100 + tens*10 + ones;
    String valueString= String(hundreds)+String(tens)+String(ones);
    lcd.setCursor(0,1);
    lcd.print(valueString);

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
          value = hundreds*100 + tens*10 + ones;
          String valueString = String(hundreds)+String(tens)+String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
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
          value = hundreds*100 + tens*10 + ones;
          String valueString = String(hundreds)+String(tens)+String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
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
          value = hundreds*100 + tens*10 + ones;
          String valueString = String(hundreds)+String(tens)+String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
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
          value = hundreds*100 + tens*10 + ones;
          String valueString = String(hundreds)+String(tens)+String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
          delay(400);
          break;
        }
      case btnSELECT:
        {
          value = hundreds*100 + tens*10 + ones;
          if (value>highval || value<lowval) {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Min Val:");
            lcd.setCursor(10,0);
            lcd.print(lowval);
            lcd.setCursor(0,1);
            lcd.print("Max Val:");
            lcd.setCursor(10,1);
            lcd.print(highval);
            delay(3000);
            hundreds = 0;
            tens = 0;
            ones = 0;
            value = hundreds*100 + tens*10 + ones;
            String valueString = String(hundreds)+String(tens)+String(ones);

            lcd.clear();
            lcd.setCursor(0,0);
            switch (name) {
            case 1:
              lcd.print("Region1TempFinal");
              break;
            case 2:
              lcd.print("Region1Slope");
              break;
            case 3:
              lcd.print("Region2Time");
              break;
            case 4:
              lcd.print("Region3Slope");
              break;
            case 5:
              lcd.print("Region3TempFinal");
              break;
            case 6:
              lcd.print("Region56Time");
              break;
            case 7:
              lcd.print("Region7Slope");
              break;
            }
            lcd.setCursor(0,1);
            lcd.print(valueString);
            delay(400);
          } 
          else{
            delay(400); 
            return value;
          }
          break;
        }
      }
    }
  }
  else if (numbers==2){ 
    tens = 0;
    ones = 0;

    place = 1;
    value=tens*10 + ones;
    String valueString = String(tens)+String(ones);
    lcd.setCursor(0,1);
    lcd.print(valueString);


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
            if (tens<9) {
              tens = tens + 1;
            } 
            else {
              tens = 0;
            }
          }
          if (place==2) {
            if (ones<9) {
              ones = ones + 1;
            } 
            else {
              ones = 0;
            }
          }
          value = tens*10 + ones;

          String valueString  = String(tens)+String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
          delay(400);
          break;
        }
      case btnDOWN:
        {
          if (place==1) {
            if (tens>0) {
              tens = tens - 1;
            } 
            else {
              tens = 9;
            }
          }
          if (place==2) {
            if (ones>0) {
              ones = ones - 1;
            } 
            else {
              ones = 9;
            }
          }
          value = tens*10 + ones;
          String valueString  = String(tens)+String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
          delay(400);
          break;
        }
      case btnLEFT:
        {
          if (place == 1) {
            place = 2;
          } 
          else if (place == 2) {
            place = 1;
          } 
          value = tens*10 + ones;
          String valueString = String(tens)+String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
          delay(400);
          break;
        }
      case btnRIGHT:
        {
          if (place == 1) {
            place = 2;
          } 
          else if (place == 2) {
            place = 1;
          } 
          value = tens*10 + ones;
          String valueString  = String(tens)+String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
          delay(400);
          break;
        }
      case btnSELECT:
        {
          value = tens*10 + ones;
          if (value>highval || value<lowval) {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Min Val:");
            lcd.setCursor(10,0);
            lcd.print(lowval);
            lcd.setCursor(0,1);
            lcd.print("Max Val:");
            lcd.setCursor(10,1);
            lcd.print(highval);
            delay(3000);
            tens = 0;
            ones = 0;
            value = tens*10 + ones;
            String valueString  = String(tens)+String(ones);
            lcd.clear();
            lcd.setCursor(0,0);
            switch (name) {
            case 1:
              lcd.print("Region1TempFinal");
              break;
            case 2:
              lcd.print("Region1Slope");
              break;
            case 3:
              lcd.print("Region2Time");
              break;
            case 4:
              lcd.print("Region3Slope");
              break;
            case 5:
              lcd.print("Region3TempFinal");
              break;
            case 6:
              lcd.print("Region56Time");
              break;
            case 7:
              lcd.print("Region7Slope");
              break;
            }
            lcd.setCursor(0,1);
            lcd.print(valueString);
            delay(400);
          } 
          else{
            delay(400);
            return value;
          }
          break;
        }
      }
    }
  }
  else if (numbers==1){
    ones = 0;

    value=ones;
    String valueString = String(ones);
    lcd.setCursor(0,1);
    lcd.print(valueString);


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
          if (ones<9) {
            ones = ones + 1;
          } 
          else {
            ones = 0;
          }
          value = ones;

          String valueString = String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
          delay(400);
          break;
        }
      case btnDOWN:
        {
          if (ones>0) {
            ones = ones - 1;
          } 
          else {
            ones = 9;
          }
          value = ones;
          String valueString = String(ones);
          lcd.setCursor(0,1);
          lcd.print(valueString);
          delay(400);
          break;
        }
      case btnSELECT:
        {
          value = ones;
          if (value>highval || value<lowval) {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Min Val:");
            lcd.setCursor(10,0);
            lcd.print(lowval);
            lcd.setCursor(0,1);
            lcd.print("Max Val:");
            lcd.setCursor(10,1);
            lcd.print(highval);
            delay(3000);
            ones = 0;
            value = ones;
            String valueString = String(ones);
            lcd.clear();
            lcd.setCursor(0,0);
            switch (name) {
            case 1:
              lcd.print("Region1TempFinal");
              break;
            case 2:
              lcd.print("Region1Slope");
              break;
            case 3:
              lcd.print("Region2Time");
              break;
            case 4:
              lcd.print("Region3Slope");
              break;
            case 5:
              lcd.print("Region3TempFinal");
              break;
            case 6:
              lcd.print("Region56Time");
              break;
            case 7:
              lcd.print("Region7Slope");
              break;
            }
            lcd.setCursor(0,1);
            lcd.print(valueString);
            delay(400);
          } 
          else{
            delay(400);
            return value;
          }

          break;
        }
      }
    }
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Something Wrong");
    lcd.setCursor(0,1);
    lcd.print("Fix Code");
  }
}

