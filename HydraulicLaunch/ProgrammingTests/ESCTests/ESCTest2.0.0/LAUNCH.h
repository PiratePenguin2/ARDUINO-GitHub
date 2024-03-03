// LAUNCH.h
#ifndef LAUNCH_h
#define LAUNCH_h

#include <Arduino.h>
#include "ESC.h"
#include "LED.h"
#include "BUTTON.h"

enum LaunchState {
  IDLE,
  LAUNCHREADY,
  PRESTAGING,
  PRESTAGED,
  STAGING,
  STAGED,
  LAUNCHING,
  DECELERATING,
  TRAINASCEND,
  STARTRESET,
  RESET,
  INTERVAL
};

class Launch {
private:
  ESC esc;
  LED led;
  Button button;
  LaunchState currentState;

  // Define the duration for each state in milliseconds
  const int stateDurations[12] = {0, 0, 0, 0, 100, 0, 1000, 0, 150, 2000, 0, 1000};

  // Define state names for debugging
  const char *stateNames[12] = {"IDLE", "LAUNCHREADY", "PRESTAGING", "PRESTAGED", "STAGING", "STAGED",
                                "LAUNCHING", "DECELERATING", "TRAINASCEND", "STARTRESET", "RESET", "INTERVAL"};

public:
  Launch(int escPin, int ledPin, int buttonPin);
  void initialize();
  void updateState();
  void startLaunch();
};

#endif
