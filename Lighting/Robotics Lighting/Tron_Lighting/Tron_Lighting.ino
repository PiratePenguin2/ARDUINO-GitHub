#include <FastLED.h>

#define LED_PIN        7     // Data pin for LED strip
#define START_LED      2//113
#define NUM_LEDS       86//61    // Number of LEDs
#define WAVE_SPEED     3     // Speed of the moving wave
#define SPEED          20    // Overall wave update speed (lower = faster)
#define BRIGHTNESS_MASTER 255

#define LIT_WAVE_SIZE  20
#define DULL_WAVE_SIZE 100
#define LIT_BRIGHTNESS 255
#define DULL_BRIGHTNESS 40
#define COLOR          CRGB(0, 0, 255)  // Base wave color

#define PULSE_LENGTH   10       // Length of the pulse in pixels
#define PULSE_COLOR    CRGB::White //CRGB(255, 8, 0)
#define PULSE_INTERVAL 5000    // Time between new pulses (ms)
#define PULSE_DURATION 1000    // Time for a pulse to travel full strip (ms)
#define PULSE_SOLID_PERCENT 0.2

CRGB leds[NUM_LEDS];

unsigned long lastPulseStart = 0;
bool pulseActive = false;
const float edgePercent = (1.0 - PULSE_SOLID_PERCENT) / 2.0;  // 30% on each edge if solid is 40%
bool pulseDirectionForward = false;

void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();
    FastLED.setBrightness(BRIGHTNESS_MASTER);
}

void drawWaveEffect(uint16_t waveOffset) {
    for (int i = START_LED; i < NUM_LEDS; i++) {
        uint8_t wave = sin8((i * 255 / (LIT_WAVE_SIZE + DULL_WAVE_SIZE)) + waveOffset);
        uint8_t brightness = map(wave, 0, 255, DULL_BRIGHTNESS, LIT_BRIGHTNESS);
        leds[i] = COLOR;
        leds[i].nscale8(brightness);
    }
}

void drawPulseEffect() {
    float elapsed = millis() - lastPulseStart;
    if (elapsed >= PULSE_DURATION) {
        pulseActive = false;
        return;
    }

    float progress = elapsed / (float)PULSE_DURATION;
    float pathStart = START_LED - PULSE_LENGTH / 2.0;
    float pathEnd = NUM_LEDS - 1 + PULSE_LENGTH / 2.0;
    float pulseCenterF = pulseDirectionForward
        ? pathStart + progress * (pathEnd - pathStart)
        : pathEnd - progress * (pathEnd - pathStart);
    int pulseCenter = round(pulseCenterF);

    for (int i = -PULSE_LENGTH / 2; i <= PULSE_LENGTH / 2; i++) {
        int ledIndex = pulseCenter + i;
        if (ledIndex >= START_LED && ledIndex < NUM_LEDS) {
            CRGB baseColor = leds[ledIndex];
            int relativeIndex = i + PULSE_LENGTH / 2;
            float pct = relativeIndex / float(PULSE_LENGTH);
            uint8_t blendAmount;

            if (pct < edgePercent) {
                float fadePct = pct / edgePercent;
                blendAmount = fadePct * 255;
            } else if (pct < (1.0 - edgePercent)) {
                blendAmount = 255;
            } else {
                float fadePct = (pct - (1.0 - edgePercent)) / edgePercent;
                blendAmount = (1.0 - fadePct) * 255;
            }

            leds[ledIndex] = blend(baseColor, PULSE_COLOR, blendAmount);
        }
    }
}

void loop() {
    static uint16_t waveOffset = 0;
    unsigned long now = millis();

    if (!pulseActive && (now - lastPulseStart >= PULSE_INTERVAL)) {
        lastPulseStart = now;
        pulseActive = true;
    }

    drawWaveEffect(waveOffset);

    if (pulseActive) {
        drawPulseEffect();
    }

    waveOffset += WAVE_SPEED;
    FastLED.show();
    FastLED.delay(SPEED);
}
