import paho.mqtt.client as mqtt
import json


class MQTTClient:
    def __init__(self, broker, port, topic, username=None, password=None):
        """
        Initialize the MQTT client.

        Args:
            broker (str): The hostname or IP address of the MQTT broker.
            port (int): The port number of the MQTT broker.
            topic (str): The MQTT topic to subscribe to.
            client_id (str): The client ID for the MQTT client.
            username (str, optional): The username for MQTT broker authentication.
            password (str, optional): The password for MQTT broker authentication.
        """
        self.broker = broker
        self.port = int(port)
        self.topic = topic
        self.username = username
        self.password = password
        self.client = mqtt.Client(
            mqtt.CallbackAPIVersion.VERSION1, client_id="flask-client")
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        self.data = None

    def on_connect(self, client, userdata, flags, rc):
        """
        Callback function for successful connection to the MQTT broker.

        Args:
            client (mqtt.Client): The MQTT client instance.
            userdata (Any): User-defined data passed to the callback function.
            flags (dict): Flags related to the connection.
            rc (int): The result code of the connection attempt.
        """
        print(f"Connected to MQTT broker with result code {str(rc)}")
        client.subscribe(self.topic)

    def on_message(self, client, userdata, msg):
        """
        Callback function for receiving messages from the MQTT broker.

        Args:
            client (mqtt.Client): The MQTT client instance.
            userdata (Any): User-defined data passed to the callback function.
            msg (MQTTMessage): The received MQTT message.
        """
        self.data = json.loads(msg.payload.decode())
        print(f"Received data: {self.data}")

    def start(self):
        """
        Start the MQTT client and connect to the broker.
        """
        if self.username and self.password:
            self.client.username_pw_set(self.username, self.password)
        self.client.connect(self.broker, self.port)
        self.client.loop_start()

    def stop(self):
        """
        Stop the MQTT client and disconnect from the broker.
        """
        self.client.loop_stop()
        self.client.disconnect()
