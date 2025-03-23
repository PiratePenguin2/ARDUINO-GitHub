#include <Adafruit_NeoPixel.h>

#define LED_PIN 2      // Digital pin connected to the LED strip
#define LED_COUNT 160   // Number of LEDs in the strip

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    strip.setBrightness(100);
}

void loop() {
    //rainbowCycle(10);  // Run a rainbow cycle animation
    //setAllColor(128, 128, 128, 100);
    setAllColor(0,0,255,1000);
    //setAllColor(255,7,0,10);
    //setAllColor(255,255,255,1000);
    delay(10);
}

void setAllColor(uint8_t r, uint8_t g, uint8_t b, int wait) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show(); // Update LED strip
}

void rainbowCycle(int wait) {
    for (int j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on the wheel
        for (int i = 0; i < LED_COUNT; i++) {
            int pixelIndex = (i * 256 / LED_COUNT + j) & 255;
            strip.setPixelColor(i, Wheel(pixelIndex));
        }
        strip.show();
        delay(wait);
    }
}

uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}