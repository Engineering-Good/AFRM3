// test values
const byte TEST_PWM = 80;

// Motor interface
const int PIN_PWM_UP      = 9;
const int PIN_PWM_DOWN    = 10;
const int PIN_SLEEP       = 11;
const int PIN_REFLECTANCE = A1;

// User interface
const int PIN_DIR_UP      = 7;
const int PIN_DIR_DOWN    = 6;
const int PIN_BUTTON      = 5;

// Direction definitions
const int DIRECTION_NONE  = 0;
const int DIRECTION_UP    = 1;
const int DIRECTION_DOWN  = 2;

// Input signal definitions
const int SELECTED = LOW;   // pins are selected when they're pulled to ground by the switch

// Serial logging
const int LOG_INTERVAL_MILLIS = 1000; // log every second
unsigned long last_log_time = 0; // last time in milliseconds when the log output was run

// Encoder
volatile long encoder_count = 0;
long last_encoder_count = 0;
bool last_reflectance = LOW;
int reflectance_count = 0;
byte reflectance_bits = 0; // change data type to word for reflectance history of 16
const byte REFLECTANCE_HISTORY = 8; // use the last 5 reflectance values to determine reflectance; max. 8 if reflectance_bits is of type byte
const byte REFLECTANCE_OUTLIERS = 1; // allow 2 outliers in the reflectance history

unsigned long start_millis = 0;

void setup() {
  // initialise serial communication at 9600 bits per second
  Serial.begin(115200);

  // setup digital pins; encoder pins are setup by the Encoder library
  pinMode(PIN_PWM_UP, OUTPUT);
  pinMode(PIN_PWM_DOWN, OUTPUT);
  pinMode(PIN_SLEEP, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_DIR_UP, INPUT_PULLUP);
  pinMode(PIN_DIR_DOWN, INPUT_PULLUP);
  pinMode(PIN_REFLECTANCE, INPUT);

  // safe states to start
  digitalWrite(PIN_PWM_UP, LOW);
  digitalWrite(PIN_PWM_DOWN, LOW);
  digitalWrite(PIN_SLEEP, LOW);
}

int direction_input() {
  if(digitalRead(PIN_DIR_UP) == SELECTED && digitalRead(PIN_DIR_DOWN) != SELECTED) {
    return DIRECTION_UP;
  } else if(digitalRead(PIN_DIR_UP) != SELECTED && digitalRead(PIN_DIR_DOWN) == SELECTED) {
    return DIRECTION_DOWN;
  } else {
    return DIRECTION_NONE;
  }
}

void debug_log() {
  if(millis() >= last_log_time + LOG_INTERVAL_MILLIS) {
    last_log_time = millis();
    Serial.println("Test mode:");
    Serial.println("INPUTS:\t\t\t\tOUTPUTS:\t\t\tTIME:");
    Serial.println("Dir\tButton\tCounts\tPWM\tDir up\tDir dwn\t\tNow");
    if(direction_input() == DIRECTION_UP) {
      Serial.print("Up");
    } else if (direction_input() == DIRECTION_DOWN) {
      Serial.print("Down");
    } else {
      Serial.print("None");
    }
    Serial.print("\t");
    if(digitalRead(PIN_BUTTON) == SELECTED) {
      Serial.print("On");
    } else {
      Serial.print("Off");
    }
    Serial.print("\t");
    Serial.print(encoder_count);
    Serial.print("\t");
    Serial.print(TEST_PWM);
    Serial.print("\t");
    Serial.print("N/A for DRV8833");
    Serial.print("\t\t");
    Serial.print((millis()-start_millis)%1000000);
    Serial.print("\n");
  }
}

void stop_motor() {
  digitalWrite(PIN_PWM_UP, LOW);
  digitalWrite(PIN_PWM_DOWN, LOW);
  digitalWrite(PIN_SLEEP, LOW);
}

void move_motor(int dir, unsigned int pwm) {
  if(dir == DIRECTION_UP) {
    digitalWrite(PIN_SLEEP, HIGH);
    digitalWrite(PIN_PWM_DOWN, LOW);
    analogWrite(PIN_PWM_UP, TEST_PWM);
  } else if(dir == DIRECTION_DOWN) {
    digitalWrite(PIN_SLEEP, HIGH);
    digitalWrite(PIN_PWM_UP, LOW);
    analogWrite(PIN_PWM_DOWN, pwm);
  } else {
    // no defined direction -> stop motor
    stop_motor();
    return;
  }
}

void loop() {
  reflectance_bits = reflectance_bits << 1; // shift all bits to the left, freeing the rightmost bit
  reflectance_bits += digitalRead(PIN_REFLECTANCE); // set the rightmost bit to the current reflectance
  for(byte i = 0; i < REFLECTANCE_HISTORY; i++) { // walk through the bits starting from the right up to reflectance_history
    reflectance_count += (reflectance_bits & (1<<i)); // add the i'th bit of reflectance_bits
  }
  if(last_reflectance == 0 && reflectance_count >= (REFLECTANCE_HISTORY-REFLECTANCE_OUTLIERS)) {
    encoder_count++;
    last_reflectance = 1;
  }
  if(last_reflectance == 1 && reflectance_count <= REFLECTANCE_OUTLIERS) {
    encoder_count++;
    last_reflectance = 0;
  }
  reflectance_count = 0; // reset count for next round

  // reset encoder_count and time when button is pushed
  if(digitalRead(PIN_BUTTON) == SELECTED) {
    encoder_count = 0;

    start_millis = millis();
  }
  
  if(direction_input() == DIRECTION_UP) {
    // motor should go upwards
    move_motor(DIRECTION_UP, TEST_PWM);
  } else if (direction_input() == DIRECTION_DOWN) {
    // motor should go down
    move_motor(DIRECTION_DOWN, TEST_PWM);
  } else {
    // no direction -> stop motor
    stop_motor();
  }
  debug_log();
}

