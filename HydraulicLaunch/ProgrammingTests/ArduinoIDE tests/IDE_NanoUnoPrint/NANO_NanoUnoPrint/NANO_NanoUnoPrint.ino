void setup() {
  Serial.begin(9600); // Start serial communication
}

void loop() {
  //if (Serial.available()) { // Check if data is available to read
    Serial.println("Message from Arduino Nano"); // Print message
    delay(1000); // Wait for 1 second
  //}
}
