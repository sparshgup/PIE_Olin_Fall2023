import serial
import matplotlib.pyplot as plt
import math
import csv
from mpl_toolkits.mplot3d import Axes3D


arduinoComPort = "/dev/cu.usbmodem12101"

# Set the baud rate
baudRate = 115200

# open the serial port
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

# Initialize spherical data lists
pan_angles = []
tilt_angles = []
distances = []

# main loop to read data from the Arduino, then display it
while True:
    lineOfData = serialPort.readline().decode()

    if "end\r\n" in lineOfData:
        break

    elif len(lineOfData) > 0:
        pan_angle, tilt_angle, distance = map(float, lineOfData.split(','))

        print(f"Pan angle: {pan_angle}, "
              f"Tilt angle: {tilt_angle}, "
              f"Distance: {distance}")

        # Append data to lists
        pan_angles.append(pan_angle)
        tilt_angles.append(tilt_angle)
        distances.append(distance)

# Lists for plotting cartesian coordinates
x = []
y = []
z = []

for i in range(len(distances)):
    x.append(distances[i] * math.sin(tilt_angles[i] * math.pi / 180) *
             math.sin(pan_angles[i]) * math.pi / 180)
    y.append(distances[i] * math.sin(tilt_angles[i] * math.pi / 180) *
             math.cos(pan_angles[i] * math.pi / 180))
    z.append(distances[i] * math.cos(tilt_angles[i] * math.pi / 180))

file_name = 'data.csv'

# Create a list of lists where each sublist contains the values for each column
data = list(zip(x, y, z))

# Write the data to a CSV file with three columns
with open(file_name, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['x', 'y', 'z'])  # Write header row
    writer.writerows(data)

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.clear()
ax.scatter(x, y, z, c=y, cmap='viridis')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_xlim(-1.4, 1.4)
ax.set_ylim(0, 200)
ax.set_zlim(10, -25)
plt.show()
