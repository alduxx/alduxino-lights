int btn_1 = 0;
int btn_2 = 0;

void setupPushbtn(){
    pinMode(D3, INPUT_PULLUP);
}

void readPushbtn(){
    btn_1 = digitalRead(D3);

    /*Serial.print("btn_1 now is [");
    Serial.print(btn_1);
    Serial.println("]");
    */

    if (btn_1 == LOW) {
        delay(500);
        Serial.println("btn_1 is LOW\n-------------\n");
        if( d8State == "off"){
            digitalWrite(D8, HIGH);
            d8State = "on";
            Serial.println("D8 State ON, port HIGH");
        } else {
            digitalWrite(D8, LOW);
            d8State = "off";
            Serial.println("D8 State OFF ");
            Serial.println("D8 State OFF, port LOW");
        }
    }

}
