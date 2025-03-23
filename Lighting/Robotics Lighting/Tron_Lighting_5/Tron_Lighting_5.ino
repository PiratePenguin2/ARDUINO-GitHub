#include <Adafruit_NeoPixel.h>

#define LED_PIN    2      // Pin where the LED strip is connected
#define LED_COUNT  160     // Total number of LEDs

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int startLED = 160;   // Starting LED position
int endLED = 97;    // Ending LED position
unsigned long moveDuration = 200; // Time (ms) to move from startLED to endLED
unsigned long startTime;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  startTime = millis(); // Record the starting time
}

void loop() {
  updateDotPosition();
}

void updateDotPosition() {
  unsigned long elapsedTime = millis() - startTime;
  
  if (elapsedTime >= moveDuration) {
    startTime = millis(); // Reset timer to loop back
    elapsedTime = 0;
  }

  // Map time to LED position
  int currentLED = map(elapsedTime, 0, moveDuration, startLED, endLED);
  
  // Clear the strip
  strip.clear();
  
  // Set the current LED to a color (e.g., red)
  strip.setPixelColor(currentLED, strip.Color(255, 0, 0));
  
  // Show the updated strip
  strip.show();
}
