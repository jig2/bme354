float selectReflowSlope()
{
  float ReflowThresh;

  int ones = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reflow Slope");
  String ReflowString = String(ones);
  lcd.setCursor(0,1);
  lcd.print(ReflowString);


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
        float ReflowThresh = ones;

        String ReflowString = String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowString);
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
        float ReflowThresh = ones;
        String ReflowString = String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float ReflowThresh = ones;
        if (ReflowThresh>4 || ReflowThresh<1) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Outside Range");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          ones = 0;
          float ReflowThresh = ones;
          String ReflowString = String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Select A Slope");
          lcd.setCursor(0,1);
          lcd.print(ReflowString);
          delay(400);
        } else{
          return ReflowThresh;
        }
        break;
      }
    }
  }
}
