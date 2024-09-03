#ifndef MotorServoControl_h
#define MotorServoControl_h

#include <Adafruit_PWMServoDriver.h>

class MotorServoControl {
public:
  MotorServoControl(Adafruit_PWMServoDriver& pwmDriver, uint8_t motor1Channel, uint8_t motor2Channel, uint8_t servoChannel);

  void setMotorSpeed(int motor1Speed, int motor2Speed); // Speed range: -100 to 100
  void setServoAngle(int angle); // Angle range: 0 to 180
  
private:
  Adafruit_PWMServoDriver& pwm;
  uint8_t motor1PwmChannel;
  uint8_t motor2PwmChannel;
  uint8_t servoPwmChannel;

  static const int motorMinPWM = 0;
  static const int motorMaxPWM = 4095;
  static const int servoMinPulse = 1000;
  static const int servoMaxPulse = 2000;

  void updateMotorPWM(uint8_t channel, int speed);
};

#endif
