#include <Wire.h>
#include <Adafruit_MotorShield.h>
// #include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(10, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(10, 2);

int IRSensor2 = A2; // connect IR sensor module to Arduino pin left most sensor
int IRSensor3 = A3; // connect IR sensor module to Arduino pin left middle sensor
int IRSensor4 = A4; // connect IR sensor module to Arduino pin right middle sensor
int IRSensor5 = A5; // connect IR sensor module to Arduino pin right most sensor

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  AFMS.begin();  // create with the default frequency 1.6KHz
  
  myMotor1->setSpeed(4);  //  rpm 
  myMotor2->setSpeed(4);  //  rpm   

  // put your setup code here, to run once:
  pinMode(IRSensor2, INPUT); // IR Sensor pin INPUT
  pinMode(IRSensor3, INPUT); // IR Sensor pin INPUT
  pinMode(IRSensor4, INPUT); // IR Sensor pin INPUT
  pinMode(IRSensor5, INPUT); // IR Sensor pin INPUT
  Serial.println("Serial Working"); // Test to check if serial is working or not

}

void loop() {
  int sensorStatus2 = analogRead(IRSensor2); // Set the GPIO as Input
  int sensorStatus3 = analogRead(IRSensor3); // Set the GPIO as Input
  int sensorStatus4 = analogRead(IRSensor4); // Set the GPIO as Input
  int sensorStatus5 = analogRead(IRSensor5); // Set the GPIO as Input

  myMotor1->step(random(30,50), FORWARD, DOUBLE); 
  myMotor2->step(random(30,50), FORWARD, DOUBLE); 

}
