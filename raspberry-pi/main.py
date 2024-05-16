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
    thingsboard_client.loop_stop()
    thingsboard_client.disconnect()
    mosquitto_client.loop_stop()
    mosquitto_client.disconnect()
    exit(0)
    
def handle_mqtt_data():
    if thingsboard_client.data:
        if "deviceType" not in thingsboard_client.data:
            print(f"Received invalid data: {thingsboard_client.data}")
            thingsboard_client.data = None
            return
        
        device_type = thingsboard_client.data["deviceType"]
        if device_type == "alarmSystem":
            print(f"Received command data: {thingsboard_client.data}")
            serial_reader.send_data(thingsboard_client.data)
        else:
            print(f"Received unknown data: {thingsboard_client.data}")
        thingsboard_client.data = None
    if mosquitto_client.data:
        if "deviceType" not in mosquitto_client.data:
            print(f"Received invalid data: {mosquitto_client.data}")
            mosquitto_client.data = None
            return
        
        device_type = mosquitto_client.data["deviceType"]
        if device_type == "alarmSystem":
            print(f"Received command data: {mosquitto_client.data}")
            serial_reader.send_data(mosquitto_client.data)
        else:
            print(f"Received unknown data: {mosquitto_client.data}")
        mosquitto_client.data = None

def read_and_publish_sensor_data():
    sensor_data = serial_reader.read_sensor_data()
    sensor_data = serial_reader.update_data_with_device_id_and_timestamp(sensor_data)
    serialized_data = json.dumps(sensor_data)
    print(f"Publishing sensor data: {sensor_data}")
    thingsboard_client.publish(f"v1/devices/me/telemetry", serialized_data)
    mosquitto_client.publish(f"v1/devices/me/telemetry", serialized_data)

def main():
    thingsboard_client.connect()
    mosquitto_client.connect()

    while True:
        read_and_publish_sensor_data()
        handle_mqtt_data()
        time.sleep(config.publish_interval)


# Set up signal handlers for graceful exit
signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGTERM, signal_handler)

if __name__ == "__main__":
    config = Config()
    thingsboard_client = MQTTClient(
        broker=config.mqtt_broker,
        port=config.mqtt_port,
        topics=["alarmSystem/command"],
        client_id=config.mqtt_client_id,
        username=config.mqtt_username,
        password=config.mqtt_password,
    )
    mosquitto_client = MQTTClient(
        broker="20.70.77.206",
        port=config.mqtt_port,
        topics=["alarmSystem/command"],
        client_id=config.mqtt_client_id,
    )
    serial_reader = SerialReader(config)
    main()
