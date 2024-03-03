#pragma once
#include "LED.h"
#include "ESC.h"

class Launch {
public:
    Launch();
    void startSequence();

private:
    void printState(const char* state, int duration);
    void setState(const char* state, int duration);

    Led led;
    Esc esc;
    const int blinkRate1 = 750;
    const int blinkRate2 = 250;
    const int rapidBlinkRate = 50;
};
