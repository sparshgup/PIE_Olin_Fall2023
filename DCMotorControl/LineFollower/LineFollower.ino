#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(10, 1); 
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(10, 2);

int IRSensor2 = A2; // IR sensor pin for left-most sensor
int IRSensor3 = A3; // IR sensor pin for middle-left sensor
int IRSensor4 = A4; // IR sensor pin for middle-right sensor
int IRSensor5 = A5; // IR sensor pin for right-most sensor

// IR sensor cutoff value reading for determing whether line/not line
int cutoffValue = 300;

// Specify PID initial parameters
double Input, Output, Setpoint;
PID myPID(&Input, &Output, &Setpoint,2,0.1,0.5, DIRECT);

void setup() {
  Serial.begin(115200); // Set Serial Baud Rate

  // Start motor with the default frequency 1.6KHz
  AFMS.begin();  
  
  // Intialize motors
  myMotor1->setSpeed(1);  // Set Motor 1 speed
  myMotor1->release()
  myMotor2->setSpeed(1);  // Set Motor 2 speed
  myMotor2->release()

  // Initialize IR sensors
  pinMode(IRSensor2, INPUT); // IR Sensor 2 pin INPUT
  pinMode(IRSensor3, INPUT); // IR Sensor 3 pin INPUT
  pinMode(IRSensor4, INPUT); // IR Sensor 4 pin INPUT
  pinMode(IRSensor5, INPUT); // IR Sensor 5 pin INPUT

  // Initialize PID setpoint
  Setpoint = 0;

  // Turn the PID on
  myPID.SetMode(AUTOMATIC);

  // Check if serial is working or not
  Serial.println("===== Serial Working ====="); 
}

void loop() {
  // IR sensor readings
  int IR2 = analogRead(IRSensor2); // Set the IR Sensor 2 as Input
  int IR3 = analogRead(IRSensor3); // Set the IR Sensor 3 as Input
  int IR4 = analogRead(IRSensor4); // Set the IR Sensor 4 as Input
  int IR5 = analogRead(IRSensor5); // Set the IR Sensor 5 as Input

  // Classify IR sensor readings as 0 or 1 based on cutoffValue
  int IR2state = (IR2 > cutoffValue) ? 1 : 0;
  int IR3state = (IR3 > cutoffValue) ? 1 : 0;
  int IR4state = (IR4 > cutoffValue) ? 1 : 0;
  int IR5state = (IR5 > cutoffValue) ? 1 : 0;

  // Print sensor readings
  Serial.print("==== IR sensor readings ====");
  Serial.print("| 2 | 3 | 4 | 5 |");
  Serial.print("| ", IR2State, " | ", IR3State, " | ", IR4State, " | ", IR5State, " |");

  // Calculate error to determine the direction of the line
  weightedError = (sensor2State * 2 + sensor4State - sensor5State * 2) * 0.5;

  // Update PID Input based on weightedError
  Input = weightedError;

  // Compute PID control output
  myPID.compute();

  // Adjust motor speeds based on PID input
  int motor1Speed = constrain(1 + Output, 0, 255);
  int motor1Speed = constrain(1 + Output, 0, 255);

  myMotor1->setSpeed(motor1Speed);
  myMotor2->setSpeed(motor2Speed); 

  // Run motors
  myMotor1->step(1, FORWARD, INTERLEAVE)
  myMotor2->step(1, FORWARD, INTERLEAVE)
}
