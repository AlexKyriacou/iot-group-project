#include "MotionDetector.h"

// Pin number for the PIR sensor
#define PIR_PIN 7

// Interval in milliseconds for printing the motion status
#define PRINT_INTERVAL 1000 // 1 second

MotionDetector motionDetector(PIR_PIN);

/**
 * @brief Initializes the motion detector and serial communication.
 */
void setup()
{
    motionDetector.setup();
    Serial.begin(9600);
}

/**
 * @brief The main loop that checks for motion detection and prints the motion status every PRINT_INTERVAL milliseconds.
 */
void loop()
{
    static unsigned long lastPrintTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - lastPrintTime >= PRINT_INTERVAL)
    {
        JsonDocument motionData = motionDetector.getJsonData();
        serializeJson(motionData, Serial);
        Serial.println();
        lastPrintTime = currentTime;
    }
}