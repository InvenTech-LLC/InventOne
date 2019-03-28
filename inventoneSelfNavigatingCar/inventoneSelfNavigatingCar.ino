#include <Servo.h>
#include <Ultrasonic.h>
#include <Drive.h>

#define ECHO 2 //D7
#define TRIGGER 14  //D8
#define SERVO 15  //D5
#define MAX_DISTANCE 200

//Define L298N pin mappings
const int IN1 = 16;  //D4
const int IN2 = 12; //D3
const int IN3 = 13; //D2
const int IN4 = 4;  //D1

Servo myservo;
Drive drive(IN1, IN2, IN3, IN4);
Ultrasonic ultrasonic(TRIGGER, ECHO);

int rightDistance;
int leftDistance;

void setup() {
  Serial.begin(9600);
  myservo.attach(SERVO);
}

void loop() {
  lookForward();

  while (findDistance() >= 20) {
    drive.moveForward(500);
    Serial.println("Moving forward");
    delay(100);
  }

  drive.stopMoving();
  Serial.println("Stopped moving");

  rightDistance = lookRight();
  leftDistance = lookLeft();

  if (leftDistance > rightDistance) {
    drive.turnLeft(500);
    Serial.println("Turning left");
    delay(500);
    drive.stopMoving();
  }

  else if (rightDistance > leftDistance) {
    drive.turnRight(500);
    Serial.println("Turning right");
    delay(500);
    drive.stopMoving();
  }
  else {
    drive.moveBackward(500);
    delay(500);
    drive.stopMoving();
  }

  delay(1000);
}
//Help the robot know the last turn it made so it doesn't repeat it
//Also check if the turns are correct
