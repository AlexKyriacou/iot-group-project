import paho.mqtt.client as mqtt
import json
import time
import os
import serial
import signal

# Load configuration from environment variables
MQTT_BROKER = os.environ.get('MQTT_BROKER', 'mqtt.example.com')
MQTT_PORT = int(os.environ.get('MQTT_PORT', 1883))
MQTT_TOPIC = os.environ.get('MQTT_TOPIC', 'iot/device/data')
MQTT_CLIENT_ID = os.environ.get('MQTT_CLIENT_ID', 'raspberry_pi_client')
MQTT_USERNAME = os.environ.get('MQTT_USERNAME', None)
MQTT_PASSWORD = os.environ.get('MQTT_PASSWORD', None)

# Set the appropriate serial port
SERIAL_PORT = os.environ.get('SERIAL_PORT', '/dev/ttyACM0')
SERIAL_BAUD_RATE = int(os.environ.get('SERIAL_BAUD_RATE', 9600))
PUBLISH_INTERVAL = int(os.environ.get('PUBLISH_INTERVAL', 10))  # in seconds

# Create an MQTT client instance
client = mqtt.Client(client_id=MQTT_CLIENT_ID)


def on_connect(client, userdata, flags, rc):
    """
    Callback function for successful connection to the MQTT broker.

    Args:
        client (mqtt.Client): The MQTT client instance.
        userdata (Any): User-defined data passed to the callback function.
        flags (dict): Flags related to the connection.
        rc (int): The result code of the connection attempt.
    """
    print(f"Connected to MQTT broker with result code {str(rc)}")


def on_disconnect(client, userdata, rc):
    """
    Callback function for disconnection from the MQTT broker.

    Args:
        client (mqtt.Client): The MQTT client instance.
        userdata (Any): User-defined data passed to the callback function.
        rc (int): The result code of the disconnection.
    """
    print(f"Disconnected from MQTT broker with result code {str(rc)}")


def read_sensor_data():
    """
    Read sensor data from the serial port.

    Returns:
        dict: The sensor data as a dictionary,
        or an empty dictionary if an error occurs.
    """
    try:
        with serial.Serial(SERIAL_PORT, SERIAL_BAUD_RATE) as ser:
            data = ser.readline().decode().strip()
            if data:
                return json.loads(data)
    except (serial.SerialException, ValueError) as e:
        print(f"Error reading sensor data: {e}")
    return {}


def publish_sensor_data(data):
    """
    Publish sensor data to the MQTT broker.

    Args:
        data (dict): The sensor data to be published.
    """
    payload = json.dumps(data)
    client.publish(MQTT_TOPIC, payload)
    print(f"Published data to MQTT topic '{MQTT_TOPIC}': {payload}")


# Set a flag to control the main loop
running = True


def signal_handler(signal, frame):
    """
    Handle signals to gracefully exit the program.

    Args:
        signal (int): The signal number.
        frame (frame): The current stack frame.
    """
    global running
    running = False
    print("Exiting program...")


# Set MQTT credentials if provided
if MQTT_USERNAME and MQTT_PASSWORD:
    client.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)

# Set the callback functions for the client
client.on_connect = on_connect
client.on_disconnect = on_disconnect

# Connect to the MQTT broker
client.connect(MQTT_BROKER, MQTT_PORT)

# Set up signal handlers for graceful exit
signal.signal(signal.SIGINT, signal_handler)  # Handle Ctrl+C
signal.signal(signal.SIGTERM, signal_handler)  # Handle termination signal

# Start the MQTT client loop
client.loop_start()

# Main loop
while running:
    sensor_data = read_sensor_data()
    publish_sensor_data(sensor_data)
    time.sleep(PUBLISH_INTERVAL)

print("Cleaning up...")
# Stop the MQTT client loop and disconnect
client.loop_stop()
client.disconnect()
