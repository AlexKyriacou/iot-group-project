from flask import Flask, render_template
from flask_socketio import SocketIO
from mqtt.client import MQTTClient
from datetime import datetime
import json

from config import Config

app = Flask(__name__)
# TODO: Replace with a secure secret key
app.config["SECRET_KEY"] = "your_secret_key"
socketio = SocketIO(app)


@app.route("/")
def index():
    """
    Render the homepage with the latest data from the MQTT broker.

    Returns:
        str: Rendered HTML template.
    """
    return render_template("index.html")


@socketio.on("connect")
def handle_connect():
    """
    Handle a new WebSocket connection.
    """
    print("Client connected")


@socketio.on("disconnect")
def handle_disconnect():
    """
    Handle a WebSocket disconnection.
    """
    print("Client disconnected")


@socketio.on("command_alarm")
def handle_command_alarm(data):
    """
    Handle a command to enable or disable the alarm.

    Args:
        data (dict): The command data.
    """
    alarmObject = build_alarm_object(data)
    serializedAlarmObject = json.dumps(alarmObject)
    mqtt_client.publish("alarmSystem/command", serializedAlarmObject)


def build_alarm_object(requestData):
    alarmObject = {}
    if "command" not in requestData:
        return None

    alarmObject["deviceType"] = "alarmSystem"
    alarmObject["data"] = {}
    alarmObject["data"]["command"] = requestData["command"]
    return alarmObject


def emit_data(data):
    """
    Emit data to the WebSocket clients.

    Args:
        data (dict): The data to be emitted.
    """
    socketio.emit("mqtt_data", data)


# Set up a background task to emit data from the MQTT client
def background_task():
    """
    Background task to emit data from the MQTT client to the WebSocket clients.
    """
    while True:
        data = mqtt_client.data
        if data:
            emit_data(data)
            mqtt_client.data = None
        socketio.sleep(0.1)  # Small delay to avoid overwhelming the WebSocket


if __name__ == "__main__":
    config = Config()
    mqtt_client = MQTTClient(
        broker=config.broker,
        port=config.port,
        topics=["motionDetector/+/status", "ultraSonicSensor/+/status", "gasSensor/+/status", "flameSensor/+/status"],
        client_id=config.client_id,
        username=config.username,
        password=config.password,
    )
    mqtt_client.start()
    socketio.start_background_task(background_task)
    socketio.run(
        app, allow_unsafe_werkzeug=True, debug=True, host="0.0.0.0", use_reloader=False
    )
