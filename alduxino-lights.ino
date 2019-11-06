#include <Wire.h>
#include "RTClib.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

/*- Wifi consts -* 
    Create a _secret_.ino and add the following consts with your wifi info:
    const char* WIFI_SSID = "your_wifi_ssid";
    const char* WIFI_PASSWORD = "your_wifi_password";
*/

/*- Wifi -*/
ESP8266WebServer server(80);
IPAddress ip(192,168,100,111);
IPAddress gateway(192,168,100,1);
IPAddress subnet(255,255,255,0);

/*- Real Time Clock -*/
RTC_DS1307 RTC;

/*
See for Setup and Loop functions see:
  __setup__.ino
  __loop__.ino
*/

