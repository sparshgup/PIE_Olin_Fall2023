#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <PID_v1.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(3); 
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(4);

int IRSensor2 = A2; // IR sensor pin for left-most sensor
int IRSensor3 = A3; // IR sensor pin for middle-left sensor
int IRSensor4 = A4; // IR sensor pin for middle-right sensor
int IRSensor5 = A5; // IR sensor pin for right-most sensor


void setup() {
  Serial.begin(9600); // Set Serial Baud Rate

  // Start motor with the default frequency 1.6KHz
  AFMS.begin();  
  
  // Intialize motors
  myMotor1->setSpeed(0);  // Set Motor 1 speed
  myMotor2->setSpeed(0);  // Set Motor 2 speed

  // Initialize IR sensors
  pinMode(IRSensor2, INPUT); // IR Sensor 2 pin INPUT
  pinMode(IRSensor3, INPUT); // IR Sensor 3 pin INPUT
  pinMode(IRSensor4, INPUT); // IR Sensor 4 pin INPUT
  pinMode(IRSensor5, INPUT); // IR Sensor 5 pin INPUT


  // Check if serial is working or not
  Serial.println("");
  Serial.println("===== Serial Working ====="); 
  Serial.println("==== IR sensor readings ====");
  Serial.println("| 2 | 3 | 4 | 5 |");
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
  Serial.println(IR2state);
  Serial.print("|");
  Serial.print(IR3state);
  Serial.print("|");
  Serial.print(IR4state);
  Serial.print("|");
  Serial.print(IR5state);
  Serial.print("|");

  // Calculate error to determine the direction of the line
  double weightedError = (IR2state + IR3state + IR4state + IR5state) / 4.0;

  // Adjust motor speeds based on PID input
  int motor1Speed = constrain(40 + Output, 30, 60);
  int motor2Speed = constrain(40 + Output, 30, 60);

  myMotor1->setSpeed(motor1Speed);
  myMotor2->setSpeed(motor2Speed); 

  // Run motors
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
}
