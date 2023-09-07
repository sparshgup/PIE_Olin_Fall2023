const int LED[] = {8, 9, 10, 11, 12};     // LEDs connected
const uint8_t SW1 = 7;                    // SW1 connected to D7
const uint8_t POT = 0;                    // POT wiper is connected to A0

const uint16_t DEBOUNCE_INTERVAL = 100;   // Set the debounce interval

uint8_t switch1_state;                    // Global var to store the state of SW1
uint8_t mode = 0;                         // Global var to store the mode
int8_t bounce_led = 0;                    // Current active LED for bouncing lights
int8_t rand_led = 0;                      // Current active LED for random lights
int pot_value = 0;                        // Potentiometer value
uint32_t last_debounce_time = 0;          // Store the last debounce time

void setup() {
  for (int i = 0; i < 5; i++){
    pinMode(LED[i], OUTPUT);
  }
  pinMode(SW1, INPUT);

  switch1_state = digitalRead(SW1);
}

void loop() {
  uint32_t current_time = millis();                 
  uint8_t SW1_state = digitalRead(SW1);             // Record the state of SW1

  if (SW1_state != switch1_state && (current_time - last_debounce_time) > DEBOUNCE_INTERVAL) {
    if (SW1_state == LOW) {
      mode = (mode + 1) % 5;  // Cycle through the 5 modes
    }
    switch1_state = SW1_state;
    last_debounce_time = current_time;
  }

  // Read potentiometer value
  pot_value = analogRead(POT);

  switch (mode) {
    case 0:  // All LEDs off
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], LOW);
      }
      break;

    case 1:  // All LEDs flashing
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], current_time % 1000 < 500 ? HIGH : LOW);
      }
      break;

    case 2:  // All LEDs on
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], HIGH);
      }
      break;

    case 3:  // Bouncing lights
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], i == bounce_led ? HIGH : LOW);
      }
      bounce_led = (bounce_led + 1) % 5;
      break;

    case 4:  // Random LEDs lighting up
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], i == rand_led ? HIGH : LOW);
      }
      rand_led = random(5);
      break;
  }

  // Adjust the speed of the modes using potentiometer
  delay(map(pot_value, 0, 1023, 50, 500));
}
