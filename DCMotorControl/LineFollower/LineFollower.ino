#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(3); 
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(4);

int IRSensor0 = A0; // IR sensor pin for left-most sensor
int IRSensor1 = A1; // IR sensor pin for middle-left sensor
int IRSensor2 = A2; // IR sensor pin for middle-right sensor
int IRSensor3 = A3; // IR sensor pin for right-most sensor

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
  pinMode(IRSensor0, INPUT); // IR Sensor 0 pin INPUT
  pinMode(IRSensor1, INPUT); // IR Sensor 1 pin INPUT
  pinMode(IRSensor2, INPUT); // IR Sensor 2 pin INPUT
  pinMode(IRSensor3, INPUT); // IR Sensor 3 pin INPUT
}

void loop() {
  // IR sensor readings
  int IR0 = analogRead(IRSensor0); // Set the IR Sensor 1 as Input
  int IR1 = analogRead(IRSensor0); // Set the IR Sensor 2 as Input
  int IR2 = analogRead(IRSensor0); // Set the IR Sensor 3 as Input
  int IR3 = analogRead(IRSensor0); // Set the IR Sensor 4 as Input

  // Output IR readings and motor speeds to serial
  Serial.println(IR0);
  Serial.print(",");
  Serial.print(IR1);
  Serial.print(",");
  Serial.print(IR2);
  Serial.print(",");
  Serial.print(IR3);

  // Classify IR sensor readings as 0 or 1 based on cutoffValue
  int IR0state = (IR0 > cutoffValue) ? 1 : 0;
  int IR1state = (IR1 > cutoffValue) ? 1 : 0;
  int IR2state = (IR2 > cutoffValue) ? 1 : 0;
  int IR3state = (IR3 > cutoffValue) ? 1 : 0;

  // IR sensor state-based cases to follow the line
  // Modify motor speeds based on that
  if (IR0state==0 & IR1state==0 & IR2state==0 & IR3state==0){
    int motor1Speed = speed;
    int motor2Speed = speed;

    Serial.print(",");
    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.print(motor2Speed);

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

  }
  if (IR0state==1 & IR1state==1 & IR2state==1 & IR3state==1){
    int motor1Speed = speed;
    int motor2Speed = speed;

    Serial.print(",");
    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.print(motor2Speed);

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

  } 
  else if (IR0state==0 & IR1state==0 & IR2state==1 & IR3state==0){
    int motor1Speed = speed;
    int motor2Speed = 0;

    Serial.print(",");
    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.print(motor2Speed);

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

  }

  else if (IR0state==0 & IR1state==0 & IR2state==0 & IR3state==1){
    int motor1Speed = speed;
    int motor2Speed = 0;

    Serial.print(",");
    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.print(motor2Speed);

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

  }

  else if (IR0state==0 & IR1state==1 & IR2state==0 & IR3state==0){
    int motor1Speed = 0;
    int motor2Speed = speed;

    Serial.print(",");
    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.print(motor2Speed);

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

  }

  else if (IR0state==1 & IR1state==0 & IR2state==0 & IR3state==0){
    int motor1Speed = 0;
    int motor2Speed = speed;

    Serial.print(",");
    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.print(motor2Speed);

    myMotor1->setSpeed(motor1Speed);
    myMotor2->setSpeed(motor2Speed); 

  }

  else if (IR0state==1 & IR1state==1 & IR2state==1 & IR3state==0){
    int motor1Speed = 0;
    int motor2Speed = speed+30;

    Serial.print(",");
    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.print(motor2Speed);

    while (IR3state==0){
      IR3 = analogRead(IRSensor3); // Set the IR Sensor 5 as Input
      IR3state = (IR3 > cutoffValue) ? 1 : 0;
      myMotor1->setSpeed(motor1Speed);
      myMotor2->setSpeed(motor2Speed); 
    }
    myMotor1->setSpeed(speed);
    myMotor2->setSpeed(0);
    delay(100);
  }

  else if (IR0state==1 & IR1state==1 & IR2state==0 & IR3state==0){
    int motor1Speed = 0;
    int motor2Speed = speed+20;

    Serial.print(",");
    Serial.print(motor1Speed);
    Serial.print(",");
    Serial.print(motor2Speed);
    
    while (IR3state==0){
      IR3 = analogRead(IRSensor3);
      IR3state = (IR3 > cutoffValue) ? 1 : 0;
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
