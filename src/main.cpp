#include <Arduino.h>

#include <WiFi.h>

// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  #ifndef ESP32
    #define ESP32
  #endif
#endif
#include "WiFi.h"


#define SER Serial0
#define SER1 USBSerial
#define SER_BEGIN  SER.begin(115200, SERIAL_8N1, 44, 43)
//#define SER_BEGIN  SER.begin(115200)


void setup() {
  SER1.begin();
  SER_BEGIN;
  SER.end();
  SER1.end();
  delay(100);
  SER1.begin();
  SER_BEGIN;
}

void process(Stream& s) {
  if (s.available())  {
    bool done = false;
    s.println();
    while (!done) {
      int c = s.read();
      if (c < 0) {
        done = true;
      } else {
        s.print((char)c);
      }
    }
    s.println();
  }
  s.write('.');
}

void loop()
{
  process(SER);
  process(SER1);
  delay(1000);
}