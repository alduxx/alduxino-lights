# alduxino-lights
Arduino Project for Home Lights Automation

Create a file named _secret_.ino and fill the variables:

`
/\*- Wifi consts -\*/
const char\* WIFI_SSID = "your_wifi_ssid";
const char\* WIFI_PASSWORD = "your_wifi_password";
`

Using arduino-cli:


For compiling the code:

`arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 alduxino-lights.ino`
