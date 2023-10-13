#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(3); 
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(4);

int IRSensor2 = A0; // IR sensor pin for left-most sensor
int IRSensor3 = A1; // IR sensor pin for middle-left sensor
int IRSensor4 = A2; // IR sensor pin for middle-right sensor
int IRSensor5 = A3; // IR sensor pin for right-most sensor

int cutoffValue = 200;
int speed = 30;

void setup() {

  // Start motor with the default frequency 1.6KHz
  AFMS.begin();  
  
  Serial.begin(9600); // Set Serial Baud Rate

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
  Serial.print(IR2state);
  Serial.print(",");
  Serial.print(IR3state);
  Serial.print(",");
  Serial.print(IR4state);
  Serial.print(",");
  Serial.print(IR5state);
  Serial.print(",");

  if (IR2state==0 & IR3state==0 & IR4state==0 & IR5state==0){
    int motor1Speed = speed;
    int motor2Speed = speed;

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.println(motor2Speed);
  }
  if (IR2state==1 & IR3state==1 & IR4state==1 & IR5state==1){
    int motor1Speed = 0;
    int motor2Speed = 0;

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.println(motor2Speed);
  } 
  else if (IR2state==0 & IR3state==0 & IR4state==1 & IR5state==0){
    int motor1Speed = speed;
    int motor2Speed = 0;

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.println(motor2Speed);
  }

  else if (IR2state==0 & IR3state==0 & IR4state==0 & IR5state==1){
    int motor1Speed = speed;
    int motor2Speed = 0;

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.println(motor2Speed);
  }

  else if (IR2state==0 & IR3state==1 & IR4state==0 & IR5state==0){
    int motor1Speed = 0;
    int motor2Speed = speed;

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.println(motor2Speed);
  }

  else if (IR2state==1 & IR3state==0 & IR4state==0 & IR5state==0){
    int motor1Speed = 0;
    int motor2Speed = speed;

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.println(motor2Speed);
  }

  else if (IR2state==1 & IR3state==1 & IR4state==1 & IR5state==0){
    int motor1Speed = 0;
    int motor2Speed = speed+30;

    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.println(motor2Speed);

    while (IR5state==0){
      IR5 = analogRead(IRSensor5); // Set the IR Sensor 5 as Input
      IR5state = (IR5 > cutoffValue) ? 1 : 0;
      myMotor1->setSpeed(motor1Speed);
      myMotor2->setSpeed(motor2Speed); 
    }
    myMotor1->setSpeed(speed);
    myMotor2->setSpeed(0);
    delay(100);
  }

  else if (IR2state==1 & IR3state==1 & IR4state==0 & IR5state==0){
    int motor1Speed = 0;
    int motor2Speed = speed+20;

    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.println(motor2Speed);
    
    while (IR5state==0){
      IR5 = analogRead(IRSensor5); // Set the IR Sensor 5 as Input
      IR5state = (IR5 > cutoffValue) ? 1 : 0;
      myMotor1->setSpeed(motor1Speed);
      myMotor2->setSpeed(motor2Speed);
    }

    myMotor1->setSpeed(speed);
    myMotor2->setSpeed(0);
    delay(100);
  }

  // Run motors
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
}