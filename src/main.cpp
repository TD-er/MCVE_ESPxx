#include <Arduino.h>

#include <WiFi.h>

#include <Wire.h>

// Needed due to preprocessor issues.
#ifdef PLUGIN_SET_GENERIC_ESP32
  #ifndef ESP32
    #define ESP32
  #endif
#endif

const uint8_t gpio_pins[]{
  23,     22,     21,    19,    18,    5
};

constexpr size_t nrPins = sizeof(gpio_pins) / sizeof(gpio_pins[0]);


void setup() {
  Serial.begin(115200);

  for (size_t i = 0; i < nrPins; ++i) {
    pinMode(gpio_pins[i], OUTPUT);
  }

  Wire.begin();
  Wire1.begin();
  Wire.end();


  // Reset default SDA/SCL
//  gpio_reset_pin(static_cast<gpio_num_t>(21));
//  gpio_reset_pin(static_cast<gpio_num_t>(22));


  delay(100);

  Serial.println("Setup done");
}

void loop() {
  Serial.println("Start looping GPIO pins");

  int counter = 0;
  bool state = true;

  for (;;) {
    for (size_t i = 0; i < nrPins; ++i) {
//      pinMode(gpio_pins[i], OUTPUT);
      digitalWrite(gpio_pins[i], state);
      Serial.print("Set GPIO ");
      Serial.print(gpio_pins[i]);
      Serial.print(" to: ");
      Serial.println(state ? 1 : 0);
      delay(1000);    
    }
    state = !state;
  }
}