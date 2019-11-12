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
void oldHandleRoot() {
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


void handleRoot() {
    String html = "<!DOCTYPE html>";
    html += "<html lang=en dir=ltr>";
    html += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<meta charset=utf-8>";
    html += "<title>Casa Container</title>";
    html += "<link href=\"https://fonts.googleapis.com/css?family=Montserrat:400,500,600,700,800&display=swap\" rel=stylesheet>";
    html += "<style media=screen>body,html{background:#cbdffe;height:100%;padding:0;margin:0;font-family:Montserrat,sans-serif}.head{background:#4d91fc;height:25%;text-align:center;color:#FFF;position:relative;padding-top:.5em}head>h1{margin:0;font-weight:700}.status_geral{display:block;padding-top:0}.status_geral>strong{color:#40e74e;padding-top:.5em;font-weight:600}.consumo_geral{display:block;position:absolute;bottom:1.5em;left:0;right:0}.button_row{width:400px;margin:0 auto;padding:2em}.button_row>a{float:left;margin-right:20px}.switch{width:120px;height:120px;background:#f3f7ff;border:1px solid #CCC;border-radius:10px;position:relative;box-shadow:3px 3px 8px #999}.switch>svg{position:absolute;top:30px;left:50%;transform:translate(-50%,0)}.switch_status{position:absolute;top:10px;right:10px;font-size:.7em}.switch_status.on{color:#40e74e}.switch_status.off{color:#658ba3}.switch_label{position:absolute;top:75px;font-size:.8em;font-weight:600;color:#111;left:50%;transform:translate(-50%,0)}.switch_area{position:absolute;bottom:10px;font-size:.7em;color:#658ba3;left:50%;transform:translate(-50%,0)}</style>";
    html += "</head>";
    html += "<body>";
    html += "<div class=head>";
    html += "<h1>Casa Container</h1>";
    html += "<span class=status_geral>status <strong>UP</strong><span>";
    html += "<span class=consumo_geral>Consumo <strong>2,54</strong> kW/h<span>";
    html += "</span></span></span></span></div>";
    html += "<div class=body>";
    html += "<div class=button_row>";
    if (d8State=="off") {
        html += "<a href='/d8/on/'>";
    } else {
        html += "<a href='/d8/off/'>";
    }
    html += "<div class=switch>";
    if (d8State=="off") {
        html += "<span class=\"switch_status off\">OFF</span>";
    } else {
        html += "<span class=\"switch_status on\">ON</span>";
    }
    html += "<svg xmlns=http://www.w3.org/2000/svg height=32 width=22 version=1.1 viewBox=\"0 0 210 297\">";
    html += "<g fill=#fff transform=matrix(4.9063,0,0,4.9063,-48.173,-8.7829)>";
    if (d8State=="off") {
        html += "<path fill=#BBB";
    } else {
        html += "<path fill=#f8a006";
    }
    html += " d=\"m46.888 11.515a3.5 3.5 0 0 0 1.4 -6.314 3.464 3.464 0 0 0 -2.417 -0.595 3.5 3.5 0 0 0 -3.371 -2.606h-21a3.48 3.48 0 0 0 -2.477 1.022 3.491 3.491 0 0 0 2.058 5.936l-3.969 0.7a3.5 3.5 0 0 0 -1.4 6.314 3.488 3.488 0 0 0 2.615 0.579l1.843-0.325 5.371 0.946-8.43 1.486a3.5 3.5 0 0 0 -1.4 6.314 3.488 3.488 0 0 0 2.615 0.579l1.842-0.325 5.125 0.9-8.183 1.442a3.5 3.5 0 0 0 -1.4 6.314 3.47 3.47 0 0 0 2.615 0.579l0.675-0.116v0.839a3 3 0 0 0 -2 2.816v3.32a8.988 8.988 0 0 0 3.143 6.833l3.857 3.307v3.54a7 7 0 0 0 7 7h2a7 7 0 0 0 7 -7v-3.54l3.857-3.306a8.992 8.992 0 0 0 3.143 -6.834v-3.32a3 3 0 0 0 -2 -2.816v-5.422l1.888-0.333a3.5 3.5 0 0 0 1.4 -6.314 3.458 3.458 0 0 0 -2.615 -0.579l-0.216 0.038-5.122-0.9 6.554-1.155a3.5 3.5 0 0 0 1.4 -6.314 3.462 3.462 0 0 0 -2.574 -0.582l-5.379-0.949zm-25.388-4.515a1.5 1.5 0 1 1 0 -3h21a1.5 1.5 0 0 1 1.388 0.937l-11.704 2.063zm-3.52 7.581a1.5 1.5 0 0 1 -1.737 -1.217 1.5 1.5 0 0 1 1.217 -1.738l28.56-5.035a1.492 1.492 0 0 1 1.12 0.249 1.5 1.5 0 0 1 -0.6 2.706zm6.02 18.883v1.536h-3v-1.007zm2 1.536v-1.889l12-2.111v4zm-7 3a1 1 0 0 1 1 -1h24a1 1 0 0 1 1 1v2h-26zm19 16h-12v-2h12zm-2 5a5.028 5.028 0 0 1 -3 1h-2a4.984 4.984 0 0 1 -4.891 -4h11.782a5.024 5.024 0 0 1 -1.891 3zm6.556-12.365-3.926 3.365h-13.26l-3.926-3.365a6.986 6.986 0 0 1 -2.407 -4.635h25.926a6.986 6.986 0 0 1 -2.407 4.635zm0.444-11.635h-3v-4.357l3-0.529zm3.02-10.495a1.492 1.492 0 0 1 1.12 0.249 1.5 1.5 0 0 1 -0.6 2.706l-28.56 5.035a1.5 1.5 0 0 1 -1.737 -1.217 1.5 1.5 0 0 1 1.217 -1.738zm-6.32-0.916-8.649 1.525-5.125-0.9 8.651-1.525zm6.582-8.021a1.5 1.5 0 0 1 1.473 1.24 1.5 1.5 0 0 1 -1.217 1.738l-28.558 5.035a1.5 1.5 0 0 1 -1.737 -1.217 1.5 1.5 0 0 1 1.217 -1.738l28.56-5.035a1.472 1.472 0 0 1 0.264 -0.023zm-6.338-0.936-8.644 1.523-5.372-0.946 8.649-1.524z\"/>";
    html += "</g>";
    html += "</svg>";
    html += "<span class=switch_label>Pergolado</span>";
    html += "<span class=switch_area>Externo</span>";
    html += "</div>";
    html += "</a>";
    html += "<a href=/d7/on/>";
    html += "<div class=switch>";
    html += "<span class=\"switch_status off\">OFF</span>";
    html += "<svg xmlns=http://www.w3.org/2000/svg height=32 width=22 version=1.1 viewBox=\"0 0 210 297\">";
    html += "<g fill=#fff transform=matrix(4.9063,0,0,4.9063,-48.173,-8.7829)>";
    html += "<path fill=#f8a006 d=\"m46.888 11.515a3.5 3.5 0 0 0 1.4 -6.314 3.464 3.464 0 0 0 -2.417 -0.595 3.5 3.5 0 0 0 -3.371 -2.606h-21a3.48 3.48 0 0 0 -2.477 1.022 3.491 3.491 0 0 0 2.058 5.936l-3.969 0.7a3.5 3.5 0 0 0 -1.4 6.314 3.488 3.488 0 0 0 2.615 0.579l1.843-0.325 5.371 0.946-8.43 1.486a3.5 3.5 0 0 0 -1.4 6.314 3.488 3.488 0 0 0 2.615 0.579l1.842-0.325 5.125 0.9-8.183 1.442a3.5 3.5 0 0 0 -1.4 6.314 3.47 3.47 0 0 0 2.615 0.579l0.675-0.116v0.839a3 3 0 0 0 -2 2.816v3.32a8.988 8.988 0 0 0 3.143 6.833l3.857 3.307v3.54a7 7 0 0 0 7 7h2a7 7 0 0 0 7 -7v-3.54l3.857-3.306a8.992 8.992 0 0 0 3.143 -6.834v-3.32a3 3 0 0 0 -2 -2.816v-5.422l1.888-0.333a3.5 3.5 0 0 0 1.4 -6.314 3.458 3.458 0 0 0 -2.615 -0.579l-0.216 0.038-5.122-0.9 6.554-1.155a3.5 3.5 0 0 0 1.4 -6.314 3.462 3.462 0 0 0 -2.574 -0.582l-5.379-0.949zm-25.388-4.515a1.5 1.5 0 1 1 0 -3h21a1.5 1.5 0 0 1 1.388 0.937l-11.704 2.063zm-3.52 7.581a1.5 1.5 0 0 1 -1.737 -1.217 1.5 1.5 0 0 1 1.217 -1.738l28.56-5.035a1.492 1.492 0 0 1 1.12 0.249 1.5 1.5 0 0 1 -0.6 2.706zm6.02 18.883v1.536h-3v-1.007zm2 1.536v-1.889l12-2.111v4zm-7 3a1 1 0 0 1 1 -1h24a1 1 0 0 1 1 1v2h-26zm19 16h-12v-2h12zm-2 5a5.028 5.028 0 0 1 -3 1h-2a4.984 4.984 0 0 1 -4.891 -4h11.782a5.024 5.024 0 0 1 -1.891 3zm6.556-12.365-3.926 3.365h-13.26l-3.926-3.365a6.986 6.986 0 0 1 -2.407 -4.635h25.926a6.986 6.986 0 0 1 -2.407 4.635zm0.444-11.635h-3v-4.357l3-0.529zm3.02-10.495a1.492 1.492 0 0 1 1.12 0.249 1.5 1.5 0 0 1 -0.6 2.706l-28.56 5.035a1.5 1.5 0 0 1 -1.737 -1.217 1.5 1.5 0 0 1 1.217 -1.738zm-6.32-0.916-8.649 1.525-5.125-0.9 8.651-1.525zm6.582-8.021a1.5 1.5 0 0 1 1.473 1.24 1.5 1.5 0 0 1 -1.217 1.738l-28.558 5.035a1.5 1.5 0 0 1 -1.737 -1.217 1.5 1.5 0 0 1 1.217 -1.738l28.56-5.035a1.472 1.472 0 0 1 0.264 -0.023zm-6.338-0.936-8.644 1.523-5.372-0.946 8.649-1.524z\"/>";
    html += "</g>";
    html += "</svg>";
    html += "<span class=switch_label>Parede</span>";
    html += "<span class=switch_area>Externo</span>";
    html += "</div>";
    html += "</a>";
    html += "</div>";
    html += "</div>";
    html += "</body>";
    html += "</html>";

    server.send(200, "text/html", html);
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
