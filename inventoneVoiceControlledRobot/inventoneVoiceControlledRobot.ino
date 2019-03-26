/************************** Configuration ***********************************/
#include "config.h"
#include <Drive.h>

/************************ Example Starts Here *******************************/

//Define L298N pin mappings
const int IN1 = 16; //D9
const int IN2 = 12; //D8
const int IN3 = 13; //D7
const int IN4 = 5;  //D6

Drive drive(IN1, IN2, IN3, IN4);

const int speed = 500;

// set up the 'counter' feed
AdafruitIO_Feed *control_centre = io.feed("Control");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  Serial.println();
  Serial.print("Connecting to Adafruit IO");
  Serial.println();


  // connect to io.adafruit.com
  io.connect();
  control_centre->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  control_centre->get();

}

void loop() {
  io.run();
}

void handleMessage(AdafruitIO_Data *data) {

  if(data->toString() == "Forward") {
    Serial.println("Moving forward");
    drive.moveForward(speed);
    
  }else if(data->toString() == "Backward") {
    Serial.println("Moving backwards");
    drive.moveBackward(speed);
    
  }else if(data->toString() == "Right") {
    Serial.println("Turning right");
    drive.turnLeft(speed);
    
  }else if(data->toString() == "Left") {
    Serial.println("Turning left");
    drive.turnRight(speed);
    
  } else if(data->toString() == "Stop") {
    Serial.println("Stop!!!");
    drive.stopMoving();
  }

}
