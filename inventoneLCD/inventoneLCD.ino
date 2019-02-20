// include the library 
#include <LiquidCrystal_I2C.h>

// initialize the LCD with the LCD address and the LCD //type
LiquidCrystal_I2C lcd(0x3F, 16, 2);
//The function works like this:
//LiquidCrystal_I2C lcd(address, length, width);
//length and width are those of the LCD

void setup() {

  Wire.begin(D4, D3);   //Wire.begin(sda_pin, scl_pin);
  // Initialize the LCD
  lcd.init();
  // Turn ON the LCD back light

  lcd.backlight();
}

void loop() {
  //The LCD is indexed from 0, hence (0,0) represents the topmost 

  //left corner of the LCD
  lcd.setCursor(0, 0); //set cursor to column 0,line 0
  lcd.print("Welcome to InvenTech");
  lcd.scrollDisplayLeft();
  delay(500);
}
