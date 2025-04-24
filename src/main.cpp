#include <Arduino.h>

#include <WiFi.h>

#include <Wire.h>

// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  #ifndef ESP32
    #define ESP32
  #endif
#endif



void setup() {
  Serial.begin(115200);

  delay(100);

  Serial.println("Setup done");
}

void loop() {
  Serial.println("Start looping GPIO pins");


  for (;;) {
    delay(1000);
    Serial.print('.');
  }
}