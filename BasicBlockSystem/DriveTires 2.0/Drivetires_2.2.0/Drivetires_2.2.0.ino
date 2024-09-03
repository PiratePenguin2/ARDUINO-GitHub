#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PCA9685 object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Custom Servo Motor Class
class PTservo {
  // Define the channel for the servo (0-15) 320 mid, +-225
  #define SERVOMIN  95 // This is the 'minimum' pulse length count (out of 4096)
  #define SERVOMAX  545 // This is the 'maximum' pulse length count (out of 4096)

public:
  PTservo(Adafruit_PWMServoDriver& driver, uint8_t channel) : pwmDriver(driver), pwmChannel(channel) {}

  void write(int angle) {
    // Constrain angle to range 0 to 180
    angle = constrain(angle, 0, 180);

    int pwmValue = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    
    pwmDriver.setPWM(pwmChannel, 0, pwmValue);
  }
  
private:
  Adafruit_PWMServoDriver& pwmDriver;
  uint8_t pwmChannel;
};

// Custom DC Motor Class
class PTdcmotor {
public:
  PTdcmotor(Adafruit_PWMServoDriver& driver, uint8_t channel, uint8_t in1, uint8_t in2) :
      pwmDriver(driver), pwmChannel(channel), pin1(in1), pin2(in2) {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void write(int speed) {
    // Constrain speed to range -100 to 100
    speed = constrain(speed, -100, 100);

    // Set corresponding IN pins
    digitalWrite(pin1, speed > 0 ? HIGH : LOW);
    digitalWrite(pin2, speed < 0 ? HIGH : LOW);
    
    // Map pulse width to PCA9685 PWM range (0-4095)
    int pwmValue = map(abs(speed), 0, 100, 0, 4095);

    pwmDriver.setPWM(pwmChannel, 0, pwmValue);
  }
  
private:
  Adafruit_PWMServoDriver& pwmDriver;
  uint8_t pwmChannel;
  uint8_t pin1;
  uint8_t pin2;
};

// PCA9685 PWM channels
const int motorA = 0;  // Channel for Motor A
const int motorB = 1;  // Channel for Motor B
const int svoA = 8;   // Channel for Servo A

//PCA9685Servo myServo(pwm, servoPwmChannel); // Create servo object
  PTdcmotor tireA = PTdcmotor(pwm, motorA, 2, 3);
  PTdcmotor tireB = PTdcmotor(pwm, motorB, 4, 5);
  PTservo servoA  = PTservo(pwm, svoA);

void setup() {
  // Initialize PCA9685
  pwm.begin();
  pwm.setPWMFreq(50);

  // Start with motors stopped
  tireA.write(0);
  tireB.write(0);
  servoA.write(90); // Set servo to initial position (90 degrees)
}

void loop() {

  tireA.write(100);
  tireB.write(100);
  servoA.write(180);

  delay(2000);  // Run forward for 2 seconds

  tireA.write(0);
  tireB.write(0);
  servoA.write(90);

  delay(1000);  // Stop for 1 second

  tireA.write(-100);
  tireB.write(-100);
  servoA.write(0);

  delay(2000);  // Run backward for 2 seconds

  tireA.write(0);
  tireB.write(0);
  servoA.write(90);

  delay(1000);  // Stop for 1 second
}
