float ReflowTemp()
{
  float ReflowThresh;

  int tens = 0;
  int ones = 0;

  int place = 1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select A Temp");
  String ReflowString = String(tens) + String(ones);
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
        float ReflowThresh = tens*10 + ones;

        String ReflowString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowString);
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
        float ReflowThresh = tens*10 + ones;
        String ReflowString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowString);
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
        float ReflowThresh = tens*10 + ones;
        String ReflowString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowString);
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
        float ReflowThresh = tens*10 + ones;
        String ReflowString = String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(ReflowString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float ReflowThresh = tens*10 + ones;
        if (ReflowThresh>300 || ReflowThresh<20) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("You suck!");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          tens = 0;
          ones = 0;
          float ReflowThresh = tens*10 + ones;
          String ReflowString = String(tens) + String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Select A Temp");
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
