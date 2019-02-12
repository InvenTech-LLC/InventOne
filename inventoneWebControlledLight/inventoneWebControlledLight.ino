/*
 * ESP8266 NodeMCU LED Control over WiFi Demo
 *
 * https://inventone.ng
 */
#include <ESP8266WiFi.h> 
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>

//---------------------------------------------------------------
//Our HTML webpage contents in program memory
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>Welcome to InventOne IoT Platform</h1><br>
Press to switch <a href="relayOn" target="myIframe">ON</a><br>
Press to switch <a href="relayOff" target="myIframe">OFF</a><br>
LED State:<iframe name="myIframe" width="100" height="25" frameBorder="0" margin="0"><br>
<a href="https://inventone.ng">inventone.ng</a><br>

</center>

</body>
</html>
)=====";
//---------------------------------------------------------------
//RELAY Connected to GPIO5
#define RELAY 5 //D6

//SSID and Password of your WiFi router
const char* ssid = "ESP8266_WIFI";
const char* password = "123456789";

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleRELAYon() { 
 Serial.println("RELAY on page");
 digitalWrite(RELAY,LOW); //RELAY is connected in reverse
 server.send(200, "text/html", "ON"); //Send ADC value only to client ajax request
}

void handleRELAYoff() { 
 Serial.println("RELAY off page");
 digitalWrite(RELAY,HIGH); //RELAY off
 server.send(200, "text/html", "OFF"); //Send ADC value only to client ajax request
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Make RELAY port output
  pinMode(RELAY,OUTPUT); 
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/relayOn", handleRELAYon); //as Per  <a href="relayOn">, Subroutine to be called
  server.on("/relayOff", handleRELAYoff);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
