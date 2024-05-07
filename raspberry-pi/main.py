import signal
import time
import json

from config import Config
from mqtt_client import MQTTClient
from serial_reader import SerialReader


def signal_handler(signal, frame):
    """
    Handle signals to gracefully exit the program.
    """
    print("Exiting program...")
    mqtt_client.loop_stop()
    mqtt_client.disconnect()
    exit(0)


def main():
    mqtt_client.connect()

    while True:
        sensor_data = serial_reader.read_sensor_data()
        serialized_data = json.dumps(sensor_data)
        print(f"Publishing sensor data: {sensor_data}")
        mqtt_client.publish(config.mqtt_topic, serialized_data)
        time.sleep(config.publish_interval)


# Set up signal handlers for graceful exit
signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGTERM, signal_handler)

if __name__ == "__main__":
    config = Config()
    mqtt_client = MQTTClient(
        broker=config.mqtt_broker,
        port=config.mqtt_port,
        topics=["motionDetector/+/command"],
        client_id=config.mqtt_client_id,
        username=config.mqtt_username,
        password=config.mqtt_password,
    )
    serial_reader = SerialReader(config)
    main()
