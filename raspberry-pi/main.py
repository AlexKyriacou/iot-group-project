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


def handle_mqtt_data():
    if mqtt_client.data:
        if "deviceType" not in mqtt_client.data:
            print(f"Received invalid data: {mqtt_client.data}")
            mqtt_client.data = None
            return

        device_type = mqtt_client.data["deviceType"]
        match device_type:
            case "alarmSystem":
                print(f"Received command data: {mqtt_client.data}")
                serial_reader.send_data(mqtt_client.data)
            case _:
                print(f"Received unknown data: {mqtt_client.data}")
        mqtt_client.data = None


def read_and_publish_sensor_data():
    sensor_data = serial_reader.read_sensor_data()
    sensor_data = serial_reader.update_data_with_device_id_and_timestamp(sensor_data)
    serialized_data = json.dumps(sensor_data)
    print(f"Publishing sensor data: {sensor_data}")
    # handle different device types
    if "deviceType" not in sensor_data:
        print(f"Invalid data: {sensor_data}")
        return
    device_type = sensor_data["deviceType"]
    mqtt_client.publish(f"{device_type}/{config.device_id}/status", serialized_data)


def main():
    mqtt_client.connect()

    while True:
        read_and_publish_sensor_data()
        handle_mqtt_data()
        time.sleep(config.publish_interval)


# Set up signal handlers for graceful exit
signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGTERM, signal_handler)

if __name__ == "__main__":
    config = Config()
    mqtt_client = MQTTClient(
        broker=config.mqtt_broker,
        port=config.mqtt_port,
        topics=["alarmSystem/command"],
        client_id=config.mqtt_client_id,
        username=config.mqtt_username,
        password=config.mqtt_password,
    )
    serial_reader = SerialReader(config)
    main()
