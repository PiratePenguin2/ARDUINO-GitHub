#include <FastLED.h>

#define LED_PIN     2    // Pin connected to the LED strip
#define NUM_LEDS    160  // Adjust to your LED count
#define BRIGHTNESS  50   // Adjust brightness (0-255)
#define FPS         30   // Global FPS setting
#define PULSE_INTERVAL 3000 // Interval to start a new pulse (in milliseconds)

CRGB leds[NUM_LEDS];

class PulseEffect {
public:
    PulseEffect(int startIdx, int endIdx, CRGB baseColor, CRGB pulseColor, int moveDuration, int startLength, int endLength)
        : startIdx(startIdx), endIdx(endIdx), baseColor(baseColor), pulseColor(pulseColor),
          moveDuration(moveDuration), startLength(startLength), endLength(endLength), active(false) {
        pulseStartTime = 0;

        // Compute start and end positions
        initialBack = startIdx - startLength;
        initialFront = startIdx - 1;
        finalBack = endIdx + 1;
        finalFront = endIdx + endLength;
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

        // Compute dynamic positions of front and back
        int frontPos = map(pulseTime, 0, moveDuration, initialFront, finalFront);
        int backPos = map(pulseTime, 0, moveDuration, initialBack, finalBack);

        // Ensure backPos does not exceed frontPos
        if (backPos > frontPos) backPos = frontPos;

        // Clamp within LED range
        frontPos = constrain(frontPos, 0, NUM_LEDS - 1);
        backPos = constrain(backPos, 0, NUM_LEDS - 1);

        // Update LED colors
        for (int i = startIdx - startLength; i <= endIdx + endLength; i++) {
            if (i >= backPos && i <= frontPos) {
                leds[i] = pulseColor;
            } else {
                leds[i] = baseColor;
            }
        }
    }

private:
    int startIdx, endIdx;
    int initialBack, initialFront;
    int finalBack, finalFront;
    CRGB baseColor, pulseColor;
    int moveDuration;
    int pulseStartTime;
    int startLength, endLength;
    bool active;
};

// Create a pulse effect with start at 10, end at 20, start length 5, end length 10
PulseEffect pulse1(97, 159, CRGB(30, 30, 255), CRGB(255, 8, 0), 3000, 5, 5);
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
