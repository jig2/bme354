float selectSoakSlope()
{
  float slopeSoakThresh;

  int ones = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Soak Slope");
  String SslopeString = String(ones);
  lcd.setCursor(0,1);
  lcd.print(SslopeString);


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
        float slopeSoakThresh = ones;

        String SslopeString = String(ones);
        lcd.setCursor(0,1);
        lcd.print(SslopeString);
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
        float slopeSoakThresh = ones;
        String SslopeString = String(ones);
        lcd.setCursor(0,1);
        lcd.print(SslopeString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float slopeSoakThresh =ones;
        if (slopeSoakThresh>3 || slopeSoakThresh<1) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Outside Range");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          ones = 0;
          float slopeSoakThresh =ones;
          String SslopeString =String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Soak Slope");
          lcd.setCursor(0,1);
          lcd.print(SslopeString);
          delay(400);
        } else{
          return slopeSoakThresh;
        }
        break;
      }
    }
  }
}
