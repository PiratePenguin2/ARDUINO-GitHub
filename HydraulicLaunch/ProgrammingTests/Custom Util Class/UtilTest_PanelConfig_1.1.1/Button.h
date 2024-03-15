// Button.h
#pragma once

#include "Timer.h"
#include <ArrayList.h>


class Button {
public:
  enum ButtonState {
    PRESSED,
    OPEN,
    NEITHER,
    BOTH
  };

  Button();
  
  void update();
  
    void updateButtonState();
  
    void updateLocalStates();
      void addMode(ButtonMode mode);
      void removeMode(ButtonMode mode);
  
    void updateLampState();


  //String title;
  int pinNO;
  int pinNC;
  int pinLED;

  Timer timeBtnNeither;

  ButtonState buttonState;
  ButtonState prevButtonState;
  ArrayList<ButtonMode> localModes;
};



class EStopButton extends Button {
public:
  @override
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
  


private:
  
};
