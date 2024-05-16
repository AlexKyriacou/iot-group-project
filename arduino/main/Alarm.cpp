#include "Alarm.h"
#include <Arduino.h>

Alarm::Alarm(int pin)
  : pin(pin), state(LOW) {}

void Alarm::on() {
  digitalWrite(pin, HIGH);
}

void Alarm::off() {
  digitalWrite(pin, LOW);
}

void Alarm::toggle() {
  digitalWrite(pin, !digitalRead(pin));
}

void Alarm::setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}