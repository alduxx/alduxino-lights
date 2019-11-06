/*- Real Time Clock -*/
RTC_DS1307 RTC;

void setupRTC(){
    Wire.begin();
    RTC.begin();

    if(!RTC.isrunning()){
        Serial.println("RTC is not running. Adjusting...");
        RTC.adjust(DateTime(__DATE__, __TIME__));
    }
}
