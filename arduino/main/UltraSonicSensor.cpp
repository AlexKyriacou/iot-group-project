#include "UltraSonicSensor.h"
float duration;

UltraSonicSensor::UltraSonicSensor(int trigPin, int echoPin)
  : trigPin(trigPin), echoPin(echoPin) {}

void UltraSonicSensor::setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float UltraSonicSensor::value() {
  // Initialise the Ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float dist = (duration*.0343)/2;

  if (dist < 5) {
    tooClose = true;
  }
  
  return dist;
}

bool UltraSonicSensor::isDetected() {
  return tooClose;  // Set the flag to true when an object is too close to the sensor
}

JsonDocument UltraSonicSensor::getJsonData() {
  JsonDocument doc;
  doc["data"]["distance"] = value();
  tooClose = false; // Reset the flag after retrieving the JSON data
  return doc;
}