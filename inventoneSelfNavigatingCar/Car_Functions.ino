
int lookRight() {
  myservo.write(0);
  delay(1000);
  int distance = findDistance();
  return distance;
  }

int lookLeft() {
  myservo.write(180);
  delay(1000);
  int distance = findDistance();
  return distance;
  }

int lookForward() {
  myservo.write(90);
  delay(1000);
  int distance = findDistance();
  return distance;
  }

int findDistance(){
  int distance = ultrasonic.read();
  if(distance >= MAX_DISTANCE){
    return MAX_DISTANCE;
    }
  else{
    return distance;
  }
 }
