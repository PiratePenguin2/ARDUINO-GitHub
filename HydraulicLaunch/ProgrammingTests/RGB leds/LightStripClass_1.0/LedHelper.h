#ifndef LEDHELPER_H
#define LEDHELPER_H

#include <FastLED.h>

class LedHelper {
  private:
    CRGB *leds;
    int numLeds;
    int minLed;
    int maxLed;
    int lightSkip;
    double bright;

  public:
    LedHelper(int num_leds, int min_led, int max_led, int light_skip, double brightness);
    ~LedHelper();
    void rainbow();
    void clear();
};

#endif
