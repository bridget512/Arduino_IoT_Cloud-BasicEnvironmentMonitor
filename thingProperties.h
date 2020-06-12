#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char THING_ID[] = "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx";

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)

float rHumidity;
float rPressure;
float rTempIndex;
float rTemperature;

void initProperties(){

  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(rHumidity, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(rPressure, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(rTempIndex, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(rTemperature, READ, ON_CHANGE, NULL);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
