#include "LedHelper.h"

#define LED_PIN     3
#define NUM_LEDS    150

LedHelper ledHelper(NUM_LEDS, 0, NUM_LEDS - 1, 1, 10);

void setup() {
  // No setup required
}

void loop() {
  ledHelper.rainbow(); // Call whichever function you need to run
}
