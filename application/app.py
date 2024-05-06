from flask import Flask, render_template
from flask_socketio import SocketIO
from mqtt.client import MQTTClient
import os
from dotenv import load_dotenv

load_dotenv()

app = Flask(__name__)
# TODO: Replace with a secure secret key
app.config['SECRET_KEY'] = 'your_secret_key'
socketio = SocketIO(app)

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


@app.route('/')
def index():
    """
    Render the homepage with the latest data from the MQTT broker.

    Returns:
        str: Rendered HTML template.
    """
    return render_template('index.html')


@socketio.on('connect')
def handle_connect():
    """
    Handle a new WebSocket connection.
    """
    print('Client connected')


@socketio.on('disconnect')
def handle_disconnect():
    """
    Handle a WebSocket disconnection.
    """
    print('Client disconnected')


def emit_data(data):
    """
    Emit data to the WebSocket clients.

    Args:
        data (dict): The data to be emitted.
    """
    socketio.emit('mqtt_data', data)


# Set up a background task to emit data from the MQTT client
def background_task():
    """
    Background task to emit data from the MQTT client to the WebSocket clients.
    """
    while True:
        data = mqtt_client.data
        if data:
            emit_data(data)
        socketio.sleep(0.1)  # Small delay to avoid overwhelming the WebSocket


if __name__ == '__main__':
    socketio.start_background_task(background_task)
    socketio.run(app, allow_unsafe_werkzeug=True, debug=True, host='0.0.0.0')
