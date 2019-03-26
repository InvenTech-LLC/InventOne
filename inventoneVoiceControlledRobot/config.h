/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "iLad"
#define IO_KEY         "7626a2b1069646ab96d1f6db1ab053d9"

/******************************* WIFI **************************************/

#define WIFI_SSID       "InvenTech"
#define WIFI_PASS       "1234567890"

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
