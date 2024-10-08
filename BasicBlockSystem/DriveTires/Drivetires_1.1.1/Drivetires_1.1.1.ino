#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PCA9685 object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Custom Servo class
class PCA9685Servo {
public:
  PCA9685Servo(Adafruit_PWMServoDriver& driver, uint8_t channel) : pwmDriver(driver), pwmChannel(channel) {}

  void attach() {
    // Initialize PWM settings
    pwmDriver.setPWMFreq(60); // Set frequency to 60 Hz for servo control
  }

  void write(int angle) {
    // Constrain angle to range 0-180
    angle = constrain(angle, 0, 180);
    
    // Convert angle to pulse width (1000-2000 microseconds)
    int pulseWidth = map(angle, 0, 180, servoMinPulse, servoMaxPulse);
    
    // Map pulse width to PCA9685 PWM range (0-4095)
    int pwmValue = map(pulseWidth, servoMinPulse, servoMaxPulse, 0, 4095);
    
    pwmDriver.setPWM(pwmChannel, 0, pwmValue);
  }

private:
  Adafruit_PWMServoDriver& pwmDriver;
  uint8_t pwmChannel;
  static const int servoMinPulse = 1000; // Minimum pulse width for servo (in microseconds)
  static const int servoMaxPulse = 2000; // Maximum pulse width for servo (in microseconds)
};

// Pin definitions for motors
const int motor1In1Pin = 2;  // IN1 on H-Bridge
const int motor1In2Pin = 3;  // IN2 on H-Bridge
const int motor2In3Pin = 4;  // IN3 on H-Bridge
const int motor2In4Pin = 5;  // IN4 on H-Bridge

// PCA9685 PWM channels
const int motor1PwmChannel = 0;  // Channel for Motor 1
const int motor2PwmChannel = 1;  // Channel for Motor 2
const int servoPwmChannel = 8;   // Channel for Servo

// Motor speed (0-4095 for PCA9685)
int motorSpeed1 = 4095; // Set Motor 1 to full speed
int motorSpeed2 = 4095; // Set Motor 2 to full speed

PCA9685Servo myServo(pwm, servoPwmChannel); // Create servo object

void setup() {
  // Initialize PCA9685
  pwm.begin();
  pwm.setPWMFreq(1600);  // Set frequency to 1.6 kHz for motor control
  
  // Initialize Servo
  myServo.attach();
  
  // Set up the pin modes for Motor 1
  pinMode(motor1In1Pin, OUTPUT);
  pinMode(motor1In2Pin, OUTPUT);

  // Set up the pin modes for Motor 2
  pinMode(motor2In3Pin, OUTPUT);
  pinMode(motor2In4Pin, OUTPUT);

  // Start with motors stopped
  digitalWrite(motor1In1Pin, LOW);
  digitalWrite(motor1In2Pin, LOW);
  pwm.setPWM(motor1PwmChannel, 0, 0); // Motor 1 stop

  digitalWrite(motor2In3Pin, LOW);
  digitalWrite(motor2In4Pin, LOW);
  pwm.setPWM(motor2PwmChannel, 0, 0); // Motor 2 stop

  // Set the initial position of the servo
  myServo.write(90); // Set servo to initial position (90 degrees)
}

void loop() {
  // Motor 1 Forward
  digitalWrite(motor1In1Pin, HIGH);
  digitalWrite(motor1In2Pin, LOW);
  pwm.setPWM(motor1PwmChannel, 0, motorSpeed1);  // Set Motor 1 speed

  // Motor 2 Forward
  digitalWrite(motor2In3Pin, HIGH);
  digitalWrite(motor2In4Pin, LOW);
  pwm.setPWM(motor2PwmChannel, 0, motorSpeed2);  // Set Motor 2 speed

  delay(2000);  // Run forward for 2 seconds

  // Stop both motors
  digitalWrite(motor1In1Pin, LOW);
  digitalWrite(motor1In2Pin, LOW);
  pwm.setPWM(motor1PwmChannel, 0, 0);  // Motor 1 stop

  digitalWrite(motor2In3Pin, LOW);
  digitalWrite(motor2In4Pin, LOW);
  pwm.setPWM(motor2PwmChannel, 0, 0);  // Motor 2 stop

  delay(1000);  // Stop for 1 second

  // Motor 1 Backward
  digitalWrite(motor1In1Pin, LOW);
  digitalWrite(motor1In2Pin, HIGH);
  pwm.setPWM(motor1PwmChannel, 0, motorSpeed1);  // Set Motor 1 speed

  // Motor 2 Backward
  digitalWrite(motor2In3Pin, LOW);
  digitalWrite(motor2In4Pin, HIGH);
  pwm.setPWM(motor2PwmChannel, 0, motorSpeed2);  // Set Motor 2 speed

  delay(2000);  // Run backward for 2 seconds

  // Stop both motors
  digitalWrite(motor1In1Pin, LOW);
  digitalWrite(motor1In2Pin, LOW);
  pwm.setPWM(motor1PwmChannel, 0, 0);  // Motor 1 stop

  digitalWrite(motor2In3Pin, LOW);
  digitalWrite(motor2In4Pin, LOW);
  pwm.setPWM(motor2PwmChannel, 0, 0);  // Motor 2 stop

  delay(1000);  // Stop for 1 second

  // Move the servo to a new angle
  static int servoAngle = 90;
  servoAngle = (servoAngle + 45) % 180; // Change the angle (mod 180 to loop)
  myServo.write(servoAngle); // Set new position of the servo
  delay(1000); // Wait for the servo to reach the position
}
