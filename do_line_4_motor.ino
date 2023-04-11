// Define the pin numbers for the IR sensors and motor driver
#define LEFT_SENSOR A0
#define RIGHT_SENSOR A1
#define MIDDLE_LEFT_SENSOR A2
#define MIDDLE_RIGHT_SENSOR A3

#define MOTOR_LEFT_FORWARD 10
#define MOTOR_LEFT_BACKWARD 11
#define MOTOR_RIGHT_FORWARD 6
#define MOTOR_RIGHT_BACKWARD 5
#define MOTOR_LEFT_FRONT 9
#define MOTOR_LEFT_BACK 3
#define MOTOR_RIGHT_FRONT 8
#define MOTOR_RIGHT_BACK 4

// Define the threshold values for the IR sensors
#define THRESHOLD 500

void setup() {
  // Set the motor pins as outputs
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_FRONT, OUTPUT);
  pinMode(MOTOR_LEFT_BACK, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_FRONT, OUTPUT);
  pinMode(MOTOR_RIGHT_BACK, OUTPUT);
}

void loop() {
  // Read the sensor values
  int left = analogRead(LEFT_SENSOR);
  int right = analogRead(RIGHT_SENSOR);
  int middle_left = analogRead(MIDDLE_LEFT_SENSOR);
  int middle_right = analogRead(MIDDLE_RIGHT_SENSOR);

  // Determine the motor speeds based on the sensor values
  int left_speed_front = 0;
  int left_speed_back = 0;
  int right_speed_front = 0;
  int right_speed_back = 0;

  if (left < THRESHOLD && right < THRESHOLD && middle_left < THRESHOLD && middle_right < THRESHOLD) {
    // Stop if all sensors are reading black
    left_speed_front = 0;
    left_speed_back = 0;
    right_speed_front = 0;
    right_speed_back = 0;
  } else if (middle_left < THRESHOLD && middle_right < THRESHOLD) {
    // Move forward if the middle sensors are reading black
    left_speed_front = 255;
    left_speed_back = 0;
    right_speed_front = 255;
    right_speed_back = 0;
  } else if (middle_left >= THRESHOLD && middle_right < THRESHOLD) {
    // Turn left if the left middle sensor is reading white
    left_speed_front = 0;
    left_speed_back = 255;
    right_speed_front = 255;
    right_speed_back = 0;
  } else if (middle_left < THRESHOLD && middle_right >= THRESHOLD) {
    // Turn right if the right middle sensor is reading white
    left_speed_front = 255;
    left_speed_back = 0;
    right_speed_front = 0;
    right_speed_back = 255;
  }

  // Set the motor speeds
  analogWrite(MOTOR_LEFT_FORWARD, left_speed_front);
  analogWrite(MOTOR_LEFT_BACKWARD, left_speed_back);
  analogWrite(MOTOR_RIGHT_FORWARD, right_speed_front);
  analogWrite(MOTOR_RIGHT_BACKWARD, right_speed_back);
}
