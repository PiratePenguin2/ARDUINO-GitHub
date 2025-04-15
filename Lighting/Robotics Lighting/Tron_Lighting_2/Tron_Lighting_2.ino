#include <FastLED.h>

#define LED_PIN     2    // Pin connected to the LED strip
#define START_INDEX 0
#define NUM_LEDS    86   // Adjust to your LED count
#define BRIGHTNESS  255  // Adjust brightness (0-255)

#define BASE_COLOR  CRGB(0, 0, 255)   // Deep blue (default state)
//#define PULSE_COLOR CRGB(255, 8, 0)   // Aggressive red pulse effect
#define PULSE_COLOR CRGB(50, 150, 255)    // Lighter blue (pulse effect)

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}

// Function for fewer, stronger pulses
void pulseElectricity() {
    static uint8_t offset = 0;  // Pulse movement offset
    static uint8_t pulseGap = 50; // Distance between pulses (bigger = fewer pulses)
    static uint8_t pulseWidth = 12; // Width of each pulse (makes them more noticeable)

    for (int i = START_INDEX; i < NUM_LEDS; i++) {
        leds[i] = BASE_COLOR; // Default to deep blue

        // Create fewer, stronger pulses
        if ((i + offset) % pulseGap < pulseWidth) {  
            int strength = sin8((i * 25 + offset) % 255); // More intense pulsing
            leds[i] = blend(BASE_COLOR, PULSE_COLOR, strength); 
        }
    }

    FastLED.show();
    delay(20);  // Speed of movement

    // Move pulses at a noticeable pace
    offset += 7;
}

void loop() {
    pulseElectricity();
}