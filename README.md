# alduxino-lights
Arduino Project for Home Lights Automation

Create a file named _secret_.ino and fill the variables:

`
/\*- Wifi consts -\*/
const char\* WIFI_SSID = "your_wifi_ssid";
const char\* WIFI_PASSWORD = "your_wifi_password";
`

Using arduino-cli:


Compiling the code: (One dir up)
`arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 alduxino-lights/`

Uploading the code: (Replace port with your own)
`arduino-cli upload -p /dev/ttyUSB0 --fqbn esp8266:esp8266:nodemcuv2 alduxino-lights/`

List ports:
`ls -l /dev/ttyUS*`

Serial Monitor: (Replace port with your own)
`cu -9600 -l /dev/ttyUSB0`

If you get permission denied on upload, try:
`sudo chmod a+rw /dev/ttyUSB0`
