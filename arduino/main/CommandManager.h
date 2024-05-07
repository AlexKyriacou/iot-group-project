#include <ArduinoJson.h>

class CommandManager {
public:
  static String deserializeCommand(const String &message);

private:
  JsonManager() {}  // Private constructor to prevent instantiation
};