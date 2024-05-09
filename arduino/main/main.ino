#include "AlarmSystem.h"
#include "MotionDetector.h"

#define LED_PIN 6

AlarmSystem alarmSystem(LED_PIN);

// add/remove all the sensors that you are using here and the pins they need
#define PIR_PIN 7
MotionDetector motionDetector(PIR_PIN);


void setup() {
  Serial.begin(9600);
  // Add all the sensors you are using here, e.g., alarmSystem.addSensor(&anotherSensor);
  alarmSystem.addSensor(&motionDetector);

  alarmSystem.setup();
}

void loop() {
  alarmSystem.loop();
}