const int ledPin = 3; // Define the LED pin

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
}

void loop() {
  Serial.println("Enter a command (1, 2, 3, 4):");

  while (Serial.available() == 0) {
    // Wait for user input
  }

  int userInput = Serial.read() - '0'; // Read the user input and convert it to an integer

  switch (userInput) {
    case 1:
      digitalWrite(ledPin, HIGH);
      Serial.println("LED turned ON");
      break;
    case 2:
      digitalWrite(ledPin, LOW);
      Serial.println("LED turned OFF");
      break;
    case 3:
      Serial.println("Custom command 3 executed");
      // Add your custom code here
      break;
    case 4:
      Serial.println("Custom command 4 executed");
      // Add your custom code here
      break;
    default:
      Serial.println("Invalid command. Please enter a valid command (1, 2, 3, 4).");
      break;
  }

  delay(1000); // Add a small delay to make the output easier to read
}
