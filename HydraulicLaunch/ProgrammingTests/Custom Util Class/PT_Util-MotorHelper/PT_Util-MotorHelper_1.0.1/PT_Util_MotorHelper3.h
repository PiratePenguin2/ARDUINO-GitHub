#include <Arduino_FreeRTOS.h>
#include <Servo.h>

class Motor {
//public:
    
};

class ServoPos : public Motor {
private:
    Servo servoMotor;
    int servoPin;

public:
    ServoPos(int pin) : servoPin(pin) {
      servoMotor.attach(servoPin);
    }

    void move(int targetPosition) {
      servoMotor.write(targetPosition);
    }
};
