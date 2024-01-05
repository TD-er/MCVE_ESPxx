#include <Arduino.h>


// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  #ifndef ESP32
    #define ESP32
  #endif
#endif

#define COL 12
#define ROW 4

String str;
float myfloat[COL][ROW];
int idx;


void setup() {
  idx = 0;
  Serial.begin(115200);
  for (int i = 0; i < COL; ++i) {
    for (int j = 0; j < ROW; ++j) {
      ++idx;
      myfloat[i][j] = 1.0f * idx;
    }
  }
}

void loop() {
  ++idx;
  if (idx >= (COL*ROW)) {
    idx = 0;
  }

  str = myfloat[idx / ROW][idx % ROW];
  Serial.print(F("str: '"));
  Serial.print(str);
  Serial.print(F("' '"));
  Serial.print(String(myfloat[idx / ROW][idx % ROW], 2));
  Serial.println('\'');
  delay(1000);
}
