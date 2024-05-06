# Raspberry Pi MQTT Client

This Python script runs on a Raspberry Pi and is responsible for reading motion data from an Arduino over a serial connection and publishing it to a cloud application using the MQTT protocol.

## Prerequisites

- Python 3.x installed on the Raspberry Pi
- `paho-mqtt` library installed (`pip install paho-mqtt`)

## Configuration

The script is designed to be highly configurable using environment variables. The following variables can be set:

- `MQTT_BROKER`: The hostname or IP address of the MQTT broker (default: `mqtt.example.com`).
- `MQTT_PORT`: The port number of the MQTT broker (default: `1883`).
- `MQTT_TOPIC`: The MQTT topic to publish the motion data (default: `iot/device/data`).
- `MQTT_CLIENT_ID`: The client ID for the MQTT client (default: `raspberry_pi_client`).
- `MQTT_USERNAME`: The username for MQTT broker authentication (optional).
- `MQTT_PASSWORD`: The password for MQTT broker authentication (optional).
- `SERIAL_PORT`: The serial port where the Arduino is connected (default: `/dev/ttyACM0`).
- `SERIAL_BAUD_RATE`: The baud rate for serial communication (default: `9600`).
- `PUBLISH_INTERVAL`: The interval (in seconds) at which the script checks for new sensor data (default: `10`).


## Usage

1. Connect the Arduino to the Raspberry Pi via the serial port.
2. Ensure that the Arduino is running the motion detector code and sending data in the expected JSON format.
3. Run the Python script: `python mqtt_client.py`

The script will connect to the MQTT broker, read motion data from the serial port, and publish it to the configured MQTT topic. You can monitor the published data using an MQTT client or by subscribing to the topic in your cloud application.

## How it Works

1. The script loads the configuration from environment variables or the `.env` file.
2. It creates an MQTT client instance and sets the appropriate credentials (if provided).
3. The script defines callback functions for successful connection and disconnection from the MQTT broker.
4. It connects to the MQTT broker and starts the client loop.
5. In the main loop, the script reads sensor data from the serial port and publishes it to the MQTT topic.
6. The loop runs indefinitely until a signal (e.g., Ctrl+C or a termination signal) is received.
7. When a signal is received, the script gracefully stops the MQTT client loop and disconnects from the broker.