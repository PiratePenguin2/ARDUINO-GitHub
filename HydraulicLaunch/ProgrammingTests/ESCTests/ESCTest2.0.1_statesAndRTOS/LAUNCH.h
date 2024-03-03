// LAUNCH.h
#ifndef LAUNCH_H
#define LAUNCH_H

#include <Arduino.h>
#include <String.h>
#include "LED.h"

class LAUNCH {
public:
    LAUNCH();

    void initialize();
    void startLaunchSequence();
    void update();

private:
    void setState(String newState, int duration = -1);

    String state;
    unsigned long stateStartTime;
    int stateDuration;
    int escSpeed;
    int ledPin;

    LED led;
};

#endif // LAUNCH_H
