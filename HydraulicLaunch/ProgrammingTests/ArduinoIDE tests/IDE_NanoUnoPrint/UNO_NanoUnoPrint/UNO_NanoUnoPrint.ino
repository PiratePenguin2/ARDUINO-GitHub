void setup() {
  Serial.begin(9600); // Start serial communication
}

void loop() {
  Serial.println("Message from Arduino Uno"); // Print message
  delay(1000); // Wait for 1 second
}
