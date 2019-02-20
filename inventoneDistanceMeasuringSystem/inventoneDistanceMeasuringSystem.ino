/*This code senses the distance of an obastacle using the HC-SR04 ultrasonic sensor*/
int Trigger = 5;
int Echo = 4;
int distance, duration;
void setup() {
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600);
}

void loop() {
//Send sound wave to obstacle
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(1000);
//Stop sending the wave
  digitalWrite(Trigger, LOW);
//Calculate distance from the obstacle using wave reflection
  duration = pulseIn(Echo, HIGH);
  distance = (duration/2)/29.1;
  Serial.print("You are ");
  Serial.print(distance);
  Serial.println(" cm away from the obstacle");
  delay(500);
}
