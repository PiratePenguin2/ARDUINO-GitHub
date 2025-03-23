#include <FastLED.h>

#define LED_PIN     2    // Pin connected to the LED strip
#define START_INDEX 97
#define NUM_LEDS    160   // Adjust to your LED count
#define BRIGHTNESS  100  // Adjust brightness (0-255)

#define BASE_COLOR  CRGB(30, 30, 255)   // Deep blue (default state)
//#define PULSE_COLOR CRGB(255, 8, 0)   // Aggressive red pulse effect
#define PULSE_COLOR CRGB(50, 150, 255)    // Lighter blue (pulse effect)

CRGB leds[NUM_LEDS];

static uint8_t offset = 0;  // Pulse movement offset
static uint8_t pulseGap = 1000; // Distance between pulses (bigger = fewer pulses)
static uint8_t pulseWidth = 12; // Width of each pulse (makes them more noticeable)
static uint8_t fps = 1;
int timer = millis();

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}

// Function for fewer, stronger pulses
void pulseElectricity() {

    for (int i = START_INDEX; i < NUM_LEDS; i++) {
        leds[i] = BASE_COLOR; // Default to deep blue

        // Create fewer, stronger pulses
        if ((i + offset) % pulseGap < pulseWidth) {  
            int strength = sin8((i * 25 + offset) % 255); // More intense pulsing
            leds[i] = blend(BASE_COLOR, PULSE_COLOR, strength); 
        }
    }

    FastLED.show();

    // Move pulses at a noticeable pace
    offset += 7;

    // Randomly update pulse spacing & width occasionally to keep effect organic
    if (random(0, 10) > 8) { // 20% chance per loop
        pulseGap = getWeightedRandom(1000, 3000, 2000);
        //pulseWidth = getWeightedRandom(5, 30, 12);
    }
}

uint16_t getWeightedRandom(uint16_t min, uint16_t max, uint16_t avg) {
    int value;
    do {
        value = random(min, max) * 0.4 + avg * 0.6; // Skew toward avg
    } while (value < min || value > max);
    return value;
}

void waitUntil(int waitDelay) {
  while (millis() < timer + waitDelay) {
    delay(1);
  }
  timer = millis();
}

void loop() {
    pulseElectricity();
    waitUntil(1000 / fps);
}