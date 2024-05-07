import os
from dotenv import load_dotenv

load_dotenv()


class Config:
    def __init__(self):
        self.mqtt_broker = os.getenv("MQTT_BROKER", "mqtt.eclipse.org")
        self.mqtt_port = int(os.getenv("MQTT_PORT", 1883))
        self.mqtt_client_id = os.getenv("MQTT_CLIENT_ID", "raspberry_pi")
        self.mqtt_username = os.getenv("MQTT_USERNAME", None)
        self.mqtt_password = os.getenv("MQTT_PASSWORD", None)

        self.serial_port = os.getenv("SERIAL_PORT", "/dev/ttyACM0")
        self.serial_baud_rate = int(os.getenv("SERIAL_BAUD_RATE", 9600))
        self.publish_interval = int(os.getenv("PUBLISH_INTERVAL", 10))

        self.device_id = os.getenv("DEVICE_ID", "raspberry-pi")

        # print config
        print(f"MQTT Broker: {self.mqtt_broker}")
        print(f"MQTT Port: {self.mqtt_port}")
        print(f"MQTT Client ID: {self.mqtt_client_id}")
        print(f"MQTT Username: {self.mqtt_username}")
        print(f"MQTT Password: {self.mqtt_password}")

        print(f"Serial Port: {self.serial_port}")
        print(f"Serial Baud Rate: {self.serial_baud_rate}")
        print(f"Publish Interval: {self.publish_interval}")

        print(f"Device ID: {self.device_id}")
