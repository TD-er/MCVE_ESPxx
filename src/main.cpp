#include <Arduino.h>

#include <WiFi.h>

// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  #ifndef ESP32
    #define ESP32
  #endif
#endif


void setup() {
  Serial0.begin(115200);
  Serial0.println("\r\nStarting... Starting WiFi STA mode.");
  WiFi.mode(WIFI_MODE_STA);
}

void loop() {}