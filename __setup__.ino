void setup() {
    Serial.println("Starting program...");
    Serial.begin(9600);

    /* setup Real Time Clock - _rtc_.ino */
//    setupRTC();

    /* setup wifi and Http Server -  _wifi_.ino */
    setupWifi();

    /* setup relays -  _relays__.ino */
    setupRelays();

    /* setup push buttons -  _pushbtn_.ino */
//    void setupPushbtn();

    Serial.println("Setup ended...");
}
