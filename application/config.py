import os
from dotenv import load_dotenv

load_dotenv()


class Config:
    def __init__(self):
        self.broker = os.getenv("MQTT_BROKER")
        self.port = os.getenv("MQTT_PORT")
        self.username = os.getenv("MQTT_USERNAME")
        self.password = os.getenv("MQTT_PASSWORD")
        self.client_id = os.getenv("MQTT_CLIENT_ID")

        # print config
        print(self.broker)
        print(self.port)
        print(self.username)
        print(self.password)
        print(self.client_id)
