#include "AlarmSystem.h"
#include "MotionDetector.h"
#include "UltraSonicSensor.h"
#include "GasSensor.h"
#include "FlameSensor.h"

#define MMBuzzerPin 4
#define AWLedPin 6
#define AKLedPin 5

AlarmSystem alarmSystem(AKLedPin, AWLedPin, MMBuzzerPin);

// add/remove all the sensors that you are using here and the pins they need
#define PIR_PIN 7
MotionDetector motionDetector(PIR_PIN);

#define US_Trig_PIN 3
#define US_Echo_PIN 2
UltraSonicSensor ultraSonicSensor(US_Trig_PIN, US_Echo_PIN);

#define Gas_PIN A0
GasSensor gasSensor(Gas_PIN);

#define IR_Flame_PIN A1
FlameSensor flameSensor(IR_Flame_PIN);

void setup() {
  Serial.begin(9600);
  // Add all the sensors you are using here, e.g., alarmSystem.addSensor(&anotherSensor);
  alarmSystem.addSensor(&motionDetector);
  alarmSystem.addSensor(&ultraSonicSensor);
  alarmSystem.addSensor(&gasSensor);
  alarmSystem.addSensor(&flameSensor);
  alarmSystem.setup();
}

void loop() {
  alarmSystem.loop();
}