# Motion Detector System

This project is an IoT-based motion detector system developed using an Arduino Uno and a PIR (Passive Infrared) sensor. The system detects motion and reports its status in a JSON format over the serial communication.

### How it Works
The system consists of the following components:

- **Arduino Uno:** The microcontroller board that runs the code and controls the PIR sensor.
- **PIR Sensor:** A motion detector sensor that detects infrared radiation emitted by human bodies or other objects in motion.

The `MotionDetector` class encapsulates the functionality of the PIR sensor. It provides methods to initialize the sensor, check for motion detection, and retrieve the motion status in a JSON format.

The `main.ino` file sets up the motion detector, initializes serial communication, and periodically prints the motion status to the serial monitor.

## Message Format
The motion detector status is reported in a JSON format over the serial communication. The JSON object has the following structure:

```json
{
  "name": "motion_detector",
  "message": {
    "value": true/false
  }
}
```

- `name`: Identifies the type of sensor or device, which is `"motion_detector"` in this case.
- `message.value`: A boolean value indicating whether motion is detected (`true`) or not (`false`).

## Future Enhancements
This project is designed to be modular and extensible. Future enhancements may include:
- Adding additional sensors, such as gas sensors or water sprinklers, and integrating their functionality with the existing system.