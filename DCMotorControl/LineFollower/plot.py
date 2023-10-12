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

        sensor0_readings.append(data[0])
        sensor1_readings.append(data[1])
        sensor2_readings.append(data[2])
        sensor3_readings.append(data[3])
        motor1_speeds.append(data[4])
        motor2_speeds.append(data[5])

        reading_count += 1

# Create subplots for Motor 1 speed vs all IR sensors and Motor 2 speed vs all IR sensors
plt.figure(figsize=(16, 6))

# Motor 1 Speed vs IR Sensor Data
plt.subplot(1, 2, 1)
plt.plot(sensor0_readings, motor1_speeds, 'o', label='Motor 1 Speed vs IR Sensor 0')
plt.plot(sensor1_readings, motor1_speeds, 'o', label='Motor 1 Speed vs IR Sensor 1')
plt.plot(sensor2_readings, motor1_speeds, 'o', label='Motor 1 Speed vs IR Sensor 2')
plt.plot(sensor3_readings, motor1_speeds, 'o', label='Motor 1 Speed vs IR Sensor 3')
plt.xlabel('IR Sensor Readings')
plt.ylabel('Motor 1 Speed')
plt.legend()
plt.title('Motor 1 Speed vs IR Sensors')
plt.grid(True)

# Motor 2 Speed vs IR Sensor Data
plt.subplot(1, 2, 2)
plt.plot(sensor0_readings, motor2_speeds, 'o', label='Motor 2 Speed vs IR Sensor 0')
plt.plot(sensor1_readings, motor2_speeds, 'o', label='Motor 2 Speed vs IR Sensor 1')
plt.plot(sensor2_readings, motor2_speeds, 'o', label='Motor 2 Speed vs IR Sensor 2')
plt.plot(sensor3_readings, motor2_speeds, 'o', label='Motor 2 Speed vs IR Sensor 3')
plt.xlabel('IR Sensor Readings')
plt.ylabel('Motor 2 Speed')
plt.legend()
plt.title('Motor 2 Speed vs IR Sensors')
plt.grid(True)

plt.tight_layout()
plt.show()
