#include "AlarmSystem.h"
#include <ArduinoJson.h>

#define PRINT_INTERVAL 1000  // 1 second

AlarmSystem::AlarmSystem(int pirPin, int ledPin)
  : motionDetector(pirPin), motionLed(ledPin), alarmArmed(false), lastPrintTime(0) {}

void AlarmSystem::setup() {
  motionDetector.setup();
  motionLed.setup();
}

void AlarmSystem::loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    String command = CommandManager::deserializeCommand(message);
    handleCommand(command);
  }

  updateMotionLed();
  printMotionStatus();
}

void AlarmSystem::handleCommand(const String &command) {
  if (command == "arm") {
    alarmArmed = true;
  } else if (command == "disarm") {
    alarmArmed = false;
  }
}

void AlarmSystem::updateMotionLed() {
  if (alarmArmed && motionDetector.isMotionDetected()) {
    motionLed.on();
  } else {
    motionLed.off();
  }
}

void AlarmSystem::printMotionStatus() {
  unsigned long currentTime = millis();
  if (currentTime - lastPrintTime >= PRINT_INTERVAL) {
    JsonDocument motionData = motionDetector.getJsonData();
    serializeJson(motionData, Serial);
    Serial.println();
    lastPrintTime = currentTime;
  }
}