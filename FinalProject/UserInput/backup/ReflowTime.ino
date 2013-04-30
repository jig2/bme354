float ReflowTime()
{
  float ReflowTimeThresh;

  int tens = 0;
  int ones = 0;

  int place = 1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Preheat Temp");
  String ReflowTimeString = String(tens) + String(ones);
  lcd.setCursor(0,1);
  lcd.print(ReflowTimeString);


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
        float ReflowTimeThresh = tens*10 + ones;

        String ReflowTimeString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowTimeString);
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
        float ReflowTimeThresh = tens*10 + ones;
        String ReflowTimeString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowTimeString);
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
        float ReflowTimeThresh = tens*10 + ones;
        String ReflowTimeString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowTimeString);
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
        float ReflowTimeThresh = tens*10 + ones;
        String ReflowTimeString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowTimeString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float ReflowTimeThresh = tens*10 + ones;
        if (ReflowTimeThresh>75 || ReflowTimeThresh<45) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Outside of Range");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          hundreds = 0;
          tens = 0;
          ones = 0;
          float ReflowTimeThresh = tens*10 + ones;
          String ReflowTimeString = String(tens) + String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Reflow Time");
          lcd.setCursor(0,1);
          lcd.print(ReflowTimeString);
          delay(400);
        } else{
          return ReflowTimeThresh;
        }
        break;
      }
    }
  }
}
