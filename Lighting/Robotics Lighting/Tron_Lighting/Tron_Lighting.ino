#include <FastLED.h>

#define LED_PIN        2     // Data pin for LED strip
#define START_LED      2
#define NUM_LEDS       86    // Number of LEDs
#define WAVE_SPEED     3     // Speed of the moving wave
#define SPEED          20    // Overall wave update speed (lower = faster)
#define BRIGHTNESS_MASTER 255

#define LIT_WAVE_SIZE  20
#define DULL_WAVE_SIZE 100
#define LIT_BRIGHTNESS 255
#define DULL_BRIGHTNESS 40
#define COLOR          CRGB(0, 0, 255)  // Base wave color

#define PULSE_LENGTH   3       // Length of the pulse in pixels
#define PULSE_COLOR    CRGB::White
#define PULSE_INTERVAL 3000    // Time between new pulses (ms)
#define PULSE_DURATION 1000    // Time for a pulse to travel full strip (ms)

CRGB leds[NUM_LEDS];

unsigned long lastPulseStart = 0;
bool pulseActive = false;

void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();
    FastLED.setBrightness(BRIGHTNESS_MASTER);
}

void loop() {
    static uint16_t waveOffset = 0;
    unsigned long now = millis();

    // Trigger a new pulse if enough time has passed
    if (!pulseActive && (now - lastPulseStart >= PULSE_INTERVAL)) {
        lastPulseStart = now;
        pulseActive = true;
    }

    // Draw base wave effect
    for (int i = START_LED; i < NUM_LEDS; i++) {
        uint8_t wave = sin8((i * 255 / (LIT_WAVE_SIZE + DULL_WAVE_SIZE)) + waveOffset);
        uint8_t brightness = map(wave, 0, 255, DULL_BRIGHTNESS, LIT_BRIGHTNESS);
        leds[i] = COLOR;
        leds[i].nscale8(brightness);
    }

    // Draw the white pulse based on time
    // Draw the white pulse based on time
    if (pulseActive) {
        float elapsed = now - lastPulseStart;
        if (elapsed >= PULSE_DURATION) {
            pulseActive = false;
        } else {
            float progress = elapsed / (float)PULSE_DURATION;

            // Extend travel range so the full pulse clears the ends
            float pathStart = START_LED - PULSE_LENGTH / 2.0;
            float pathEnd = NUM_LEDS - 1 + PULSE_LENGTH / 2.0;
            float pulseCenterF = pathStart + progress * (pathEnd - pathStart);
            int pulseCenter = round(pulseCenterF);

            for (int i = -PULSE_LENGTH / 2; i <= PULSE_LENGTH / 2; i++) {
                int ledIndex = pulseCenter + i;
                if (ledIndex >= START_LED && ledIndex < NUM_LEDS) {
                    leds[ledIndex] = PULSE_COLOR;  // Overlay white pulse
                }
            }
        }
    }


    waveOffset += WAVE_SPEED;
    FastLED.show();
    FastLED.delay(SPEED);
}
