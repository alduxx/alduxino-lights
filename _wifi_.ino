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

    server.onNotFound(handleNotFound);

    server.begin();

    Serial.println("HTTP server started");
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
