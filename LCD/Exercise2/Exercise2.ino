// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  
}

void loop() {
  float measure = analogRead(0);
  float voltage = measure/1023*5;
  
  lcd.begin(16,2);
  lcd.print(voltage,3);
  delay(1000);
}
