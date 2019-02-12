#include "config.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define FAN_PIN 15 //D1
#define TV_PIN 14 //D3
#define LIGHT_PIN 2 //D4
#define JUG_PIN 4 //D5
#define DHT_PIN 5 //D6
#define PIR_PIN 13 //D7
#define ALARM_PIN 12 //D8
#define POWER_LED 16 //D9
#define LED 0 //D2

DHT_Unified dht(DHT_PIN, DHT22);

AdafruitIO_Feed *digital = io.feed("switches");
AdafruitIO_Feed *temperature = io.feed("temperature");
AdafruitIO_Feed *humidity = io.feed("humidity");
AdafruitIO_Feed *motion = io.feed("motion");
AdafruitIO_Feed *security = io.feed("security");

void setup() {
  
  pinMode(FAN_PIN, OUTPUT);
  pinMode(TV_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(JUG_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(POWER_LED, OUTPUT);
  
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // initialize dht22
  dht.begin();
  
  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  
  digital->onMessage(handleMessage);
  security->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  digital->get();
  security->get();

}

void loop() {
  io.run();
  getTemperature_Humidity();
  watchDog();
}

void handleMessage(AdafruitIO_Data *data) {

  if (data->toString() == "Live") {
    Serial.println("Home up and running Sir!");
    for(int i=0; i<800; i+=50){
      analogWrite(POWER_LED, i);
      analogWrite(LED, i);
      delay(200);
    }
  }
  else if(data->toString() == "Sleep") {
    Serial.println("Home going to bed Sir!");
    digital->save("Off-Light");
    digital->save("Off-TV");
    digital->save("Off-Fan");
 
    for(int i=800; i>=0; i-=50){
      analogWrite(POWER_LED, i);
      analogWrite(LED, i);
      delay(200);
    }
  }

  if (data->toString() == "Alarm On"){
    triggerAlarm();
    security->save("Alarm On");
  }else if(data->toString() == "Alarm Off"){
    digitalWrite(ALARM_PIN, LOW);
  }

  if (data->toString() == "On-Fan"){
    Serial.println("Fan coming on");
    digitalWrite(FAN_PIN, LOW);
  } else if(data->toString() == "Off-Fan") {
    Serial.println("Fan coming off");
    digitalWrite(FAN_PIN, HIGH);
  } else if(data->toString() == "On-TV") {
    Serial.println("TV coming on");
    digitalWrite(TV_PIN, LOW);
  } else if(data->toString() == "Off-TV") {
    Serial.println("TV coming off");
    digitalWrite(TV_PIN, HIGH);
  } else if(data->toString() == "On-Light") {
    Serial.println("Light coming on");
    digitalWrite(LIGHT_PIN, LOW);
  } else if(data->toString() == "Off-Light") {
    Serial.println("Light coming off");
    digitalWrite(LIGHT_PIN, HIGH);
  } else if(data->toString() == "On-Jug") {
    Serial.println("Jug coming on");
    digitalWrite(JUG_PIN, LOW);
  } else if(data->toString() == "Off-Jug") {
    Serial.println("Jug coming off");
    digitalWrite(JUG_PIN, HIGH);
  }
  
}


void getTemperature_Humidity() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  float celsius = event.temperature;

//  Serial.print("celsius: ");
//  Serial.print(celsius);
//  Serial.println("C");

  // save fahrenheit (or celsius) to Adafruit IO
  temperature->save(celsius);

  dht.humidity().getEvent(&event);

//  Serial.print("humidity: ");
//  Serial.print(event.relative_humidity);
//  Serial.println("%");

  // save humidity to Adafruit IO
  humidity->save(event.relative_humidity);

  // wait 5 seconds (5000 milliseconds == 5 seconds)
  delay(2000);
}

void watchDog() {
 
  if (digitalRead(PIR_PIN) == HIGH) {
      Serial.println("* Motion detected at home");
      motion->save("Motion");
    }
  else {
      Serial.println("* No movements at home yet!.");
      motion->save("No motion at home");
    }
  delay(2000);
}

void triggerAlarm() {
  Serial.println("ALARM TRIGGERED");
//  for(int hz=440; hz<100; hz++) {
//    tone(ALARM_PIN, 220, 50); 
//    delay(5);
//  }
//  noTone(ALARM_PIN);
//  for(int hz=1000; hz>440; hz--) {
//    tone(ALARM_PIN, hz, 50);
//    delay(5);  
//  }
  digitalWrite(ALARM_PIN, HIGH);
  noTone(ALARM_PIN);
}
