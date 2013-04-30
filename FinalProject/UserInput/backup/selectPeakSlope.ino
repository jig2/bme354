float selectPeakSlope()

  {float slopePeakThresh;

  int ones = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Peak Slope");
  String PslopeString = String(ones);
  lcd.setCursor(0,1);
  lcd.print(PslopeString);


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
        float slopePeakThresh = ones;

        String PslopeString = String(ones);
        lcd.setCursor(0,1);
        lcd.print(PslopeString);
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
        float slopePeakThresh = ones;
        String PslopeString = String(ones);
        lcd.setCursor(0,1);
        lcd.print(PslopeString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float slopePeakThresh =ones;
        if (slopePeakThresh>3 || slopePeakThresh<1) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Outside Range");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          ones = 0;
          float SlopePeakThresh =ones;
          String PslopeString =String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Peak Slope");
          lcd.setCursor(0,1);
          lcd.print(PslopeString);
          delay(400);
        } else{
          return slopePeakThresh;
        }
        break;
      }
    }
  }
}

