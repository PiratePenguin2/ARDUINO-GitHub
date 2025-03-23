#include <FastLED.h>

#define LED_PIN     2    // Pin connected to the LED strip
#define NUM_LEDS    160  // Adjust to your LED count
#define BRIGHTNESS  50   // Adjust brightness (0-255)
#define FPS         30   // Global FPS setting
#define PULSE_INTERVAL 3000 // Interval to start a new pulse (in milliseconds)

CRGB leds[NUM_LEDS];

class PulseEffect {
public:
    PulseEffect(int startIdx, int endIdx, CRGB baseColor, CRGB pulseColor, int moveDuration)
        : startIndex(startIdx), endIndex(endIdx), baseColor(baseColor), pulseColor(pulseColor), moveDuration(moveDuration), active(false) {
        pulseStartTime = 0;
        pulseLength = random(3, 10); // Initial random pulse length
    }

    void start() {
        if (!active) {
            pulseStartTime = millis();
            active = true;
        }
    }

    void update() {
        if (!active) return;

        int pulseTime = millis() - pulseStartTime;
        if (pulseTime >= moveDuration) {
            active = false;
            return;
        }

        int pulsePos = map(pulseTime, 0, moveDuration, startIndex, endIndex);
        pulseLength = random(3, 10); // Change pulse length dynamically
        for (int i = startIndex; i < endIndex; i++) {
            if (i >= pulsePos && i < pulsePos + pulseLength) {
                leds[i] = pulseColor;
            } else {
                leds[i] = baseColor;
            }
        }
    }

private:
    int startIndex, endIndex;
    CRGB baseColor, pulseColor;
    int moveDuration;
    int pulseLength;
    int pulseStartTime;
    bool active;
};

PulseEffect pulse1(97, 160, CRGB(30, 30, 255), CRGB(255, 8, 0), 5000);
unsigned long lastPulseTime = 0;

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    Serial.begin(9600);
}

void loop() {
    if (millis() - lastPulseTime >= PULSE_INTERVAL) {
        pulse1.start();
        lastPulseTime = millis();
    }
    
    pulse1.update();
    FastLED.show();
    delay(1000 / FPS);
}
