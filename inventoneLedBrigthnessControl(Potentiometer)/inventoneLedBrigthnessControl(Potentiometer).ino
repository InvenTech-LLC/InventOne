/*This sketch is used to regulate the brightness of an LED using the InventOne dev. board
Note that the InventOne board is very sensitive with a maximum ADC port voltage of 1V hence use
appropriate voltage division circuit
*/
//Define LED, Potentiometer pins
int Potentiometer = 0;
int LED = 16;
int Value;

void setup() {
  pinMode(Potentiometer, INPUT);
  pinMode(LED, OUTPUT);
//Begin serial connection
  Serial.begin(9600);
}

void loop() {
//Read voltage level from Potentiometer
  Value = analogRead(Potentiometer);
  Serial.println(Value);
//Write voltage level to LED pin
  analogWrite(LED, Value);
  delay(20);
}
