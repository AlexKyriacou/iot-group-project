import paho.mqtt.client as mqtt
import json


class MQTTClient(mqtt.Client):
    def __init__(self, broker, port, topics, client_id, username=None, password=None):
        super().__init__(mqtt.CallbackAPIVersion.VERSION1, client_id=client_id)
        self.broker = broker
        self.port = int(port)
        self.topics = topics
        self.username = username
        self.password = password
        self.data = None

    def on_connect(self, client, userdata, flags, rc):
        print(f"Connected to MQTT broker with result code {str(rc)}")
        for topic in self.topics:
            client.subscribe(topic)

    def on_message(self, client, userdata, msg):
        self.data = json.loads(msg.payload.decode())
        print(f"Received data: {self.data}")

    def start(self):
        if self.username and self.password:
            self.username_pw_set(self.username, self.password)
        self.connect()
        self.loop_start()

    def connect(self):
        if self.username and self.password:
            self.username_pw_set(self.username, self.password)
        super().connect(self.broker, self.port)
        self.loop_start()

    def stop(self):
        self.loop_stop()
        self.disconnect()
