#include <HCSR04.h>
#include <LiquidCrystal_I2C.h>

HCSR04 hc(4,5);   //initialisation class HCSR04 (trig pin , echo pin)
LiquidCrystal_I2C lcd(0x3F, 16, 2); // initialize the LCD with the LCD address and the LCD type
int distance;
void setup()
{ 
  Serial.begin(9600);
  Wire.begin(2, 14); 
  // Initialize the LCD
  lcd.init();
   // Turn ON the LCD back light
  lcd.backlight();
}

void loop()
{ distance = hc.dist();
  Serial.println( distance ); 
  lcd.setCursor(0, 0);  // set the cursor to column 0, line 0
  lcd.print("Distance is: ");
  lcd.println(distance);
  lcd.setCursor(0, 1);
  delay(500);
}//return curent distance in serial
