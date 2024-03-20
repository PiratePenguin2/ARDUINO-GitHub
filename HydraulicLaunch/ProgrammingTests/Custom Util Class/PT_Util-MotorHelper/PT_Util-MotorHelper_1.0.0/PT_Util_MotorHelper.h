#include <Arduino_FreeRTOS.h>
#include <Servo.h>
#include <LinkedList.h>

struct Move {
    int targetPosition;
    int speed;
};
/*
struct StepperPins {
    int pinA;
    int pinB;
    int pinC;
    int pinD;
};

struct DCDriverPins {
    int pinA;
    int pinB;
    int pinC;
};*/

class Motor {
public:
    virtual void move(int targetPosition, int speed = 1, bool schedule = false) = 0;
    virtual bool isMoving() const = 0;
    //virtual int getPosition() const = 0;
    virtual void clearQueue() = 0;
    virtual void clearQueue(int index) = 0;
};

class ServoPos : public Motor {
private:
    Servo servoMotor;
    int servoPin;
    TaskHandle_t taskHandle;
    bool moving;
    int targetPosition;
    int speed;
    bool scheduleNextMove;
    LinkedList<Move> moveQueue;

public:
    ServoPos(int pin) : servoPin(pin), taskHandle(NULL), moving(false), targetPosition(0), speed(1), scheduleNextMove(false) {}

    void move(int newTargetPosition, int newSpeed = 1, bool schedule = false) override {
        if (!scheduleNextMove || !isMoving()) {
            targetPosition = newTargetPosition;
            speed = newSpeed;
            scheduleNextMove = schedule;
            if (!scheduleNextMove || !isMoving()) {
                createMoveTask();
            }
        } else {
            Move move;
            move.targetPosition = newTargetPosition;
            move.speed = newSpeed;
            moveQueue.add(move);
        }
    }

    bool isMoving() const override {
        return (taskHandle != NULL && uxTaskGetNumberOfTasks() > 0);
    }

    /*int getPosition() const override {
        return servoMotor.read();
    }*/

    void clearQueue() override {
        moveQueue.clear();
    }

    void clearQueue(int index) override {
        if (index >= 0 && index < moveQueue.size()) {
            moveQueue.remove(index);
        }
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
        const int delayTime = 15;

        Servo servoMotor;
        servoMotor.attach(9);

        int currentPosition = servoMotor.read();
        int direction = (targetPosition - currentPosition > 0) ? 1 : -1;
        int actualSpeed = min(abs(targetPosition - currentPosition), maxSpeed);

        for (int pos = currentPosition; pos != targetPosition; pos += direction * actualSpeed) {
            servoMotor.write(pos);
            vTaskDelay(pdMS_TO_TICKS(delayTime));
        }

        servoMotor.detach();
        vTaskDelete(NULL);
    }
};
/*
class DCBrushed : public Motor {
private:
    DCBrushed dcMotor;
    int motorPin;
    TaskHandle_t taskHandle;
    bool moving;
    float speed;
}

class DCBrushedDriver : public DCBrushed {
private:
    override 
    LinkedList<DCDriverPins> motorPins; // overide motorPin with motorpins list
}

class DCBrushless : public Motor {
private:
    DCBrushless dcBrushlessMotor;
    int escPin;
    TaskHandle_t taskHandle;
    bool moving;
    float speed;
}

class Stepper : public Motor {
private:
    Stepper stepperMotor;
    LinkedList<StepperPins> stepperPins;
    TaskHandle_t taskHandle;
    bool moving;
    float speed;
}*/
// Implement other motor classes (DCBrushed, DCBrushless, Stepper) similarly
