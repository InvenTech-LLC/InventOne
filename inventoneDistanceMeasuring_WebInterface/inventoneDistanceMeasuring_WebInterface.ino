/*
 * Distance measuring using HCSR04 lib
 * 
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <HCSR04.h>
#include "index.h"  //Web page

#define TRIG_PIN 13
#define ECHO_PIN 12

HCSR04 hc(TRIG_PIN, ECHO_PIN);   //initialisation class HCSR04 (trig pin , echo pin)

//SSID and Password of your WiFi router
const char* ssid = "ESP8266_WIFI";
const char* password = "123456789";

ESP8266WebServer server(80); //Server on port 80

//===============================================================
//     This routine is executed when you open its IP in browser
//===============================================================

void handleRoot() {
  String s = MAIN_page; 
  int Distance; 
  Distance = hc.dist();  //Read distance from ultrasonic sensor
  Serial.print("Distance is: ");
  Serial.println(Distance);
  //Convert Temperature int to String then Replace @@temp@@ in HTML with temperaure value
  s.replace("@@temp@@",String(Distance));  
  server.send(200, "text/html", s); //Send webpage to browser
}

//===============================================================
//                  SETUP
//===============================================================

void setup(void){
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only
  Serial.begin(9600);
  Serial.println("");

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
  Serial.println(WiFi.localIP());  //IP address of ESP
 
  server.on("/", handleRoot); //handle root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

//===============================================================
//                     LOOP
//===============================================================

void loop(void){
  server.handleClient();          //Handle client requests
}
