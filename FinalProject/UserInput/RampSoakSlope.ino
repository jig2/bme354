float selectSlope()
{
  float slopeThresh;

  int ones = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Soak Slope");
  String slopeString = String(ones);
  lcd.setCursor(0,1);
  lcd.print(slopeString);


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
        float slopeThresh = ones;

        String slopeString = String(ones);
        lcd.setCursor(0,1);
        lcd.print(slopeString);
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
        float slopeThresh = ones;
        String slopeString = String(ones);
        lcd.setCursor(0,1);
        lcd.print(slopeString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float slopeThresh =ones;
        if (slopeThresh>3 || slopeThresh<1) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Outside Range");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          ones = 0;
          float SlopeThresh =ones;
          String slopeString =String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Select A Slope");
          lcd.setCursor(0,1);
          lcd.print(slopeString);
          delay(400);
        } else{
          return slopeThresh;
        }
        break;
      }
    }
  }
}
