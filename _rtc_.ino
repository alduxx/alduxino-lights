/*- Real Time Clock -*/
RTC_DS1307 RTC;

void setupRTC(){
    Wire.begin();
    RTC.begin();

    if(!RTC.isrunning()){
        Serial.println("RTC is not running. Adjusting...");
        RTC.adjust(DateTime(__DATE__, __TIME__));
    } else {
        Serial.println("RTC was already running. Time:");
        DateTime now = RTC.now();
        String message = "\nTime now is: ";
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
        Serial.println(message);
    }
}
