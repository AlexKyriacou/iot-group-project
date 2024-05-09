# IoT Motion Detector Alarm System

This project is an IoT-based motion detector alarm system with the ability to expand into a gas sensor/water sprinkler system in the future. The system consists of an Arduino Uno with a PIR sensor, a Raspberry Pi that reads data from the Arduino and publishes it to an MQTT broker, and a Flask web application that subscribes to the MQTT broker and displays the motion data.

## Prerequisites

- Arduino Uno board
- PIR (Passive Infrared) sensor
- Raspberry Pi (with Python 3.x installed)
- Docker Desktop installed on a machine for running the MQTT broker and Flask application

## Getting Started

Follow these steps to set up and run the project:

### 1. Arduino Setup

1. Connect the PIR sensor to the Arduino Uno board.
2. Upload the `main.ino` and the `MotionDetector` files to the Arduino board.

### 2. Raspberry Pi Setup

1. Create a `.env` file in the `raspberry-pi` directory based on the `.env.example` and configure the necessary environment variables.
2. If not installed, download and install [Python](https://www.python.org/downloads/)
3. Install the required Python packages by running `py -m pip install -r requirements.txt` in the 'raspberry-pi' directory.
4. Run the `main.py` script using `py main.py`. This script can be run on your local machine, and it will read the motion data from the Arduino (assuming it's connected to your local machine) and publish it to the MQTT broker.

### 3. MQTT Broker (Mosquitto) Setup

1. Navigate to the root directory of the project (`cd ..` if you're in a child directory).
2. Run `docker-compose up -d` to start the Mosquitto MQTT broker container.

> [!NOTE] 
> The password setup within the Mosquitto server only needs to happen once for authenticating the clients (Raspberry Pi and Flask application). After setting up the passwords, the `docker-compose.yml` file in the root directory can be used to start both the Flask and Mosquitto server containers.

3. Create a new file named `pwfile` that will hold the hashed passwords in `mosquitto/config`
4. Create a user and password for the MQTT broker by running the following commands (only required if you haven't set up the passwords before) [reference](https://github.com/sukesh-ak/setup-mosquitto-with-docker):

Open Docker Desktop and open the `mqtt5` container, then click on the Exec tab and run the following commands
```bash
# Create a new password file and add a user (it will prompt for a password)
mosquitto_passwd -c /mosquitto/config/pwfile raspberry_pi_client

# Add additional users (remove the -c option and it will prompt for a password)
mosquitto_passwd /mosquitto/config/pwfile flask-application
```

5. Restart the Mosquitto container after creating the user(s)

6. Update the `MQTT_USERNAME` and `MQTT_PASSWORD` environment variables in the `.env` files of the `application` and `raspberry-pi` directories with the created user credentials.

### 4. Flask Application Setup

1. Navigate to the `application` directory.
2. Create a `.env` file based on the `.env.example` and configure the necessary environment variables, including the MQTT broker credentials.
3. Build the Docker image for the Flask application by running `docker build -t flask-app .`.
4. Run the Flask application container using `docker run -p 5000:5000 flask-app`.
5. Access the web application by opening `http://localhost:5000` in a web browser.

## Running the System

Once everything is set up, you can run the system as follows:

> [!NOTE] 
> If any docker containers are running, the following steps might fail, run `docker-compose down` in all directories (root, .\mosquitto\ and .\application\) before you go through the following steps

1. In one terminal, start the Mosquitto MQTT broker and Flask application by running `docker-compose up` in the project's root directory.
2. In another terminal, navigate to the `raspberry-pi` directory and run the `main.py` script using `py main.py`. This script will read the motion data from the Arduino (if connected to your local machine) and publish it to the MQTT broker.

The Flask application should now display the motion detection status received from the Arduino via the MQTT broker.

## MQTT and JSON Schema

This project follows a specific schema for MQTT topics and JSON messages to ensure modularity, configurability, and reusability.

### MQTT Topics

The MQTT topics are structured in a hierarchical manner, following the pattern:

```
{deviceType}/{deviceId}/{action}
```

- `{deviceType}`: The type of device, such as `motionDetector`, `gasSensor`, or `sprinkler`.
- `{deviceId}`: A unique identifier for the specific device instance.
- `{action}`: The action or event being published or subscribed to, such as `status`, or `configuration`.

For example:

- `motionDetector/device001/status`: Publish motion detector status
- `gasSensor/device002/status`: Publish gas sensor readings
- `motionDetector/device001/configuration`: Subscribe to configuration updates for the motion detector
- `motionDetector/+/status`: Subscribe to all motionDetector status updates

For commands that affect the entire system i.e. arming the alarm on all motion sensors we simply remove the `{deviceId}` param

i.e.
- `alarmSystem/command`: Pub/Sub to all commands that have been given to the alarm system as a whole

### JSON Message Schema

The JSON messages have a consistent structure to ensure interoperability and ease of processing:

```json
{
  "deviceType": "string",
  "deviceId": "string",
  "timestamp": "integer unix time stamp",
  "data": {
    "placeholder": "Sensor-specific data structure"
  }
}
```

- `deviceType`: The type of device, matching the `{deviceType}` in the MQTT topic structure.
- `deviceId`: The unique identifier of the device instance, matching the `{deviceId}` in the MQTT topic structure.
- `timestamp`: The time when the message was generated, represented in unix time stamp format.
- `data`: An object containing the sensor-specific data structure.

For example, a motion detector status message might look like:

```json
{
  "deviceType": "motionDetector",
  "deviceId": "device001",
  "timestamp": 1715069574,
  "data": {
    "motion": true
  }
}
```
> [!NOTE] 
> Note that the time stamps and device ID's are added to the messages within the rasberry pi
>
> Messages will be transmitted in the following schema from the Ardunio before having the ID and timestamp added:
```json
{
    "deviceType": "motionDetector",
    "data": {
      "motion": true
    }
}
```


A command from the web app to the arduino will use a slighly different structure since it isnt really necessary to define the deviceID or the timestamp

E.G. to arm or disarm the alarm system could be:
```json
{
  "deviceType": "alarmSystem",
  "data": {
    "command": "arm"
  }
}
```



## Future Enhancements

This project is designed to be modular and extensible. Future enhancements may include:

- Adding additional sensors, such as gas sensors or water sprinklers, and integrating their functionality with the existing system.
- Implementing alert mechanisms (e.g., email, SMS, push notifications) when motion is detected.
- Enhancing the web application with additional features and visualizations.
