// Arduino Nano 1 Code

void setup() {
  Serial.begin(9600); // Begin serial communication at 9600 baud rate
}

void loop() {
  if (Serial.available()) { // Check if data is available to read
    char receivedChar = Serial.read(); // Read the incoming character
    if (receivedChar == 'A') { // Check if the received character is 'A'
      Serial.println("Received command from Arduino Uno!");
      Serial.write('B'); // Send command back to Arduino Uno
    }
  }
}
