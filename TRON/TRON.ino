#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <FS.h>
#include <Robot.h>
#include <Drive.h>
#include <ESP8266HTTPUpdateServer.h>

#define DBG_OUTPUT_PORT Serial
#define ECHO 15 //D1
#define TRIGGER 16  //D9
#define SERVO 14  //D3
#define MANUAL 0
#define SELF_DRIVE 1

//bool Move();
//bool Right();
//bool Left();
//bool Brake();
//bool Accel();
//bool Gear1();
//bool Gear2();
//bool Gear3();
//bool autoDrive();

const int IN1 = 5;  //D6
const int IN2 = 4;  //D5
const int IN3 = 12; //D8
const int IN4 = 13; //D7

Drive drive(IN1, IN2, IN3, IN4);

int g;
int s;
int d;
int rightDist;
int leftDist;

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 2, 1);
DNSServer dnsServer;
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

Robot robot(IN1, IN2, IN3, IN4);
//holds the current upload
File fsUploadFile;

//format bytes
String formatBytes(size_t bytes) {
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  } else {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

String getContentType(String filename) {
  if (server.hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}

bool handleFileRead(String path) {
  DBG_OUTPUT_PORT.println("handleFileRead: " + path);
  if (path.endsWith("/")) {
    path += "index.html";
  }
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz)) {
      path += ".gz";
    }
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void setup(void) {
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.print("\n");
  DBG_OUTPUT_PORT.setDebugOutput(true);
  SPIFFS.begin();
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      DBG_OUTPUT_PORT.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    DBG_OUTPUT_PORT.printf("\n");
  }

  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNS_PORT, "www.tron.io", apIP);

  //myservo.attach(SERVO);
  robot.setup(SERVO, TRIGGER, ECHO);

  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("TRON", "robotcar");

  //SERVER INIT
  server.on("/move", HTTP_GET, Move);
  server.on("/gear1", HTTP_GET, Gear1);
  server.on("/gear2", HTTP_GET, Gear2);
  server.on("/gear3", HTTP_GET, Gear3);
  server.on("/right", HTTP_GET, Right);
  server.on("/left", HTTP_GET, Left);
  server.on("/brake", HTTP_GET, Brake);
  server.on("/accel", HTTP_GET, Accel);
  server.on("/autodrive", HTTP_GET, autoDrive);

  //use it to load content from SPIFFS
  server.onNotFound([]() {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "FileNotFound");
    }
  });

  server.begin();
  DBG_OUTPUT_PORT.println("HTTP server started");

}

void loop(void) {
  server.handleClient();
  dnsServer.processNextRequest();
}
