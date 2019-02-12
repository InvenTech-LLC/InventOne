//Define the pins for PIR sensor and alarm
int Alarm = 16;
int PIR = 13;
void setup() {
  pinMode(Alarm, OUTPUT);
  pinMode(PIR, INPUT);
//Begin serial monitor communication
  Serial.begin(9600);
}

void loop() {  
//Check if PIR has sensed motion or not
  if(digitalRead(PIR) == HIGH){
    Serial.println("Motion Detected");
//Turn ON the alarm  
    digitalWrite(Alarm, HIGH);
    }
  else{ 
    Serial.println("No motion detected");
//Ensure the alarm doesn't come on
    digitalWrite(Alarm,LOW);
  }
   delay(3000);
}
