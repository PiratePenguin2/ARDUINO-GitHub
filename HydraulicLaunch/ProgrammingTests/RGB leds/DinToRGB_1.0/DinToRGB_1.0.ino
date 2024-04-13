#define CLOCK_PIN 2  // Clock pin connected to D3
#define DATA_PIN 3   // Data pin connected to D4

void setup() {
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void sendData(byte data) {
  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(DATA_PIN, LOW);

  // Send 8 bits of data
  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA_PIN, data & 0x01);
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
    data >>= 1;
  }
}

void setRGBColor(byte red, byte green, byte blue) {
  // Construct the data byte for RGB values
  byte data = (blue & 0b11111000) | (green >> 5);
  sendData(data);

  data = (green << 3) | (red >> 3);
  sendData(data);

  data = (red << 5) | 0x1F;  // Blue value is already in the first byte
  sendData(data);
}

void loop() {
  // Example: Set RGB color to Red
  setRGBColor(255, 0, 0);
  delay(1000);  // Delay for 1 second

  // Example: Set RGB color to Green
  setRGBColor(0, 255, 0);
  delay(1000);  // Delay for 1 second

  // Example: Set RGB color to Blue
  setRGBColor(0, 0, 255);
  delay(1000);  // Delay for 1 second
}
