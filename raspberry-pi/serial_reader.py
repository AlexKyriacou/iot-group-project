import json
import serial


class SerialReader:
    def __init__(self, config):
        self.config = config

    def read_sensor_data(self):
        try:
            with serial.Serial(
                self.config.serial_port, self.config.serial_baud_rate
            ) as ser:
                data = ser.readline().decode().strip()
                if data:
                    print(f"Read sensor data: {data}")
                    return json.loads(data)
        except (serial.SerialException, ValueError) as e:
            print(f"Error reading sensor data: {e}")
        return {}
