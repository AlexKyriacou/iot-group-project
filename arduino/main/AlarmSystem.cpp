#include "AlarmSystem.h"
#include <ArduinoJson.h>

#define PRINT_INTERVAL 1000  // 1 second

AlarmSystem::AlarmSystem(int ledPin)
  : motionLed(ledPin), alarmArmed(false), lastPrintTime(0), numSensors(0) {}

void AlarmSystem::addSensor(Sensor* sensor) {
  if (numSensors < MAX_SENSORS) {
    sensors[numSensors++] = sensor;
  } else {
    Serial.println("Error: Maximum number of sensors reached.");
  }
}

void AlarmSystem::setup() {
  for (int i = 0; i < numSensors; i++) {
    sensors[i]->setup();
  }
  motionLed.setup();
}

void AlarmSystem::loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    String command = CommandManager::deserializeCommand(message);
    handleCommand(command);
  }

  updateMotionLed();
  printSensorStatus();
}

void AlarmSystem::handleCommand(const String& command) {
  if (command == "arm") {
    alarmArmed = true;
  } else if (command == "disarm") {
    alarmArmed = false;
  }
}

void AlarmSystem::updateMotionLed() {
  bool anyDetected = false;
  for (int i = 0; i < numSensors; i++) {
    if (alarmArmed && sensors[i]->isDetected()) {
      anyDetected = true;
      break;
    }
  }

  if (anyDetected) {
    motionLed.on();
  } else {
    motionLed.off();
  }
}

void AlarmSystem::printSensorStatus() {
  unsigned long currentTime = millis();
  if (currentTime - lastPrintTime >= PRINT_INTERVAL) {
    StaticJsonDocument<1024> combinedData;

    for (int i = 0; i < numSensors; i++) {
      JsonDocument sensorData = sensors[i]->getJsonData();
      // Merge sensorData into combinedData
      for (JsonPair kv : sensorData["data"].as<JsonObject>()) {
        combinedData[kv.key()] = kv.value();
      }
    }

    serializeJson(combinedData, Serial);
    Serial.println();
    
    lastPrintTime = currentTime;
  }
}