/* values to adapt for speed control:
 *  STUCK_SPEED_INCREMENT
 *  SPEED_INCREMENT
 *  MAX_PWM_BOOSTS
 *  BOOST_PWM
 *  MIN_PWM_START_UP
 *  MIN_PWM_CONT_UP
 *  MIN_PWM_START_DOWN
 *  MIN_PWM_CONT_DOWN
 */

/* PWM values below the motor will not start/continue rotating anymore. If this is too high,
 * try adding a capacitor on the motor controller output to flatten the PWM 
 */
// Rainbow #1
/*const unsigned int MIN_PWM_START_UP = 100;
const unsigned int MIN_PWM_CONT_UP = 85;
const unsigned int MIN_PWM_START_DOWN = 80;
const unsigned int MIN_PWM_CONT_DOWN = 60;*/

// Rainbow #2
/*const unsigned int MIN_PWM_START_UP = 120;
const unsigned int MIN_PWM_CONT_UP = 75;
const unsigned int MIN_PWM_START_DOWN = 90;
const unsigned int MIN_PWM_CONT_DOWN = 50;*/

// CPAS #1 [SWAP PINS 9 and 10]
/*const unsigned int MIN_PWM_START_UP = 140;
const unsigned int MIN_PWM_CONT_UP = 100;
const unsigned int MIN_PWM_START_DOWN = 110;
const unsigned int MIN_PWM_CONT_DOWN = 70;*/

// CPAS #2 
const unsigned int MIN_PWM_START_UP = 160;
const unsigned int MIN_PWM_CONT_UP = 125;
const unsigned int MIN_PWM_START_DOWN = 110;
const unsigned int MIN_PWM_CONT_DOWN = 75;

/* Variable names in ALL_CAPS are constant configuration values that can be changed to adapt
 * the code to different hardware. They are not modified by the software at runtime.
 */

// Motor interface
const int PIN_PWM_UP      = 9;
const int PIN_PWM_DOWN    = 10;
const int PIN_SLEEP       = 11; // not connected and without effect for DRV8835
const int PIN_REFLECTANCE = 1; // use A1 for digital input; 1 for analog input.

// Input signal definitions
const int SELECTED = LOW;   // pins are selected when they're pulled to ground by the switch

// User interface
const int PIN_DIR_UP      = 7;
const int PIN_DIR_DOWN    = 6;
const int PIN_BUTTON      = 5;

// Direction definitions
const int DIRECTION_NONE  = 0;
const int DIRECTION_UP    = 1;
const int DIRECTION_DOWN  = 2;

// Serial logging
const int LOG_INTERVAL_MILLIS = 1000; // log every second

// Encoder
const int REFLECTANCE_THRESHOLD = 600; // ~2.9V
const byte REFLECTANCE_HISTORY = 8; // use the last 8 reflectance values to determine reflectance; max. 8 if reflectance_bits is of type byte
const byte REFLECTANCE_OUTLIERS = 2; // allow 2 bits in the reflectance history to be different

// Stuck-check
const int STUCK_CHECK_MILLIS = 1000; // check every second whether the motor is stuck
const int INPUT_CHANGE_NO_STUCK_MILLIS = 2000; // suppress stuck check for 2s after direction change
const int STUCK_ENCODER_TOLERANCE = 0; // how much +/- the encoder value may still move when the motor is stuck (to offset some movement from boosting PWM)
const int MAX_PWM_BOOSTS = 1; // number of stuck-check intervals during which to apply boost PWM
const int BOOST_PWM = 180;
const int STUCK_SPEED_INCREMENT = 5; // increase PWM by this value after a boost, to reduce the chances of becoming stuck again

// Speed control
const unsigned int ANTHEM_DURATION = 90; // duration of anthem in seconds
const unsigned int SPEED_CONTROL_MILLIS = 2000; // adjust motor speed every two seconds
const unsigned int COUNTS_TOLERANCE = 4; // adjust motor speed when flag position is more than 4 counts off the intended position
const unsigned int SPEED_INCREMENT = 5; // adjust motor PWM in steps of 5 during speed control
const unsigned int START_PWM_MILLIS = 100; // time after an input change to use MIN_PWM_START_UP/DOWN as minimum PWM value, instead of MIN_PWM_CONT_UP/DOWN

// Calibration mode
const unsigned int CALIBRATION_PWM = 150;

// EEPROM storage see below

/* Variable names in small letters are working variables that are dynamically changed at runtime.
 * they are initialised here to some default value that probably doesn't need to be changed to
 * adapt or tune the code.
 */

// Variables to detect an input change
int last_button = !SELECTED;
int last_direction = DIRECTION_NONE;

// Serial logging
unsigned long last_log_time = 0; // last time in milliseconds when the log output was run

// Encoder
volatile long encoder_count = 0;
long last_encoder_count = 0;
bool last_reflectance = LOW;
int reflectance_count = 0;
byte reflectance_bits = 0; // change data type to word for reflectance history of 16

// Stuck-check
unsigned long last_stuck_check = 0;
unsigned long last_input_change_time = 0;
bool is_stuck = false;
int boost_count = 0;
bool boost_pwm = false;

// Speed control
unsigned long length_counts = 0; // length of the flag pole in encoder counts
unsigned int recommended_pwm_up = 0; // speed as determined during calibration, used as starting point for speed control
unsigned int recommended_pwm_down = 0;
unsigned int current_pwm = 0;
unsigned long start_time = 0;
unsigned long last_speed_control = 0;

// Calibration mode
bool calibration_mode = false;
unsigned long cal_start_time_up = 0;
unsigned long cal_start_time_down = 0;
bool cal_up_done = false;
bool cal_down_done = false;
unsigned long cal_distance_up = 0;
unsigned long cal_distance_down = 0;
unsigned int cal_pwm_up = 0;
unsigned int cal_pwm_down = 0;

// EEPROM storage
#include <EEPROM.h>
const int ADDRESS_LENGTH = 0; // length_counts is stored at this address
const int ADDRESS_PWM_UP = ADDRESS_LENGTH + sizeof(length_counts); // recommended_pwm_up is stored behind length counts
const int ADDRESS_PWM_DOWN = ADDRESS_PWM_UP + sizeof(recommended_pwm_up); // recommended_pwm_down is stored behind recommended_pwm_up

/* This function initialises the I/O pins and reads configuration values from the EEPROM
 */
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

  // output safe states to start
  digitalWrite(PIN_PWM_UP, LOW);
  digitalWrite(PIN_PWM_DOWN, LOW);
  digitalWrite(PIN_SLEEP, LOW);

  // If push button is pushed during startup, enter configuration mode
  if(digitalRead(PIN_BUTTON) == SELECTED) {
    calibration_mode = true;
  }

  // read values from EEPROM
  EEPROM.get(ADDRESS_LENGTH, length_counts);
  EEPROM.get(ADDRESS_PWM_UP, recommended_pwm_up);
  EEPROM.get(ADDRESS_PWM_DOWN, recommended_pwm_down);

  if(length_counts == 0 || recommended_pwm_up == 0 || recommended_pwm_down == 0) {
    // incomplete calibration -> enter calibration mode
    calibration_mode = true;
  }

  if(recommended_pwm_up < MIN_PWM_CONT_UP) recommended_pwm_up = MIN_PWM_CONT_UP;
  if(recommended_pwm_down < MIN_PWM_CONT_DOWN) recommended_pwm_down = MIN_PWM_CONT_DOWN;
}

/* This function returns DIRECTION_UP, DIRECTION_DOWN or DIRECTION_NONE depending on
 * the state of the direction switch pins.
 */
int direction_input() {
  if(digitalRead(PIN_DIR_UP) == SELECTED && digitalRead(PIN_DIR_DOWN) != SELECTED) {
    return DIRECTION_UP;
  } else if(digitalRead(PIN_DIR_UP) != SELECTED && digitalRead(PIN_DIR_DOWN) == SELECTED) {
    return DIRECTION_DOWN;
  } else {
    return DIRECTION_NONE;
  }
}

/* This function is responsible for printing debugging information on the
 *  serial console. Open the Arduino Serial Monitor to see the output.
 */
void debug_log() {
  if(millis() >= last_log_time + LOG_INTERVAL_MILLIS) {
    last_log_time = millis();
    if(calibration_mode) {
      Serial.println("Calibration:");
    }
    Serial.println("INPUTS:\t\t\tOUTPUT:\t\tTIME:");
    Serial.println("Dir\tButton\tCounts\tPWM\t\tNow\tinputchange");
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
    if(calibration_mode) {
      Serial.print(CALIBRATION_PWM);
    } else {
      Serial.print(current_pwm);
    }
    Serial.print("\t\t");
    Serial.print(millis()%1000000);
    Serial.print("\t");
    Serial.print(last_input_change_time%1000000);
    Serial.print("\n");
  }
}

/* Stop the motor
 */
void stop_motor() {
  digitalWrite(PIN_PWM_UP, LOW);
  digitalWrite(PIN_PWM_DOWN, LOW);
  digitalWrite(PIN_SLEEP, LOW);
}

/* This function generates the output signals to move the motor
 * at the desired speed upwards or downwards. If boost_pwm is true,
 * then the BOOST_PWM is output. It also takes care of applying
 * the minimum PWM values for start-up and continuous operation.
 */
void move_motor(int dir, unsigned int pwm) {
  if(dir == DIRECTION_UP) {
    digitalWrite(PIN_SLEEP, HIGH);
    digitalWrite(PIN_PWM_DOWN, LOW);
    if(boost_pwm) {
      analogWrite(PIN_PWM_UP, BOOST_PWM);
    } else if(millis() <= last_input_change_time + START_PWM_MILLIS) {
      analogWrite(PIN_PWM_UP, max(pwm, MIN_PWM_START_UP));
    } else {
      analogWrite(PIN_PWM_UP, max(pwm, MIN_PWM_CONT_UP));
    }
  } else if(dir == DIRECTION_DOWN) {
    digitalWrite(PIN_SLEEP, HIGH);
    digitalWrite(PIN_PWM_UP, LOW);
    if(boost_pwm) {
      analogWrite(PIN_PWM_DOWN, BOOST_PWM);
    } else if(millis() <= last_input_change_time + START_PWM_MILLIS) {
      analogWrite(PIN_PWM_DOWN, max(pwm, MIN_PWM_START_DOWN));
    } else {
      analogWrite(PIN_PWM_DOWN, max(pwm, MIN_PWM_CONT_DOWN));
    }
  } else {
    // no defined direction -> stop motor
    stop_motor();
    return;
  }
}

/* This function is called periodically to detect if any change happened
 * to the direction switch or push button. This information is used in
 * move_motor() to apply the minimum start-up PWM, to suppress the "stuck
 * check" to allow some time for the motor to start moving, and to help
 * with time measurement during calibration.
 */
void detect_input_change() {
  if(direction_input() != last_direction) {
    /* If the direction switch position changed, reset the encoder count, PWM value and boost counter.
     * Also the time of change is stored. It is used to suppress the stuck detection for a short while
     * after a change of direction to allow the motor to spin up.
     */
    encoder_count = 0; // reset start values for next run in other direction
    if(direction_input() == DIRECTION_UP) {
      current_pwm = recommended_pwm_up;
    } else if(direction_input() == DIRECTION_DOWN) {
      current_pwm = recommended_pwm_down;
    }
    last_direction = direction_input();
    last_input_change_time = millis();
    boost_count = 0; // reset "boost"
  }
  if(digitalRead(PIN_BUTTON) != last_button) {
    /* If the push button state changes, the encoder count and PWM values are kept because the motor will
     * continue in the same direction. But the boost count is reset and the time of the change is stored.
     * The time is used to suppress the stuck detection for a short while to allow the motor to spin up.
     */
    last_button = digitalRead(PIN_BUTTON);
    last_input_change_time = millis();
    boost_count = 0; // reset "boost"
  }
}

/* Every STUCK_CHECK_MILLIS milliseconds, this functions checks if the encoder value has changed
 * compared to the previous check. There is a certain tolerance (STUCK_ENCODER_TOLERANCE) to
 * allow for noisy encoder values and slight elastic turns of the motor during boost.
 * This check is suppressed for a short time (INPUT_CHANGE_NO_STUCK_MILLIS) to allow the motor
 * to spin up first.
 * If no significant change in encoder count is detected, a "boost" will be activated for a limited
 * number of times (MAX_PWM_BOOSTS). BOOST_PWM is applied to the motor (in move_motor()) to see if
 * the motor only got stuck due to running at low power. If the encoder still doesn't change in the
 * next check after the maximum number of boosts has been applied, the motor is declared stuck and
 * stopped.
 */
void stuck_check() {
  if(millis() >= last_stuck_check + STUCK_CHECK_MILLIS) {
    last_stuck_check = millis();
    if(millis() <= last_input_change_time + INPUT_CHANGE_NO_STUCK_MILLIS) {
      Serial.println("Skipping stuck check (direction changed)");
      is_stuck = false; // skip the stuck-check to allow for motor startup
    } else {
      if(encoder_count <= (last_encoder_count + STUCK_ENCODER_TOLERANCE) && encoder_count >= (last_encoder_count - STUCK_ENCODER_TOLERANCE)) {
        // motor is stuck
        if(boost_count < MAX_PWM_BOOSTS) {
          // see if it can be solved by higher PWM:
          boost_pwm = true;
          boost_count++;
          last_encoder_count = encoder_count;
          is_stuck = false;
          current_pwm += STUCK_SPEED_INCREMENT;
          Serial.print("Stuck detected -> Boost motor (");
          Serial.print(boost_count);
          Serial.print("/");
          Serial.print(MAX_PWM_BOOSTS);
          Serial.println(")");
        } else {
          Serial.println("Stuck detected");
          stop_motor();
          is_stuck = true;
          boost_pwm = false;
        }
      } else {
        // motor is moving
        last_encoder_count = encoder_count;
        is_stuck = false;
        boost_pwm = false; // reset "boost"
        boost_count = 0;
      }
    }
  }
}

/* It is assumed that calibration mode is started from the bottom up, with the the flag at the lowest position.
 * To start the calibration, the direction switch is set to the UP position. The motor will move the flag
 * upwards at CALIBRATION_PWM until it reaches the top of the flag pole and is blocked there. The time and
 * the number of encoder counts it took to move the flag up are measured/counted. The time it took at
 * CALIBRATION_PWM and the duration of the national anthem are put in relation to determine the recommended
 * PWM value for the upwards direction.
 * Afterwards, the same procedure is repeated downwards. The encoder counts for upwards and downwards
 * direction are averaged to minimize noise. The resulting flagpole length (measured in encoder counts) is
 * used for speed control in speed_control().
 * Flag pole length and recommended PWM values are saved to EEPROM memory.
 */
void calibration_loop() {
  if(!cal_up_done && direction_input() == DIRECTION_UP) {
    if(millis() <= last_input_change_time + INPUT_CHANGE_NO_STUCK_MILLIS) cal_start_time_up = millis();
    stuck_check();
    if(!is_stuck) {
      move_motor(DIRECTION_UP, CALIBRATION_PWM);
    } else {
      // motor is stuck -> probably reached end of the pole -> calculate recommended PWM for upwards
      cal_distance_up = abs(encoder_count);
      encoder_count = 0; // reset encoder count for following downwards calibration
      last_encoder_count = 0;
      cal_pwm_up = CALIBRATION_PWM * (millis() - cal_start_time_up) / 1000 / ANTHEM_DURATION;
      if(cal_pwm_up > 255) {
        cal_pwm_up = 255; // 255 is the maximum PWM value (=full power)
        Serial.println("Recommended upwards PWM larger than 255!");
      }
      Serial.println("Upwards calibration:");
      Serial.print("Measured distance (up): ");
      Serial.print(cal_distance_up);
      Serial.println(" encoder counts");
      Serial.print("Recommended upwards PWM: ");
      Serial.println(cal_pwm_up);
      cal_up_done = true;
    }
  } else if(!cal_down_done && direction_input() == DIRECTION_DOWN) {
    if(millis() <= last_input_change_time + INPUT_CHANGE_NO_STUCK_MILLIS) cal_start_time_down = millis();
    stuck_check();
    if(!is_stuck) {
      move_motor(DIRECTION_DOWN, CALIBRATION_PWM);
    } else {
      // motor is stuck -> probably reached end of the pole -> calculate recommended PWM for downwards
      cal_distance_down = abs(encoder_count);
      encoder_count = 0;
      last_encoder_count = 0;
      cal_pwm_down = CALIBRATION_PWM * (millis() - cal_start_time_down) / 1000 / ANTHEM_DURATION;
      if(cal_pwm_down > 255) {
        cal_pwm_down = 255;
        Serial.println("Recommended downwards PWM larger than 255!"); // 255 is the maximum PWM value (=full power)
      }
      // store recommended up/down speeds and average distance in EEPROM
      EEPROM.put(ADDRESS_LENGTH, (cal_distance_up + cal_distance_down)/2);
      EEPROM.put(ADDRESS_PWM_UP, cal_pwm_up);
      EEPROM.put(ADDRESS_PWM_DOWN, cal_pwm_down);
      Serial.println("Downwards calibration:");
      Serial.print("Measured distance (down): ");
      Serial.print(cal_distance_down);
      Serial.println(" encoder counts");
      Serial.print("Average distance (up/down): ");
      Serial.print((cal_distance_up + cal_distance_down)/2);
      Serial.println(" encoder counts");
      Serial.print("Recommended downwards PWM: ");
      Serial.println(cal_pwm_down);
      cal_down_done = true;
    }
  } else {
    stop_motor();
  }
}

/* This function compares the position in encoder counts where the flag should be in order to reach on time
 * to the actual number of encoder counts. The speed is then increased or decreased accordingly, but cannot
 * be reduced below the MIN_PWM value that is required to keep the motor moving.
 * If the flag position is within the tolerance, the PWM is actually both increased and decreased, and so
 * effectively remains unchanged.
 * If the push button is let go without the motor being stuck, the start_time variable is not reset. Therefore,
 * this function will increase PWM to catch up once the button is pushed again.
 */
void speed_control() {
  if(millis() >= last_speed_control + SPEED_CONTROL_MILLIS) {
    Serial.print("Target count: ");
    Serial.println((millis() - start_time) / 1000.0 / ANTHEM_DURATION * length_counts); // encoder count that we should be at, based on elapsed time, anthem duration and length of the pole
    Serial.print("Actual count + TOL: ");
    Serial.println(abs(encoder_count) + COUNTS_TOLERANCE);
    
    if((millis() - start_time) / 1000.0 / ANTHEM_DURATION * length_counts > abs(encoder_count) - COUNTS_TOLERANCE) { // calculated target position < actual position - tolerance
      Serial.print("Speed too low - ");
      if(current_pwm <= (255 - SPEED_INCREMENT)) {
        current_pwm += SPEED_INCREMENT; // increase motor pwm to catch up
        Serial.print("Increasing speed");
      }
      Serial.println();
    }
    if((millis() - start_time) / 1000.0 / ANTHEM_DURATION * length_counts < abs(encoder_count) + COUNTS_TOLERANCE) { // calculated target position > actual position + tolerance
      Serial.print("Speed too high - ");
      if((direction_input() == DIRECTION_UP && current_pwm >= MIN_PWM_CONT_UP + SPEED_INCREMENT) or (direction_input() == DIRECTION_DOWN && current_pwm >= MIN_PWM_CONT_DOWN + SPEED_INCREMENT)) {
        current_pwm -= SPEED_INCREMENT; // decrease motor pwm
        Serial.print("Decreasing speed");
      }
      Serial.println();
    }
    last_speed_control = millis();
  }
}

/* This function is called in every loop. Depending on the status of the direction switch and
 * the push button, it makes the motor move or stop and also calls the speed control function.
 */
void normal_loop() {
  if(digitalRead(PIN_BUTTON) == SELECTED) {
    if(direction_input() == DIRECTION_UP) {
      // motor should go upwards
      stuck_check(); // update the is_stuck variable
      if(!is_stuck) {
        if(start_time == 0) start_time = millis(); // record start time for speed control
        speed_control(); // adjust PWM if required
        move_motor(DIRECTION_UP, current_pwm);
      } else {
        // prepare everything for the next run in opposite direction -> reset the encoder count
        start_time = 0;
        encoder_count = 0;
        last_encoder_count = 0;
      }
    } else if (direction_input() == DIRECTION_DOWN) {
      // motor should go down
      stuck_check(); // update the is_stuck variable
      if(!is_stuck) {
        if(start_time == 0) start_time = millis(); // record start time for speed control
        speed_control(); // adjust PWM if required
        move_motor(DIRECTION_DOWN, current_pwm);
      } else {
        // prepare everything for the next run in opposite direction -> reset the encoder count
        start_time = 0;
        encoder_count = 0;
        last_encoder_count = 0;
      }
    } else {
      // no direction -> stop motor
      stop_motor();
    }
  } else {
    // button not pushed -> stop motor
    stop_motor();
  }
}

/* This is the main loop. It updates the encoder_count based on the reflectance sensor signal,
 * detects changes to the input signals and then calls calibration_loop() or normal_loop()
 * depending on whether calibration mode is on or not.
 */
void loop() {
  /* Each sensor reading yields 0 or 1 depending on reflectance. A rolling history of the last
   * sensor readings is saved as bits in reflectance_bits. Each time, the oldest bit gets shifted out
   * to the left and the newest bit is added on the right of reflectance_bits.
   * Then, the sum of the newest REFLECTANCE_HISTORY bits in reflectance_bits is calculated. The sum
   * is the number of recent sensor readings that returned 1. Then we check if the sum is high enough
   * or low enough, depending on the previous state (last_reflectance), to be considered a new valid
   * reading. REFLECTANCE_OUTLIERS bits are allowed to be out of line to account for noisy readings.
   */
  reflectance_bits = reflectance_bits << 1; // shift all bits to the left, freeing the rightmost bit
  //reflectance_bits += digitalRead(PIN_REFLECTANCE); // set the rightmost bit to the current reflectance
  if(analogRead(PIN_REFLECTANCE) > REFLECTANCE_THRESHOLD) reflectance_bits++;
  // calculate the sum:
  for(byte i = 0; i < REFLECTANCE_HISTORY; i++) { // walk through the bits starting from the right up to reflectance_history
    reflectance_count += (reflectance_bits & (1<<i)); // add the i'th bit of reflectance_bits to the sum
  }
  // check if the sum is big enough to detect a change from 0 to 1
  if(last_reflectance == 0 && reflectance_count >= (REFLECTANCE_HISTORY-REFLECTANCE_OUTLIERS)) {
    encoder_count++;
    last_reflectance = 1;
    // encoder changed -> reset boost mode
    is_stuck = false;
    boost_pwm = false;
    boost_count = 0;
  }
  // check if the sum is small enough to detect a change from 1 to 0
  if(last_reflectance == 1 && reflectance_count <= REFLECTANCE_OUTLIERS) {
    encoder_count++;
    last_reflectance = 0;
    // encoder changed -> reset boost mode
    is_stuck = false;
    boost_pwm = false;
    boost_count = 0;
  }
  reflectance_count = 0; // reset count for next round

  detect_input_change();

  if(calibration_mode) {
    // in calibration mode, run the calibration loop instead of the regular one
    calibration_loop();
  } else {
    // "normal loop"
    normal_loop();
  }
  
  debug_log();
}
 
