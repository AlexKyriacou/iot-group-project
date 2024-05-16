#include "AlarmSystem.h"
#include <ArduinoJson.h>

#define PRINT_INTERVAL 1000  // 1 second

AlarmSystem::AlarmSystem(int aKLedPin, int aWLedPin, int mMBuzzerPin)
  : aKLed(aKLedPin), aWLed(aWLedPin), mMBuzzer(mMBuzzerPin), alarmArmed(false), gasThreshold(350), flameThreshold(800), distanceThreshold(40), lastPrintTime(0), numSensors(0) {}

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
  aKLed.setup();
  aWLed.setup();
  mMBuzzer.setup();
}

void AlarmSystem::loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    String command = CommandManager::deserializeCommand(message);
    handleCommand(command);
  }

  updateAlarms();
  printSensorStatus();
}

void AlarmSystem::handleCommand(const String& command) {
  if (command == "arm") {
    alarmArmed = true;
  } else if (command == "disarm") {
    alarmArmed = false;
  } else {
    int delimiterIndex = command.indexOf('/');
    if (delimiterIndex != -1) {
      String commandType = command.substring(0, delimiterIndex);
      String valueStr = command.substring(delimiterIndex + 1);
      int value = valueStr.toInt();

      if (commandType == "gasThreshold") {
        gasThreshold = value;
      } else if (commandType == "flameThreshold") {
        flameThreshold = value;
      } else if (commandType == "distanceThreshold") {
        distanceThreshold = value;
      }
    }
  }
  updateAlarms();
}

void AlarmSystem::updateAlarms() {
  // Turn off all LEDs if the alarm is disarmed
  if (!alarmArmed) {
    aKLed.off();
    aWLed.off();
    mMBuzzer.off();
    return;
  }

  bool motionDetected = false;
  bool distanceExceeded = false;
  bool gasDetected = false;
  bool flameDetected = false;

  for (int i = 0; i < numSensors; i++) {
    Sensor* sensor = sensors[i];

    if (sensor->getType() == "motionDetector") {
      if (sensor->isDetected()) {
        motionDetected = true;
      }
    } else if (sensor->getType() == "ultraSonicSensor") {
      if (sensor->value() < distanceThreshold) {
        distanceExceeded = true;
      }
    } else if (sensor->getType() == "gasSensor") {
      if (sensor->value() > gasThreshold) {
        gasDetected = true;
      }
    } else if (sensor->getType() == "flameSensor") {
      if (sensor->value() < flameThreshold) {
        flameDetected = true;
      }
    }
  }

  // Update LEDs based on sensor states
  if (motionDetected) {
    aKLed.on();
  } else {
    aKLed.off();
  }

  if (distanceExceeded) {
    aWLed.on();
  } else {
    aWLed.off();
  }

  if (gasDetected || flameDetected) {
    mMBuzzer.on();
  } else {
    mMBuzzer.off();
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

    // Include current threshold values
    combinedData["gasThreshold"] = gasThreshold;
    combinedData["flameThreshold"] = flameThreshold;
    combinedData["distanceThreshold"] = distanceThreshold;

    serializeJson(combinedData, Serial);
    Serial.println();
    
    lastPrintTime = currentTime;
  }
}