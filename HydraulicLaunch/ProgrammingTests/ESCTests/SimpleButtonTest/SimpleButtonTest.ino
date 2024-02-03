// Test sketch for button
const int buttonPin = 2;

void setup() {
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
}

void loop() {
    int buttonState = digitalRead(buttonPin);
    Serial.println(buttonState);
    delay(500);  // Add a delay for readability
}
