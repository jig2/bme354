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

void control(int region, double startT, double endT, double slope, double time, double delayTime)
{
  double Iterations = round(time)/(delayTime/1000);

  for (int i = 1; i <= Iterations; i++) {

    readTemp = getTemp();
    threshold = startT + slope*delayTime/1000*i;

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

double getTemp(){
  double readVal = (double) analogRead(inpin);
  double readTemp = 0.9907*readVal - 13.65;
  
  Serial.begin(9600);
  Serial.println(readVal);
  
  return readTemp;
}

double LCD_ControlSystem(int region,double readTemp,double threshold,int minutesLeft,int secondsLeft){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stage   D      F");
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
  lcd.print("TL  :   A      F");
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

