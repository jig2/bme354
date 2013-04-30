float PeakTemp()
{
  float PeakThresh;

  int hundreds = 0;
  int tens = 0;
  int ones = 0;

  int place = 1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Peak Temp");
  String PeaktempString = String(hundreds) + String(tens) + String(ones);
  lcd.setCursor(0,1);
  lcd.print(PeaktempString);


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
        float PeakThresh = hundreds*100 + tens*10 + ones;

        String PeaktempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(PeaktempString);
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
        float PeakThresh = hundreds*100 + tens*10 + ones;
        String PeaktempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(PeaktempString);
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
        float PeakThresh = hundreds*100 + tens*10 + ones;
        String PeaktempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(PeaktempString);
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
        float PeakThresh = hundreds*100 + tens*10 + ones;
        String PeaktempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(PeaktempString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float PeakThresh = hundreds*100 + tens*10 + ones;
        if (Peakhresh>237 || PeakThresh<197) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Outside of Range");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          hundreds = 0;
          tens = 0;
          ones = 0;
          float PeakThresh = hundreds*100 + tens*10 + ones;
          String PeaktempString = String(hundreds) + String(tens) + String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Peak Temp");
          lcd.setCursor(0,1);
          lcd.print(PeaktempString);
          delay(400);
        } 
        else{
          return PeakThresh;
        }
        break;
      }
    }
  }
}
