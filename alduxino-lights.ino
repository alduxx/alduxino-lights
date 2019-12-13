#include <Wire.h>
#include "RTClib.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

typedef struct {
  char* pin;
  char* timeStart;
  char* timeEnd;
} schedule;


String d8State = "off";

/*
  _rtc_.ino
  _wifi_.ino
  _relays_.ino
  _pushbtn.ino
  _secret_.ino (see README)

For Setup and Loop functions see:
  __setup__.ino
  loop.ino

*/
