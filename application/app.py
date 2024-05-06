# app.py
from flask import Flask, render_template
from mqtt.client import MQTTClient
import os
from dotenv import load_dotenv

load_dotenv()

app = Flask(__name__)

# print env vars
print(os.getenv("MQTT_BROKER"))
print(os.getenv("MQTT_PORT"))
print(os.getenv("MQTT_TOPIC"))
print(os.getenv("MQTT_CLIENT_ID"))
print(os.getenv("MQTT_USERNAME"))
print(os.getenv("MQTT_PASSWORD"))

# Create an instance of the MQTT client
mqtt_client = MQTTClient(
    broker=os.getenv("MQTT_BROKER"),
    port=os.getenv("MQTT_PORT"),
    topic=os.getenv("MQTT_TOPIC"),
    client_id=os.getenv("MQTT_CLIENT_ID"),
    username=os.getenv("MQTT_USERNAME"),
    password=os.getenv("MQTT_PASSWORD")
)

# Start the MQTT client
mqtt_client.start()

data = []

@app.route('/')
def index():
    """
    Render the homepage with the latest data from the MQTT broker.

    Returns:
        str: Rendered HTML template with the data.
    """
    data.append(mqtt_client.data)
    return render_template('index.html', data=data)


if __name__ == '__main__':
    app.run(debug=True)
