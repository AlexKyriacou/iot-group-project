# Motion Detector Alarm System

This project is an IoT-based motion detector alarm system developed using an Arduino Uno and a PIR (Passive Infrared) sensor. The system detects motion and reports its status in a JSON format over the serial communication. Additionally, it provides an interface to arm or disarm the alarm system and control an LED based on the detection status. To change which sensors you are using within your system simply add/remove the object instances within main.ino

## Features

- Motion detection using a PIR sensor
- Arm/disarm the alarm system
- Control an LED based on motion detection and alarm status
- Report sensor data in JSON format over serial communication
- Modular design with sensor abstraction for easy integration of new sensor types

## Components

- **Arduino Uno:** The microcontroller board that runs the code and controls the PIR sensor and LED.
- **PIR Sensor:** A motion detector sensor that detects infrared radiation emitted by human bodies or other objects in motion.
- **LED:** An LED that indicates motion detection when the alarm is armed.

## Implementation

The project follows an object-oriented design with the following classes:

- `Sensor`: An abstract base class that defines the interface for different sensor types.
- `MotionDetector`: A concrete implementation of the `Sensor` class for the PIR motion sensor.
- `Led`: A class that encapsulates the functionality of an LED.
- `AlarmSystem`: The main class that manages the alarm system, handles user commands, and coordinates the sensors and LED.
- `CommandManager`: A utility class for deserializing commands received over the serial communication.

The `main.ino` file sets up the alarm system, adds the desired sensors, and handles the main loop.

## Message Format

The sensor data is reported in a JSON format over the serial communication. The JSON object has the following structure:

```json
{
  "deviceType": "motionDetector",
  "data": {
    "placeholder": "Sensor-specific data structure"
  }
}
```

## Command Format

The alarm system accepts commands to arm or disarm the system. These commands are sent over the serial communication in a specific JSON format:

```json
{
  "deviceType": "alarmSystem",
  "data": {
    "command": "arm/disarm"
  }
}
```