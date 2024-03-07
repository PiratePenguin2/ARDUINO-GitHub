#pragma once
#include <Arduino.h>

class PT_Util {
public:
  class Timer {
  public:
    Timer();
    Timer(int mSec);
    void setTimer(int mSec);
    unsigned long getStartTime();
    unsigned long getEndTime();
    unsigned long getElapsedTime();
    unsigned long getTimeLeft();
    bool timerFinished();
  private:
    int duration;
    unsigned long startTime;
  };

  class Stopwatch {
  public:
    Stopwatch();
    void restartStopwatch();
    unsigned long getTimeElapsed();
  private:
    unsigned long startTime;
  };

  class Button {
    #define PUSH 0
    #define TAP 1
    #define LATCH 2
  public:
    /*enum ButtonMode {
      PUSH,
      TAP,
      LATCH
    };*/
    Button(int pin);
    Button(int pin, int mode);
    bool isPressed();
    bool isEnabled();
  private:
    int buttonPin;
    bool enabled;
    int buttonLatchDelay = 500;
    int mode;
    PT_Util::Timer buttonDelay; // Declare buttonLatch as a member variable
  };

  class Led {
    #define ON 0
    #define OFF 1
    #define FLIP 2
    #define BLINK 3
  public:
    Led(int pin);
    void update();
    void setState(int state);
    void setState(int state, int onTime);
    void setState(int state, int onTime, int offTime);
    void turnOn();
    void turnOff();
    bool getState(); // New function
  private:
    bool isOn;
    int ledPin;
    int onTime;
    int offTime;
    int state;
    PT_Util::Timer blinkTimer; // Declare blinkTimer as a member variable
  };

  class HallEffectSensor {
  public:
    HallEffectSensor(int pin);
    int readSensorValue();
  private:
    int sensorPin;
  };
};
