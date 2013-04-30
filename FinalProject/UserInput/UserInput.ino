// include the library code
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define button signifiers
#define btnNONE 0
#define btnSELECT 1
#define btnLEFT 2
#define btnDOWN 3
#define btnUP 4
#define btnRIGHT 5

// define voltage thresholds for each button (obtained from Objective 3)
#define vSELECT 3.5
#define vLEFT 2.5
#define vDOWN 1.5
#define vUP 0.75
#define vRIGHT 0.25

// reads what button is being pushed
int read_button()
{
  // obtain ADC reading from analog pin A0
  float adc_in = analogRead(0);
  // map ADC reading (range = 0:1023) onto voltage value (range = 0V:5V)
  float voltage_in = adc_in/1023*5;

  // based on the measured thresholds from Objective 3, determines what button is being pushed
  if (voltage_in > vSELECT) return btnNONE;
  if (voltage_in < vRIGHT) return btnRIGHT;
  if (voltage_in < vUP) return btnUP;
  if (voltage_in < vDOWN) return btnDOWN;
  if (voltage_in < vLEFT) return btnLEFT;
  if (voltage_in < vSELECT) return btnSELECT;
  return btnNONE;
}

float PreheatThresh;
float slopeSoakThresh;
float SoakTimeThresh;
float PeakThresh;
float slopePeakThresh;
float ReflowTimeThresh;
float ReflowThresh;

void setup(){
  lcd.begin(16,2);
  lcd.clear();

  // RamptoSoakTemp()

  int hundreds = 0;
  int tens = 0;
  int ones = 0;

  int place = 1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Preheat Temp");
  String PreheattempString = String(hundreds) + String(tens) + String(ones);
  lcd.setCursor(0,1);
  lcd.print(PreheattempString);

  int nextCase = 0;
  while (nextCase!=1) {

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
        PreheatThresh = hundreds*100 + tens*10 + ones;

        String PreheattempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(PreheattempString);
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
        PreheatThresh = hundreds*100 + tens*10 + ones;
        String PreheattempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(PreheattempString);
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
        PreheatThresh = hundreds*100 + tens*10 + ones;
        String PreheattempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(PreheattempString);
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
        PreheatThresh = hundreds*100 + tens*10 + ones;
        String PreheattempString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(PreheattempString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        PreheatThresh = hundreds*100 + tens*10 + ones;
        if (PreheatThresh>170 || PreheatThresh<130) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Outside of Range");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          hundreds = 0;
          tens = 0;
          ones = 0;
          float PreheatThresh = hundreds*100 + tens*10 + ones;
          String PreaheattempString = String(hundreds) + String(tens) + String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Preheat Temp");
          lcd.setCursor(0,1);
          lcd.print(PreheattempString);
          delay(400);
        } 
        else{
          nextCase = 1;
          delay(400);
        }
        break;
      }
    }
  }

  // selectSoakSlope()



  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Soak Slope");
  String SslopeString = String(ones);
  lcd.setCursor(0,1);
  lcd.print(SslopeString);


  nextCase = 0;
  while (nextCase!=1) {

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
        } 
        else{
          nextCase = 1;
          delay(400);
        }
        break;
      }
    }
  }

  // SoakTime()


  hundreds = 0;
  tens = 0;
  ones = 0;

  place = 1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Soak Time");
  String StimeString = String(hundreds) + String(tens) + String(ones);
  lcd.setCursor(0,1);
  lcd.print(StimeString);


  nextCase = 0;
  while (nextCase!=1) {

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
        float SoakTimeThresh = hundreds*100 + tens*10 + ones;

        String StimeString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(StimeString);
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
        float SoakTimeThresh = hundreds*100 + tens*10 + ones;
        String StimeString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(StimeString);
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
        float SoakTimeThresh = hundreds*100 + tens*10 + ones;
        String StimeString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(StimeString);
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
        float SoakTimeThresh = hundreds*100 + tens*10 + ones;
        String StimeString = String(hundreds) + String(tens) + String(ones);
        lcd.setCursor(0,1);
        lcd.print(StimeString);
        delay(400);
        break;
      }
    case btnSELECT:
      {
        float SoakTimeThresh = hundreds*100 + tens*10 + ones;
        if (SoakTimeThresh>120 || SoakTimeThresh<60) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Outside of Range");
          lcd.setCursor(0,1);
          lcd.print("Resetting!");
          delay(5000);
          hundreds = 0;
          tens = 0;
          ones = 0;
          float SoakTimeThresh = hundreds*100 + tens*10 + ones;
          String StimeString = String(hundreds) + String(tens) + String(ones);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Soak Time");
          lcd.setCursor(0,1);
          lcd.print(StimeString);
          delay(400);
        } 
        else{
          nextCase = 1;
          delay(400);
        }
        break;
      }
    }
  }

  // PeakTemp()


  hundreds = 0;
  tens = 0;
  ones = 0;

  place = 1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Peak Temp");
  String PeaktempString = String(hundreds) + String(tens) + String(ones);
  lcd.setCursor(0,1);
  lcd.print(PeaktempString);


  nextCase = 0;
  while (nextCase!=1) {

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
        if (PeakThresh>237 || PeakThresh<197) {
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
          nextCase = 1;
          delay(400);
        }
        break;
      }
    }
  }

  // selectPeakSlope()


  ones = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Peak Slope");
  String PslopeString = String(ones);
  lcd.setCursor(0,1);
  lcd.print(PslopeString);


  nextCase = 0;
  while (nextCase!=1) {

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
        } 
        else{
          nextCase = 1;
          delay(400);
        }
        break;
      }
    }
  }

  // ReflowTime()


  tens = 0;
  ones = 0;

  place = 1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reflow Time");
  String ReflowTimeString = String(tens) + String(ones);
  lcd.setCursor(0,1);
  lcd.print(ReflowTimeString);


  nextCase = 0;
  while (nextCase!=1) {

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
        } 
        else{
          nextCase = 1;
          delay(400);
        }
        break;
      }
    }
  }

  // selectReflowSlope()


  ones = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reflow Slope");
  String ReflowString = String(ones);
  lcd.setCursor(0,1);
  lcd.print(ReflowString);


  nextCase = 0;
  while (nextCase!=1) {

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
        } 
        else{
          nextCase = 1;
          delay(400);
        }
        break;
      }
    }
  }

  Serial.begin(9600);
  Serial.print(PreheatThresh);
  Serial.print(slopeSoakTresh);

}

void loop(){
  lcd.clear();
  Checking(PreheatThresh, slopeSoakThresh, SoakTimeThresh, PeakThresh, slopePeakThresh, ReflowTimeThresh, ReflowThresh);
  delay(1000);
}

void Checking(float PreheatThresh, float slopeSoakThresh, float SoakTimeThresh, float PeakThresh, float slopePeakThresh, float ReflowTimeThresh, float ReflowThresh){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Soak Temp");
  lcd.setCursor(0,1);
  lcd.print(PreheatThresh);
  delay(400);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Soak Slope");
  lcd.setCursor(0,1);
  lcd.print(slopeSoakThresh);
  delay(400);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Soak Time");
  lcd.setCursor(0,1);
  lcd.print(SoakTimeThresh);
  delay(400);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reflow Temp");
  lcd.setCursor(0,1);
  lcd.print(PeakThresh);
  delay(400);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Slope to Reflow");
  lcd.setCursor(0,1);
  lcd.print(slopePeakThresh);
  delay(400);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reflow Time");
  lcd.setCursor(0,1);
  lcd.print(ReflowTimeThresh);
  delay(400);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reflow Slope");
  lcd.setCursor(0,1);
  lcd.print(ReflowThresh);
  delay(400);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("OK?");
  lcd.setCursor(0,1);
  lcd.print("UP=YES DOWN=NO");

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
        break;
      }
    case btnDOWN:
      {
        setup();
      }
    }
  }
}


