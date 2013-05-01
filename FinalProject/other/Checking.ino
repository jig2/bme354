int Checking(float variable,float name){
  lcd.clear();
  lcd.setCursor(0,0);
  if (name==1){
    lcd.print("Soak Temp");
  }
  else if (name==2){
    lcd.print("Soak Slope");
  }
  else if (name==3){
    lcd.print("Soak Time");
  }
  else if (name==4){
    lcd.print("Ramp Slope");
  }
  else if (name==5){
    lcd.print("Reflow Temp");
  }
  else if (name==6){
    lcd.print("Reflow Time");
  }
  else if (name==7){
    lcd.print("Reflow Slope");
  }
  else{
    lcd.print("Invalid");
    lcd.setCursor(0,1);
    lcd.print("Start Over");
  }
  lcd.setCursor(0,1);
  lcd.print(variable);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("OK?");
  lcd.setCursor(0,1);
  lcd.print("UP=YES DOWN=NO");
  delay(400);

  int nextcase=0;
  while (nextcase!=1) {

    int button_in = read_button();

    switch(button_in)
    {
    case btnNONE:
      {
        break;
      }
    case btnUP:
      {
        int value=1;
        return value;
      }
    case btnDOWN:
      {
        int value=0;
        return value;
      }
      break;
    }
  }
}




