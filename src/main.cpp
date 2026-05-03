#include <Arduino.h>

#include <WiFi.h>

// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  #ifndef ESP32
    #define ESP32
  #endif
#endif
#include "WiFi.h"




void setup() {
  Serial.begin(115200);
}

void loop()
{
  if (Serial.available())  Serial.read();
}