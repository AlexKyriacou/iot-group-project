
# IoT Motion Detector Alarm System

This project is an IoT-based motion detector alarm system with the ability to expand into a gas sensor/water sprinkler system in the future. The system consists of an Arduino Uno with a PIR sensor, a Raspberry Pi that reads data from the Arduino and publishes it to an MQTT broker, and a Flask web application that subscribes to the MQTT broker and displays the motion data.

## Prerequisites

- Arduino Uno board
- PIR (Passive Infrared) sensor
- Raspberry Pi (with Python 3.x installed)
- Docker and Docker Compose installed on a machine for running the MQTT broker and Flask application

## Getting Started

Follow these steps to set up and run the project:

### 1. Arduino Setup

1. Connect the PIR sensor to the Arduino Uno board.
2. Upload the `main.ino` and the `MotionDetector` files to the Arduino board.

Sure, I've updated the relevant sections as per your requirements:

### 2. Raspberry Pi Setup

1. Create a `.env` file in the `raspberry-pi` directory based on the `.env.example` and configure the necessary environment variables.
2. Install the required Python packages by running `pip install -r requirements.txt`.
3. Run the `iot-mqtt-client.py` script using `python iot-mqtt-client.py`. This script can be run on your local machine, and it will read the motion data from the Arduino (assuming it's connected to your local machine) and publish it to the MQTT broker.

### 3. MQTT Broker (Mosquitto) Setup

1. Navigate to the root directory of the project.
2. Run `docker-compose up -d` to start the Mosquitto MQTT broker container.

Note: The password setup within the Mosquitto server only needs to happen once for authenticating the clients (Raspberry Pi and Flask application). After setting up the passwords, the `docker-compose.yml` file in the root directory can be used to start both the Flask and Mosquitto server containers.

3. Create a user and password for the MQTT broker by running the following commands (only required if you haven't set up the passwords before) [reference](https://github.com/sukesh-ak/setup-mosquitto-with-docker):

```bash
# Log into the Mosquitto container
sudo docker exec -it <container-id> sh

# Create a new password file and add a user (it will prompt for a password)
mosquitto_passwd -c /mosquitto/config/pwfile raspberry_pi_client

# Add additional users (remove the -c option and it will prompt for a password)
mosquitto_passwd /mosquitto/config/pwfile flask-application

# Exit the container
exit
```

4. Restart the Mosquitto container after creating the user(s):

```bash
sudo docker restart <container-id>
```

5. Update the `MQTT_USERNAME` and `MQTT_PASSWORD` environment variables in the `.env` files of the `application` and `raspberry-pi` directories with the created user credentials.

### 4. Flask Application Setup

1. Navigate to the `application` directory.
2. Create a `.env` file based on the `.env.example` and configure the necessary environment variables, including the MQTT broker credentials.
3. Build the Docker image for the Flask application by running `docker build -t flask-app .`.
4. Run the Flask application container using `docker run -p 5000:5000 flask-app`.
5. Access the web application by opening `http://localhost:5000` in a web browser.

## Running the System

Once everything is set up, you can run the system as follows:

1. In one terminal, start the Mosquitto MQTT broker and Flask application by running `docker-compose up` in the project's root directory.
2. In another terminal, run the `iot-mqtt-client.py` script using `python iot-mqtt-client.py`. This script will read the motion data from the Arduino (if connected to your local machine) and publish it to the MQTT broker.

The Flask application should now display the motion detection status received from the Arduino via the MQTT broker.

## Future Enhancements

This project is designed to be modular and extensible. Future enhancements may include:

- Adding additional sensors, such as gas sensors or water sprinklers, and integrating their functionality with the existing system.
- Implementing alert mechanisms (e.g., email, SMS, push notifications) when motion is detected.
- Enhancing the web application with additional features and visualizations.