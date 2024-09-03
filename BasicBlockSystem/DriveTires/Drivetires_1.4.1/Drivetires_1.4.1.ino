#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create an instance of the PCA9685 PWM driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define the channels for the motor control
const int motorPin1 = 0; // PWM channel 0 on PCA9685
const int motorPin2 = 1; // PWM channel 1 on PCA9685

void setup() {
  Serial.begin(9600);
  
  // Initialize the PCA9685
  pwm.begin();
  pwm.setPWMFreq(1600);  // Set frequency to 1.6kHz

  // Set the motor pins to low initially (stopped motor)
  pwm.setPWM(motorPin1, 0, 0);
  pwm.setPWM(motorPin2, 0, 0);
}

void loop() {
  // Move motor forward
  Serial.println("Motor Forward");
  pwm.setPWM(motorPin1, 0, 4095); // Full speed forward
  pwm.setPWM(motorPin2, 0, 0);    // Reverse pin low
  delay(2000);  // Run for 2 seconds

  // Stop motor
  Serial.println("Motor Stop");
  pwm.setPWM(motorPin1, 0, 0);
  pwm.setPWM(motorPin2, 0, 0);
  delay(1000);  // Pause for 1 second

  // Move motor backward
  Serial.println("Motor Backward");
  pwm.setPWM(motorPin1, 0, 0);    // Forward pin low
  pwm.setPWM(motorPin2, 0, 4095); // Full speed reverse
  delay(2000);  // Run for 2 seconds

  // Stop motor
  Serial.println("Motor Stop");
  pwm.setPWM(motorPin1, 0, 0);
  pwm.setPWM(motorPin2, 0, 0);
  delay(1000);  // Pause for 1 second
}
