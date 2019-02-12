/*This code opens a door when a person approaches the door and shuts the door when no one
is present.
Please ensure you set Jumper on the PIR to come ON only when the person approaches and stays
close to the door (check PIR datasheet for more info)*/
//Define the pins for PIR sensor and Servo
int servo = 16;
int PIR = 13;
void setup() {
  pinMode(servo, OUTPUT);
  pinMode(PIR, INPUT);
//Begin serial monitor communication
  Serial.begin(9600);
}

void loop() {  
//Check if PIR has sensed motion or not
  if(digitalRead(PIR) == HIGH){
    Serial.println("Motion Detected");
//Open the door  
    digitalWrite(servo, HIGH);
    }
  else{ 
    Serial.println("No motion detected");
//Ensure the door doesn't open
    digitalWrite(servo,LOW);
  }
   delay(3000);
}
