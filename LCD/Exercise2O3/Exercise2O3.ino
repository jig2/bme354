/*

This exercise completes Objective 3

Objective 3: Display the voltage read from analog pin A0 onto the screen
- Screen displays changing A0 voltage depending on which button is pressed.
- Readings are in Volts.
- If measured voltage is greater than 5 V, then 5.000 V is displayed.
- Readings confirmed by measuring A0 voltage using multimeter.

*/

// include the library code
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
}

void loop() {
  // obtain ADC reading from analog pin A0
  float measure = analogRead(0);
  // map ADC reading (range = 0:1023) onto voltage value (range = 0V:5V)
  float voltage = measure/1023*5;
  
  // print voltage value to thousandths place
  lcd.begin(16,2);
  lcd.print(voltage,3);
  delay(1000);
}
