float SoakTemp()
{
  float SoakThresh;

  int tens = 0;
  int ones = 0;

  int place = 1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select A Temp");
  String SoakString = String(tens) + String(ones);
  lcd.setCursor(0,1);
  lcd.print(SoakString);


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
        float SoakThresh = tens*10 + ones;

        String tempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(tempString);
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
        float SoakThresh = tens*10 + ones;
        String SoakString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(SoakString);
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
        float SoakThresh = tens*10 + ones;
        String SoakString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(SoakString);
        delay(400);
        break;
      }
    case btnRIGHT:
      {
        if (place == 1) {
          place = 2;
        } 
        else {
          place = 1;
        }
        float SoakThresh = tens*10 + ones;
        String tempString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(SoakString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float SOakThresh = tens*10 + ones;
        if (SoakThresh>300 || SoakThresh<20) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("You suck!");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          tens = 0;
          ones = 0;
          float SoakThresh = tens*10 + ones;
          String SoakString = String(tens) + String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Select A Temp");
          lcd.setCursor(0,1);
          lcd.print(SoakString);
          delay(400);
        } else{
          return SoakThresh;
        }
        break;
      }
    }
  }
}
