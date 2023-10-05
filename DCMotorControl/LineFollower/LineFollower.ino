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

// Specify PID initial parameters
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

void setup() {
  Serial.begin(115200); // Set Serial Baud Rate

  // Start motor with the default frequency 1.6KHz
  AFMS.begin();  
  
  // Intialize motors
  myMotor1->setSpeed(1);  // Set Motor 1 speed
  myMotor1->run(FORWARD);
  myMotor1->run(RELEASE)
  myMotor2->setSpeed(1);  // Set Motor 2 speed
  myMotor2->run(FORWARD);
  myMotor2->run(RELEASE)

  // Initialize IR sensors
  pinMode(IRSensor2, INPUT); // IR Sensor 2 pin INPUT
  pinMode(IRSensor3, INPUT); // IR Sensor 3 pin INPUT
  pinMode(IRSensor4, INPUT); // IR Sensor 4 pin INPUT
  pinMode(IRSensor5, INPUT); // IR Sensor 5 pin INPUT

  // Initialize PID setpoint
  Setpoint = 100;

  // Turn the PID on
  myPID.SetMode(AUTOMATIC);

  // Check if serial is working or not
  Serial.println("===== Serial Working ====="); 
}

void loop() {
  int IR2 = analogRead(IRSensor2); // Set the IR Sensor 2 as Input
  int IR3 = analogRead(IRSensor3); // Set the IR Sensor 3 as Input
  int IR4 = analogRead(IRSensor4); // Set the IR Sensor 4 as Input
  int IR5 = analogRead(IRSensor5); // Set the IR Sensor 5 as Input

  myMotor1->setSpeed(10);
  myMotor2->setSpeed(10); 

  myPID.compute();

}
