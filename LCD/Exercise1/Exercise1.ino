/*

This exercise completes both Objectives 1 & 2

Objective 1: Automatically accelerate the scrolling text as it is pushed off of the screen (at both ends of the screen)
- Can clearly see that the text moves faster as it approaches the edges of the screen and comes back onto the screen.
Objective 2: Replace the text with a character that we create.
- Text replaced with a custom-made sword character, repeated 13 times to match the length of the original text.

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// create sword character
byte sword[8] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B11111,
  B00100,
  B00100,
};

// draws 13 swords on the display
void setup() {
  lcd.createChar(0, sword);
  lcd.begin(16, 2);
  for (int numSword = 1; numSword <= 13; numSword++){
    lcd.write(byte(0));
  }
  delay(1000);
}

void loop() {
  // scroll 8 positions to the left at normal rate
  for (int positionCounter = 0; positionCounter < 8; positionCounter++) {
    lcd.scrollDisplayLeft(); 
    delay(300);
  }

  // scroll 5 positions to the left at a faster rate
  // accelerate scrolling as it pushes swords off the screen
  for (int positionCounter = 0; positionCounter < 5; positionCounter++) {
    lcd.scrollDisplayLeft(); 
    delay(50);
  }

  // scroll 5 positions to the right at a faster rate
  // accelerate scrolling as it begins to bring back swords from off the screen
  for (int positionCounter = 0; positionCounter < 5; positionCounter++) {
    lcd.scrollDisplayRight(); 
    delay(50);
  }

  // scroll 19 positions to the right at normal rate
  for (int positionCounter = 0; positionCounter < 19; positionCounter++) {
    lcd.scrollDisplayRight(); 
    delay(300);
  }

  // scroll 5 positions to the right at a faster rate
  // accelerate scrolling as it pushes swords off the screen
  for (int positionCounter = 0; positionCounter < 5; positionCounter++) {
    lcd.scrollDisplayRight(); 
    delay(50);
  }

  // scroll 5 positions to the left at a faster rate
  // ccelerate scrolling as it begins to bring back swords from off the screen
  for (int positionCounter = 0; positionCounter < 5; positionCounter++) {
    lcd.scrollDisplayLeft(); 
    delay(50);
  }

  // scroll 11 positions to the left at normal rate
  // brings swords back to original position
  for (int positionCounter = 0; positionCounter < 11; positionCounter++) {
    lcd.scrollDisplayLeft(); 
    delay(300);
  }

  // delay at the end of the full loop
  delay(1000);

}
