/*This code controls LED using a button and inventone dev. board
 * Please connect 10k resistor to protect LED from getting burnt
 */
//Define pins for LED and button
int LED = 12;
int Button = 13;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT);
//Begin serial monitor communication
  Serial.begin(9600);
}

void loop() {
//Check if button has been pressed
  if(digitalRead(Button) == HIGH){
    digitalWrite(LED, HIGH);
    Serial.println("LED is ON");
  }
  else {
//Ensure that LED doesn't come ON
    digitalWrite(LED, LOW);
    Serial.println("LED is OFF");
  }
  delay(500);
}
