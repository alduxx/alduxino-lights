/*- Wifi -*/
ESP8266WebServer server(80);
IPAddress ip(192,168,100,110);
IPAddress gateway(192,168,100,1);
IPAddress subnet(255,255,255,0);

// Auxiliar variables to store the current output state
String d8State = "off";
String output4State = "off";


/*=========================================================================*/
/*=                           WIFI SETUP                                  =*/
/*=========================================================================*/
void setupWifi(){
    WiFi.config(ip, gateway, subnet);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("");
    Serial.println("Will wait for connection now...");

    // wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("ip address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);
    // server.on("/inline", []() {server.send(200, "text/plain", "this works as well");});
    server.on("/d8/on/", d8on);
    server.on("/d8/off/", d8off);

    server.onNotFound(handleNotFound);

    server.begin();

    Serial.println("HTTP server started");
}

void d8on() {
    d8State = "on";
    digitalWrite(D8, HIGH);
    handleRoot();
}

void d8off() {
    d8State = "off";
    digitalWrite(D8, LOW);
    handleRoot();
}

/*=========================================================================*/
/*=                           HANDLE ROOT                                 =*/
/*=========================================================================*/
void handleRoot() {
    String message = "<!DOCTYPE html><html>";
    message += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    message += "<link rel=\"icon\" href=\"data:,\">";
    message += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
    message += ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;";
    message += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
    message += ".button2 {background-color: #77878A;}</style></head>";
    message += "<body><h1>ESP8266 Web Server</h1>";

    message += "<p>GPIO 5 - State " + d8State + "</p>";
    if (d8State=="off") {
      message += "<p><a href=\"/d8/on/\"><button class=\"button\">ON</button></a></p>";
    } else {
      message += "<p><a href=\"/d8/off/\"><button class=\"button button2\">OFF</button></a></p>";
    }

    message += "<p>GPIO 4 - State " + output4State + "</p>";
    if (output4State=="off") {
      message += "<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>";
    } else {
      message += "<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>";
    }

    message += "<p>";

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
    message += "</p>";

    message += "</body></html>";

    server.send(200, "text/html", message);
}

/*=========================================================================*/
/*=                          HANDLE NOT FOUND                             =*/
/*=========================================================================*/
void handleNotFound() {
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
}
