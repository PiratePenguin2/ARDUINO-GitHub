// EStopButton.h
#pragma once

#include "Timer.h"
#include <ArrayList.h>

class EStopButton { //extends Button
public:
  enum ButtonState {
    PRESSED,
    OPEN,
    NEITHER,
    BOTH
  };
  enum ButtonMode {
    LAMP_TEST_G,
    LAMP_TEST,
    TRIPPED,
    RESET_REQUEST,
    OPERATING,
    DISABLED,
    OFF
  };
    
  
  EStopButton();
  void createEStopButton();

  void update();
  
    void updateButtonState();
  
    void updateLocalStates();
      void addMode(ButtonMode mode);
      void removeMode(ButtonMode mode);
  
   void updateLampState();
  


private:
  //String name;
  int pinNO;
  int pinNC;
  int pinLED;

  Timer timeBtnNeither;

  ButtonState buttonState;
  ButtonState prevButtonState;
  ArrayList<ButtonMode> localModes;
  
};
