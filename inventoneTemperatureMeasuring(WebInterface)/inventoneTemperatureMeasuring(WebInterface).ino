/*
 * Temperature Monitoring Web Server Connects to your Router
 * circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include "index.h"  //Web page

#define DHTPIN 12     // what digital pin we're connected to (D8)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

//SSID and Password of your WiFi router
const char* ssid = "ESP8266_WIFI";
const char* password = "123456789";

ESP8266WebServer server(80); //Server on port 80
DHT dht(DHTPIN, DHTTYPE);

//===============================================================
//     This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
  String s = MAIN_page; 
  int Temperature; 
  Temperature = (int)dht.readTemperature();  //Read Analog Voltage of ADC Pin
  Serial.print("Temperature is: ");
  Serial.println(Temperature);
  //Convert Temperature int to String then Replace @@temp@@ in HTML with temperaure value
  s.replace("@@temp@@",String(Temperature));  
  server.send(200, "text/html", s); //Send webpage to browser
}

//===============================================================
//                  SETUP
//===============================================================
void setup(void){
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, password);     //Connect to your WiFi router
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
