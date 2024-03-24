// Arduino Uno (Main) Code

void setup() {
  Serial.begin(9600); // Begin serial communication at 9600 baud rate
}

void loop() {
  Serial.println("Hi from Arduino Uno!"); // Send a greeting message
  
  if (Serial.available()) { // Check if data is available to read
    char receivedChar = Serial.read(); // Read the incoming character
    if (receivedChar == 'A') { // Check if the received character is 'A'
      Serial.println("Sending command to Nano 1...");
      Serial.write('A'); // Send command to Nano 1
    }
  }
  
  delay(1000); // Delay for 1 second
}
