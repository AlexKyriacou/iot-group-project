#include "CommandManager.h"

String CommandManager::deserializeCommand(const String &message) {
  JsonDocument doc;

  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  const char *deviceType = doc[F("deviceType")];

  const char *data_command = doc[F("data")][F("command")];

  return data_command;
}