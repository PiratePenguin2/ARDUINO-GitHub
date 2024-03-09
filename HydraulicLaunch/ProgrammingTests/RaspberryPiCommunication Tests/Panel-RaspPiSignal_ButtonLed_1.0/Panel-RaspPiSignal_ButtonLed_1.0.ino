// Panel.ino

const int buttonPin = 3;
const int ledPin = 2;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("BUTTON_PRESSED");
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  delay(50);  // Debounce delay
}
