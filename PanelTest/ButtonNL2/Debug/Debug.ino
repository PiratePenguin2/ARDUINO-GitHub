#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("I2C Scanner");

  Wire.begin();
}

void loop() {
  Serial.println("Scanning...");

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      Serial.println(address, HEX);
      delay(500);
    }
  }
  Serial.println("Scan complete.");
  delay(2000);
}
