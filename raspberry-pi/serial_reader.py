import json
import serial
from datetime import datetime


class SerialReader:
    def __init__(self, config):
        self.config = config
        self.serial = serial.Serial(
            self.config.serial_port, self.config.serial_baud_rate
        )

    def read_sensor_data(self):
        try:
            data = self.serial.readline().decode('utf-8').strip()
            if data:
                print(f"Read sensor data: {data}")
                return json.loads(data)
        except (serial.SerialException, ValueError) as e:
            print(f"Error reading sensor data: {e}")
        return {}

    def update_data_with_device_id_and_timestamp(self, data: dict[str, any]):
        data["deviceId"] = self.config.device_id
        data["timestamp"] = int(datetime.now().timestamp())
        return data
    
    def send_data(self, data: dict[str, any]):
        serialized_data = json.dumps(data)
        self.serial.write(serialized_data.encode())
        print(f"Sent data: {serialized_data}")
