bool autoDrive() {
//  g = robot.gear(4);
    Gear4();
   
    robot.lookForward();
    Serial.print("Distance is: ");
    Serial.println(robot.findDistance());
    
    while(robot.findDistance() >= 20){
      drive.moveForward(500);
      Serial.println("Moving forward");
      //server.handleClient();
      Serial.print("Gear is: ");
      Serial.println(g);
      
      if(g != 4){
        Serial.println("breaking out of auto mode");
        return true;
        }
      delay(100);
      
      }
    
    drive.stopMoving();
    Serial.println("Stopped moving");

    rightDist = robot.lookRight();
    leftDist = robot.lookLeft();

    if (leftDist > rightDist){
      drive.turnLeft(500);
      Serial.println("Turning left");
      delay(500);
      drive.stopMoving();
      }
    else if (rightDist > leftDist) {
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
      
      server.send(200, "text/html", "resend");
}

//Help the robot know the last turn it made so it doesn't repeat it
//Also check if the turns are correct
