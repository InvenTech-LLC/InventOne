
bool Move(){
  s = robot.move();
  if(g == 1){
    DBG_OUTPUT_PORT.print("Driving at: ");
    DBG_OUTPUT_PORT.println(s);
    server.send(200, "text/html", String(s));
    return true;
  }
  else if(g == 2){
    DBG_OUTPUT_PORT.print("Reversing at: ");
    DBG_OUTPUT_PORT.println(s);
    server.send(200, "text/html", String(s));
    return true;
  }
  else if(g == 3){
    DBG_OUTPUT_PORT.print("Park: ");
    DBG_OUTPUT_PORT.println(s);
    server.send(200, "text/html", String(s));
    return true;
  }
  else if(g == 4){
    DBG_OUTPUT_PORT.print("Auto-Drive.... ");
    DBG_OUTPUT_PORT.println(s);
    server.send(200, "text/html", String(s));
    return true;
  }
  else {
    DBG_OUTPUT_PORT.print("Wrong gear: ");
    DBG_OUTPUT_PORT.println(g);
    server.send(200, "text/html", String(s));
    return true;
  }
}
bool Right(){
  s = robot.turnRight();
  DBG_OUTPUT_PORT.print("Turning right: ");
  DBG_OUTPUT_PORT.println(s);
  server.send(200, "text/html", String(s)); 
  return true;
  }
bool Left(){
  s = robot.turnLeft();
  DBG_OUTPUT_PORT.print("Turning left: ");
  DBG_OUTPUT_PORT.println(s);
  server.send(200, "text/html", String(s));
  return true;
  }
bool Brake(){
  s = robot.brake();
  DBG_OUTPUT_PORT.print("Brake: ");
  DBG_OUTPUT_PORT.println(s);
  Move();
  //server.send(200, "text/html", String(s));
  return true;
  }
bool Accel(){
  s = robot.accelerate();
  DBG_OUTPUT_PORT.print("Accelerating: ");
  DBG_OUTPUT_PORT.println(s);
  Move();
  //server.send(200, "text/html", String(s));
  return true;
  }
bool Gear1(){
  //Change gear to drive
  g = robot.gear(1);
  DBG_OUTPUT_PORT.print("gear: ");
  DBG_OUTPUT_PORT.println(g);
  Move();
  //server.send(200, "text/html", String(g));
  return true;
  }
bool Gear2(){
  //Change gear to reverse
  g = robot.gear(2);
  DBG_OUTPUT_PORT.print("gear: ");
  DBG_OUTPUT_PORT.println(g);
  Move();
  //server.send(200, "text/html", String(g));
  return true;
  }
bool Gear3(){
  //Change gear to park
  g = robot.gear(3);
  DBG_OUTPUT_PORT.print("gear: ");
  DBG_OUTPUT_PORT.println(g);
  Move();
  //server.send(200, "text/html", String(g));
  return true;
  }
bool Gear4(){
  //Change gear to auto-drive
  g = robot.gear(4);
  DBG_OUTPUT_PORT.print("gear: ");
  DBG_OUTPUT_PORT.println(g);
  //server.send(200, "text/html", String(g));
  return true; 
  }
