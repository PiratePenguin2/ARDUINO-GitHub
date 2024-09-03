#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PCA9685 object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Custom Servo class
class PCA9685Servo {
public:
  PCA9685Servo(Adafruit_PWMServoDriver& driver, uint8_t channel) : pwmDriver(driver), pwmChannel(channel) {}

  void attach() {
    pwmDriver.setPWMFreq(60); // Set frequency to 60 Hz for servo control
  }

  void write(int angle) {
    angle = constrain(angle, 0, 180); // Constrain angle to range 0-180
    int pulseWidth = map(angle, 0, 180, servoMinPulse, servoMaxPulse); // Convert angle to pulse width
    int pwmValue = map(pulseWidth, servoMinPulse, servoMaxPulse, 0, 4095); // Map pulse width to PCA9685 range
    pwmDriver.setPWM(pwmChannel, 0, pwmValue);
    
    // Debugging: Print angle and PWM value
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" - PWM Value: ");
    Serial.println(pwmValue);
  }

private:
  Adafruit_PWMServoDriver& pwmDriver;
  uint8_t pwmChannel;
  static const int servoMinPulse = 1000; // Minimum pulse width for servo (in microseconds)
  static const int servoMaxPulse = 2000; // Maximum pulse width for servo (in microseconds)
};

// PCA9685 PWM channels
const int servoPwmChannel = 8; // Channel for Servo

PCA9685Servo myServo(pwm, servoPwmChannel); // Create servo object

// Servo sweeping parameters
int servoAngle = 0;       // Current angle of the servo
int servoSweepSpeed = 1;  // Speed of the servo sweep (angle per loop iteration)
bool sweepingRight = true; // Direction of the sweep

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  
  // Initialize PCA9685
  pwm.begin();
  pwm.setPWMFreq(60);  // Set frequency to 60 Hz for servo control
  
  // Initialize Servo
  myServo.attach();
  
  // Set the initial position of the servo
  myServo.write(servoAngle);
}

void loop() {
  // Sweep servo left and right
  if (sweepingRight) {
    servoAngle += servoSweepSpeed;  // Increase angle
    if (servoAngle >= 180) {
      servoAngle = 180;  // Limit to 180 degrees
      sweepingRight = false; // Change direction
    }
  } else {
    servoAngle -= servoSweepSpeed;  // Decrease angle
    if (servoAngle <= 0) {
      servoAngle = 0;  // Limit to 0 degrees
      sweepingRight = true; // Change direction
    }
  }
  
  // Update servo position
  myServo.write(servoAngle);
  delay(15); // Wait for the servo to reach the position
}
