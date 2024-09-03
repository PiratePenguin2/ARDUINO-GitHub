#include <Wire.h>
#include <Adafruit_PCF8574.h>

// Create an instance of the PCF8574 with the I2C address (default is 0x20)
Adafruit_PCF8574 pcf;

// Define the pin where the LED is connected (P0)
#define LED_PIN 0

void setup() {
  // Initialize I2C communication and the PCF8574
  Wire.begin();
  if (!pcf.begin(0x20)) {  // Change 0x20 if your PCF8574 has a different address
    Serial.println("Couldn't find PCF8574");
    while (1);
  }
  
  // Set the LED pin as an output
  pcf.pinMode(LED_PIN, OUTPUT);
  
  // Start with the LED off
  pcf.digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Turn the LED on
  pcf.digitalWrite(LED_PIN, HIGH);
  delay(1000);  // Wait for 1 second

  // Turn the LED off
  pcf.digitalWrite(LED_PIN, LOW);
  delay(1000);  // Wait for 1 second
}
