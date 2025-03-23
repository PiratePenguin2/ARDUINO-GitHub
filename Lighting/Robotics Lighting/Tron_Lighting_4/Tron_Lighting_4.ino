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
        : startIndex(startIdx), endIndex(endIdx), baseColor(baseColor), pulseColor(pulseColor), moveDuration(moveDuration),
          startLength(startLength), endLength(endLength), active(false) {
        pulseStartTime = 0;
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

        // Calculate current pulse length
        int pulseLength = map(pulseTime, 0, moveDuration, startLength, endLength);
        
        // Calculate front and back speeds automatically
        float frontSpeed = float(endIndex + endLength - startIndex) / moveDuration;
        float backSpeed = float(endIndex - (startIndex - startLength)) / moveDuration;

        // Compute positions
        int frontPos = startIndex + frontSpeed * pulseTime;
        int backPos = (startIndex - startLength) + backSpeed * pulseTime;

        // Ensure backPos does not exceed frontPos
        if (backPos > frontPos) backPos = frontPos;

        // Clamp positions within bounds
        frontPos = constrain(frontPos, startIndex, endIndex + endLength);
        backPos = constrain(backPos, startIndex - startLength, endIndex);

        for (int i = 97; i < NUM_LEDS; i++) {
            if (i >= backPos && i <= frontPos) {
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
    int pulseStartTime;
    int startLength, endLength;
    bool active;
};

PulseEffect pulse1(97, 160, CRGB(30, 30, 255), CRGB(255, 8, 0), 200, 5, 15);
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
