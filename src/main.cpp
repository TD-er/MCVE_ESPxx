#include <Arduino.h>

#include <WiFi.h>

// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  #ifndef ESP32
    #define ESP32
  #endif
#endif
#include "WiFi.h"


//#define SER Serial0
#define SER USBSerial
//#define SER_BEGIN  SER.begin(115200, SERIAL_8N1, 44, 43)
#define SER_BEGIN  SER.begin(115200)


void setup() {
  SER_BEGIN;
  SER.end();
  delay(100);
  SER_BEGIN;
}

void loop()
{
  if (SER.available())  {
    bool done = false;
    SER.println();
    while (!done) {
      int c = SER.read();
      if (c < 0) {
        done = true;
      } else {
        SER.print((char)c);
      }
    }
    SER.println();
  }
  SER.write('.');
  delay(1000);
}