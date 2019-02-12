/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "Your Adafruit IO Username"
#define IO_KEY         "You Adafruit IO Key"

/******************************* WIFI **************************************/

#define WIFI_SSID       "Your WiFi Name"
#define WIFI_PASS       "Your WiFi Password"

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
