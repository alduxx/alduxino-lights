const schedule lightsSchedule[] {
    {"D5", "19:30:00", "22:00:00"},
    {"D6", "19:30:00", "22:00:00"},
    {"D7", "19:30:00", "22:00:00"},
    {"D8", "19:30:00", "22:00:00"}
};

void setupRelays(){
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);

    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, HIGH);

    for(uint8_t i = 0; i < sizeof(lightsSchedule)/sizeof(schedule); ++i) {
        Serial.println(lightsSchedule[i].pin);
        Serial.println(lightsSchedule[i].timeStart);
        Serial.println(lightsSchedule[i].timeEnd);
    }

}
