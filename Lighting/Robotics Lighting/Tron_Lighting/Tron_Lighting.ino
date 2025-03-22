#include <FastLED.h>

#define LED_PIN        2     // Data pin for LED strip
#define NUM_LEDS       160   // Number of LEDs
#define WAVE_SPEED     3    // Speed of the moving wave

#define LIT_WAVE_SIZE  20    // Width of the bright wave
#define DULL_WAVE_SIZE 100    // Width of the dim sections

#define LIT_BRIGHTNESS 255   // Maximum brightness of the wave
#define DULL_BRIGHTNESS 40   // Minimum brightness of the wave
//#define COLOR         CHSV(225, 255, 255) // Base color (Hue, Saturation, Value)
#define COLOR         CRGB(30,30,255)
//#define COLOR         CRGB(255,8,0)
#define SPEED         20    // Overall speed of effect (lower is faster)

#define BRIGHTNESS_MASTER 100

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();
    FastLED.setBrightness(BRIGHTNESS_MASTER);
}

void loop() {
    static uint16_t waveOffset = 0;  // Tracks traveling wave position

    for (int i = 97; i < NUM_LEDS; i++) {
        uint8_t wave = sin8((i * 255 / (LIT_WAVE_SIZE + DULL_WAVE_SIZE)) + waveOffset);  // Moving wave effect
        uint8_t brightness = map(wave, 0, 255, DULL_BRIGHTNESS, LIT_BRIGHTNESS);  // Scale brightness

        leds[i] = COLOR;//CHSV(160, 255, brightness);  // Apply color with varying brightness
        leds[i].nscale8_video(brightness);
    }

    waveOffset += WAVE_SPEED;  // Move the wave down the strip
    FastLED.show();
    delay(SPEED);
}
