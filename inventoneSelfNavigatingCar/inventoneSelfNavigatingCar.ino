#include <Servo.h>
#include <Ultrasonic.h>
#include <Drive.h>

#define ECHO 15 //D1
#define TRIGGER 16  //D9
#define SERVO 14  //D3
#define MAX_DISTANCE 200 

const int IN1 = 5;  //D6
const int IN2 = 4;  //D5
const int IN3 = 12; //D8
const int IN4 = 13; //D7
 
Servo myservo;
Drive drive(IN1, IN2, IN3, IN4);
Ultrasonic ultrasonic(TRIGGER,ECHO);

int rightDistance;
int leftDistance;

void setup() {
  Serial.begin(9600);
  myservo.attach(SERVO);
 }

void loop() {
  lookForward();
  
  while(findDistance() >= 30){
    drive.moveForward(500);
    Serial.println("Moving forward");
    delay(100);
    }
    
  drive.stopMoving();
  Serial.println("Stopped moving");

  rightDistance = lookRight();
  leftDistance = lookLeft();

  if (leftDistance > rightDistance){
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

