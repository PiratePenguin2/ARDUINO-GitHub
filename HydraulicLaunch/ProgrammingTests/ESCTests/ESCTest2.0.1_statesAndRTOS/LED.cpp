// LED.cpp
#include <Arduino.h>

class LED {
public:
    LED(int pin) : pin(pin) {}

    void initialize() {
        pinMode(pin, OUTPUT);
    }

    void turnOn() {
        digitalWrite(pin, HIGH);
    }

    void turnOff() {
        digitalWrite(pin, LOW);
    }

    void blink(int onTime, int offTime) {
        turnOn();
        delay(onTime);
        turnOff();
        delay(offTime);
    }

private:
    int pin;
};
