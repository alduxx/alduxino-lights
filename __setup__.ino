void setup() {
    Serial.print("Starting program...");
    Serial.begin(9600);

    /* setup Real Time Clock - _rtc_.ino */
    setupRTC();

    /* setup wifi and Http Server -  _wifi_.ino */
    setupWifi();

    /* setup relays -  _relays__.ino */
    setupRelays();

    Serial.print("Setup ended...");
}
