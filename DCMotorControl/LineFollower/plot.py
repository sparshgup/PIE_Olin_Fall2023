import serial
import matplotlib.pyplot as plt

arduinoComPort = "/dev/cu.usbmodem12101"
baudRate = 9600

serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

# Initialize data lists
motor1_speeds = []
motor2_speeds = []
sensor0_readings = []
sensor1_readings = []
sensor2_readings = []
sensor3_readings = []

# Set the maximum number of readings
max_readings = 100
reading_count = 0

# Main loop to read data from the Arduino, then display it
while reading_count < max_readings:
    lineOfData = serialPort.readline().decode()

    if "end\r\n" in lineOfData:
        break

    elif len(lineOfData) > 0:
        data = list(map(float, lineOfData.split(',')))

        # Assuming the data list contains the following:
        # Motor 1 speed at index 0, Motor 2 speed at index 1
        # IR Sensor 2 reading at index 2, IR Sensor 3 reading at index 3
        # IR Sensor 4 reading at index 4, IR Sensor 5 reading at index 5
        sensor0_readings.append(data[0])
        sensor1_readings.append(data[1])
        sensor2_readings.append(data[2])
        sensor3_readings.append(data[3])
        motor1_speeds.append(data[4])
        motor2_speeds.append(data[5])

        reading_count += 1

# Create subplots for motor speeds and sensor readings
plt.figure(figsize=(12, 8))

# Motor Speeds
plt.subplot(2, 1, 1)
plt.plot(motor1_speeds, label='Motor 1 Speed')
plt.plot(motor2_speeds, label='Motor 2 Speed')
plt.xlabel('Time (samples)')
plt.ylabel('Speed')
plt.legend()
plt.title('Motor Speeds Over Time')
plt.grid(True)

# Sensor Readings
plt.subplot(2, 1, 2)
plt.plot(sensor0_readings, label='IR Sensor 2')
plt.plot(sensor1_readings, label='IR Sensor 3')
plt.plot(sensor2_readings, label='IR Sensor 4')
plt.plot(sensor3_readings, label='IR Sensor 5')
plt.xlabel('Time (samples)')
plt.ylabel('Reading')
plt.legend()
plt.title('IR Sensor Readings Over Time')
plt.grid(True)

plt.tight_layout()
plt.show()
