#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

// I2C address of PCA9685
#define PCA9685_ADDR 0x40

// PCA9685 Channels
#define MOTOR_A_PWM 4  // Channel 4 for Motor A PWM (speed control)
#define MOTOR_B_PWM 5  // Channel 5 for Motor B PWM (speed control)
#define SERVO_A 8      // Channel 8 for Servo A
#define SERVO_B 9      // Channel 9 for Servo B

// H-Bridge IN pins connected to Arduino Nano
#define MOTOR_A_IN1 2  // IN1 for Motor A
#define MOTOR_A_IN2 3  // IN2 for Motor A
#define MOTOR_B_IN1 4  // IN1 for Motor B
#define MOTOR_B_IN2 5  // IN2 for Motor B

// Create PWM object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDR);

Servo myServoA; // Create servo object for Servo A
Servo myServoB; // Create servo object for Servo B

void setup() {
  // Initialize I2C communication and PCA9685
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(60);  // Set frequency to 60 Hz for servos
  
  // Attach servos to their channels on the PCA9685
  myServoA.attach(SERVO_A);
  myServoB.attach(SERVO_B);

  // Set motor control pins as outputs
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);

  // Set initial motor states (stop)
  stopMotors();
}

void loop() {
  // Example: Move Servo A to 90 degrees and Servo B to 180 degrees
  myServoA.write(90);
  myServoB.write(180);
  delay(1000);

  // Example: Move Servo A to 0 degrees and Servo B to 90 degrees
  myServoA.write(0);
  myServoB.write(90);
  delay(1000);

  // Example: Drive motors forward at 75% speed
  driveMotor(MOTOR_A_IN1, MOTOR_A_IN2, MOTOR_A_PWM, 3072); // 3072 is 75% of 4096 (12-bit PWM)
  driveMotor(MOTOR_B_IN1, MOTOR_B_IN2, MOTOR_B_PWM, 3072);
  delay(2000);

  // Stop motors
  stopMotors();
  delay(1000);
}

// Function to drive a motor
void driveMotor(uint8_t in1, uint8_t in2, uint8_t pwmChannel, uint16_t speed) {
  // Set direction to forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  // Set speed
  pwm.setPWM(pwmChannel, 0, speed);
}

// Function to stop motors
void stopMotors() {
  // Set all motor direction pins low
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, LOW);

  // Set motor speed to 0
  pwm.setPWM(MOTOR_A_PWM, 0, 0);
  pwm.setPWM(MOTOR_B_PWM, 0, 0);
}
