// Led.h
#ifndef LED_H
#define LED_H

#include "Timer.h"

class Led {
public:
    enum LedMode {
        NO,
        NORMALLY_OPEN,
        NC,
        NORMALLY_CLOSED
    };

    enum LedState {
        ON,
        OFF,
        FLIP,
        BLINK
    };

    Led(int pin);
    Led(int pin, LedState ledS);
    Led(int pin, LedState ledS, LedMode ledM);
    void update();
    
    LedMode getLedMode() const;
    void setLedMode(LedMode mode);

    int getLedState();
    void setLedState(LedState ledS);
    void setLedState(LedState ledS, int newOnTime);
    void setLedState(LedState ledS, int newOnTime, int newOffTime);
    void turnOn();
    void turnOff();
    
    bool getLampState();

private:
    bool isOn;
    int ledPin;
    int onTime;
    int offTime;
    Timer blinkTimer;
    LedMode ledMode;  // Added LedMode here
    LedState ledState;
    LedState defaultLedState;
};

#endif // LED_H
