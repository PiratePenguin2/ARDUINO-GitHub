#include "LedHelper.h"

LedHelper::LedHelper(int num_leds, int min_led, int max_led, int light_skip, double brightness) {
  leds = new CRGB[num_leds];
  numLeds = num_leds;
  minLed = min_led;
  maxLed = max_led;
  lightSkip = light_skip;
  bright = brightness / 100;
  Serial.begin(9600); // Initialize serial communication for debugging
  Serial.println("LED Helper initialized."); // Debug message
  clear();
  delay(1000);
  Serial.println("Adding LEDs..."); // Debug message
  FastLED.addLeds<WS2812, 3, GRB>(leds, num_leds); // Change '3' to your LED pin
  Serial.println("LEDs added."); // Debug message
}

LedHelper::~LedHelper() {
  delete[] leds;
  Serial.println("LED Helper destroyed."); // Debug message
}

void LedHelper::rainbow() {
  Serial.println("Rainbow function called."); // Debug message
  while (true) {
    for (int j = 0; j <= 255; j++) {
      for (int i = minLed; i < maxLed; i += lightSkip) {
        leds[i] = CRGB((255 - j) * bright, j * bright, 0 * bright);
      }
      FastLED.show();
      delay(1);
    }

    for (int j = 0; j <= 255; j++) {
      for (int i = minLed; i < maxLed; i += lightSkip) {
        leds[i] = CRGB(0 * bright, (255 - j) * bright, j * bright);
      }
      FastLED.show();
      delay(1);
    }

    for (int j = 0; j <= 255; j++) {
      for (int i = minLed; i < maxLed; i += lightSkip) {
        leds[i] = CRGB(j * bright, 0 * bright, (255 - j) * bright);
      }
      FastLED.show();
      delay(1);
    }
  }
}

void LedHelper::clear() {
  Serial.println("Clearing LEDs..."); // Debug message
  for (int i = 0; i < numLeds; i++) {
    leds[i] = CRGB(0 * bright, 0 * bright, 0 * bright);
  }
  FastLED.show();
  Serial.println("LEDs cleared."); // Debug message
}
