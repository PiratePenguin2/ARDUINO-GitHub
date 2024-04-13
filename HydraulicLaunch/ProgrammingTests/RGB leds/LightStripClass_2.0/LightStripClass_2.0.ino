#include <Adafruit_NeoPixel.h>

#define LED_PIN    13
#define LED_COUNT  30

class Led {
  private:
    Adafruit_NeoPixel strip;
  
  public:
    Led(int pin, int count) : strip(count, pin, NEO_GRB + NEO_KHZ800) {
      strip.begin();
      strip.show(); // Initialize all pixels to 'off'
    }
    
    void setColor(int pixel, uint32_t color) {
      strip.setPixelColor(pixel, color);
      strip.show();
    }
    
    Adafruit_NeoPixel& getStrip() {
      return strip;
    }
};

// Define some commonly used colors
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define YELLOW  0xFFFF00
#define CYAN    0x00FFFF
#define MAGENTA 0xFF00FF
#define WHITE   0xFFFFFF

// Function to cycle through the rainbow of colors
void rainbowCycle(Led &ledStrip, uint8_t wait) {
  uint16_t i, j;
  Adafruit_NeoPixel &strip = ledStrip.getStrip(); // Access the strip from the Led object
  
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Helper function for rainbowCycle
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

Led ledStrip(LED_PIN, LED_COUNT);

void setup() {
  // No setup needed
}

void loop() {
  // Cycle through the rainbow of colors
  rainbowCycle(ledStrip, 10);
}
