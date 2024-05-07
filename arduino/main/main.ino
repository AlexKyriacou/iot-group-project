#include "AlarmSystem.h"

#define PIR_PIN 7
#define LED_PIN 6

AlarmSystem alarmSystem(PIR_PIN, LED_PIN);

void setup() {
  Serial.begin(9600);
  alarmSystem.setup();
}

void loop() {
  alarmSystem.loop();
}