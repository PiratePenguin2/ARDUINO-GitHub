#include <Arduino_FreeRTOS.h>
#include <Servo.h>

class Motor {
public:
    virtual void move(int targetPosition, int speed = 1) = 0;
};

class ServoPos : public Motor {
private:
    Servo servoMotor;
    int servoPin;
    TaskHandle_t taskHandle;
    bool moving;
    int targetPosition;
    int speed;

public:
    ServoPos(int pin) : servoPin(pin), taskHandle(NULL), moving(false), targetPosition(0), speed(1) {
      pinMode(LED_BUILTIN, OUTPUT);
    }

    void move(int newTargetPosition, int newSpeed = 1) override {
      targetPosition = newTargetPosition;
      speed = newSpeed;
      createMoveTask();
    }

private:
    void createMoveTask() {
        int *params = new int[2]{targetPosition, speed};
        if (xTaskCreate(moveTask, "ServoMoveTask", 128, params, 1, &taskHandle) != pdPASS) {
            Serial.println("Failed to create servo move task!");
            delete[] params;
        }
    }

    static void moveTask(void *pvParameters) {
        int *params = (int *)pvParameters;
        int targetPosition = params[0];
        int speed = params[1];
        const int maxSpeed = 5;
        //const int delayTime = 15;

        Servo servoMotor;
        servoMotor.attach(10); // Change pin number if needed

        int currentPosition = servoMotor.read();

        int direction = (targetPosition - currentPosition > 0) ? 1 : -1;

        //while (currentPosition != targetPosition) {
            currentPosition = servoMotor.read();
            servoMotor.write(currentPosition);
            vTaskDelay(pdMS_TO_TICKS(delayTime));
            currentPosition = servoMotor.read();
        //}

        servoMotor.detach();
        vTaskDelete(NULL);
    }
};
