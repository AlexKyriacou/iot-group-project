#include "AlarmSystem.h"
#include "MotionDetector.h"

#define PIR_PIN 7
#define LED_PIN 6

AlarmSystem alarmSystem(LED_PIN);
MotionDetector motionDetector(PIR_PIN);


void setup() {
  Serial.begin(9600);
  alarmSystem.addSensor(&motionDetector);
  // Add other sensor instances here, e.g., alarmSystem.addSensor(&anotherSensor);

  alarmSystem.setup();
}

void loop() {
  alarmSystem.loop();
}