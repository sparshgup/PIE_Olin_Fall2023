#include <Servo.h>

Servo tilt_servo, pan_servo;  // creates servo object for tilt and pan servo

uint8_t PAN_PIN = 9; // Variable representing the digital pin connected to the pan servo
uint8_t TILT_PIN = 10; // Variable representing the digital pin connected to the tilt servo
int IR_SENSOR_PIN = 0; // variable representing the analog pin that the IR sensor is connected to

int pan = 0;    // variable representing the starting pan angle
int tilt = 75;   // variable representing the starting tilt andlge

int pan_max = 50;
int pan_min = 0;
int pan_change = 1;

int tilt_max = 120;
int tilt_min = 75;

uint16_t x, y, z; // variables used to calculating/averaging IR sensor output
double res = 0; // variable used to store average IR sensor output value

bool running = true; // bool variable for stopping the movement and data collection after a scan

double get_IR_data() {                       // Function to get data fro the IR sensor. Three data points
  for(int i = 0; i < 300; i++){              // are taken at once and that the smallest is taken to account for
    x = analogRead(IR_SENSOR_PIN);           // the spike that happens in the sensors output at regular intervals.
    y = analogRead(IR_SENSOR_PIN);           // 300 of these measurements happen and are then averaged. This average
    z = analogRead(IR_SENSOR_PIN);           // value is then fed into the transfer function we calculated for the sensor.
    res += (double)min(min(x, y), z);
    delayMicroseconds(48);
  }
  res /= 300;

  return (286 + -43 * log((double)res)); // transfer function is distance = 286 + -43 * ln(sensor output)
  }

void send_IR_data(int pan, int tilt, double IR_data) {                      // Function to send the IR sensor output over
    Serial.print(pan); Serial.print(",");              // a serial connection. Converts the 8 bit values to 
    Serial.print(tilt); Serial.print(",");             // angle values.
    Serial.println(IR_data);
}

void setup() {
  Serial.begin(115200);
  tilt_servo.attach(TILT_PIN);  // Attaches the servo on the pin TILT_PIN to the servo object
  pan_servo.attach(PAN_PIN);    // Attaches the servo on pin PAN_PIN to the servo object
  pan_servo.write(pan);         // Moves the pan servo to the stating position
  delay(1000);
  tilt_servo.write(tilt);       // Moves the tilt servo to the starting position
  delay(1000);
}

void loop() {


  while (running) {                                             // While the scanner has not finished panning all angles, the scanner changes pan angle
    for (pan = pan_min; pan <= pan_max; pan += pan_change) {    // then takes distance measurements over the course of the min and mac tilt angle defined above.
                                                                // The measured data is sent over serial connection after each tilt interval.
      for (tilt = tilt_min; tilt <= tilt_max; tilt += 1) {      // Iterate through tilt angles and take data
        tilt_servo.write(tilt);
        delay(10);
        send_IR_data(pan, tilt, get_IR_data());
      }
      pan_servo.write(pan);                                     // Change pan angle
      delay(10);
    }
    running = false;                                          // Stop panning/tilting and taking data once all angles within range have been iterated through
  }
  Serial.println("end");
}
