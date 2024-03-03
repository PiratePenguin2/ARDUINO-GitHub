// LED.h
#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
public:
    LED();  // Add this line
    LED(int pin);

    void initialize();
    void turnOn();
    void turnOff();
    void blink(int onDuration, int offDuration);

private:
    int pin;
};

#endif // LED_H
