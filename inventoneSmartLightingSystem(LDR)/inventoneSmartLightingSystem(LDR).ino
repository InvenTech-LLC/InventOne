#define LDR 0
#define RELAY 13

void setup() {
     pinMode(LDR, INPUT);
     pinMode(RELAY, OUTPUT);
     Serial.begin(9600);
}

void loop() {
     int value = analogRead(LDR);
     Serial.println(value);

     //When the light intensity is much, the LDR becomes a
     //shortcircuit and we get a HIGH on the LDR pin.

     if (value <= 512){
         digitalWrite(RELAY, LOW);
         Serial.println("I'm alive");
     }

     //Switch on the relay when we have low light intensity.

     else {
         digitalWrite(RELAY, HIGH);
            }
     delay(500);
}
