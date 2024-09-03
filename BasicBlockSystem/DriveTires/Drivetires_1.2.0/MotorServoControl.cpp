#include "MotorServoControl.h"

MotorServoControl::MotorServoControl(Adafruit_PWMServoDriver& pwmDriver, uint8_t motor1Channel, uint8_t motor2Channel, uint8_t servoChannel)
  : pwm(pwmDriver), motor1PwmChannel(motor1Channel), motor2PwmChannel(motor2Channel), servoPwmChannel(servoChannel) {
  pwm.begin();
  pwm.setPWMFreq(1600); // Set frequency to 1.6 kHz
}

void MotorServoControl::setMotorSpeed(int motor1Speed, int motor2Speed) {
  motor1Speed = constrain(motor1Speed, -100, 100);
  motor2Speed = constrain(motor2Speed, -100, 100);

  int motor1PWM = map(abs(motor1Speed), 0, 100, motorMinPWM, motorMaxPWM);
  int motor2PWM = map(abs(motor2Speed), 0, 100, motorMinPWM, motorMaxPWM);

  Serial.print("Motor 1 Speed: ");
  Serial.print(motor1Speed);
  Serial.print(" => PWM Value: ");
  Serial.println(motor1PWM);

  Serial.print("Motor 2 Speed: ");
  Serial.print(motor2Speed);
  Serial.print(" => PWM Value: ");
  Serial.println(motor2PWM);

  pwm.setPWM(motor1PwmChannel, 0, motor1PWM);
  pwm.setPWM(motor2PwmChannel, 0, motor2PWM);
}

void MotorServoControl::setServoAngle(int angle) {
  angle = constrain(angle, 0, 180);
  int pulseWidth = map(angle, 0, 180, servoMinPulse, servoMaxPulse);
  int pwmValue = map(pulseWidth, servoMinPulse, servoMaxPulse, 0, 4095);

  Serial.print("Servo Angle: ");
  Serial.print(angle);
  Serial.print(" => PWM Value: ");
  Serial.println(pwmValue);

  pwm.setPWM(servoPwmChannel, 0, pwmValue);
}
