#include <Arduino.h>


// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  #ifndef ESP32
    #define ESP32
  #endif
#endif


#include <IPAddress.h>
#include <WiFiGeneric.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);


  IPAddress apIP(192,168,4,1);
  IPAddress gwIP(192,168,4,1);
  IPAddress subnet(255,255,255,0);

  WiFi.softAPConfig(apIP, gwIP, subnet);




}

void loop() {
  delay(1000);
}
