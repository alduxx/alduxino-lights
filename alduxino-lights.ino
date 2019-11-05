#include <Wire.h>
#include "RTClib.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

/*- Wifi consts -*/
const char* WIFI_SSID = "container_repeater";
const char* WIFI_PASSWORD = "isabella";

/*- Wifi -*/
ESP8266WebServer server(80);
IPAddress ip(192,168,100,111);
IPAddress gateway(192,168,100,1);
IPAddress subnet(255,255,255,0);

/*- Real Time Clock -*/
RTC_DS1307 RTC;


void setup() {
    Serial.print("Iniciando...");
    Serial.begin(9600);

    setupRTC();

    WiFi.config(ip, gateway, subnet);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("");

    Serial.println("Will wait for connection now...");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);

    // server.on("/inline", []() {server.send(200, "text/plain", "this works as well");});

    server.onNotFound(handleNotFound);

    server.begin();

    Serial.println("HTTP server started");
}

void setupRTC(){
    Wire.begin();
    RTC.begin();

    if(!RTC.isrunning()){
        Serial.println("RTC is not running. Adjusting...");
        RTC.adjust(DateTime(__DATE__, __TIME__));
    }
}

/*=========================================================================*/
/*=                               LOOP                                    =*/
/*=========================================================================*/
void loop() {
    server.handleClient();
}

/*=========================================================================*/
/*=                           HANDLE ROOT                                 =*/
/*=========================================================================*/
void handleRoot() {
    String message = "Root route\n\n";

    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }

    DateTime now = RTC.now();
    message += "\nTime now is: ";
    message += now.hour();
    message += ":";
    message += now.minute();
    message += ":";
    message += now.second();
    message += " ";
    message += now.day();
    message += "/";
    message += now.month();
    message += "/";
    message += now.year();

    server.send(404, "text/plain", message);
}

/*=========================================================================*/
/*=                          HANDLE NOT FOUND                             =*/
/*=========================================================================*/
void handleNotFound() {
  //digitalWrite(PIN_LED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
//  digitalWrite(PIN_LED, 0);
}


