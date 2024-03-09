// Lamps.ino

const int lampPin = 2;

void setup() {
  pinMode(lampPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char signal = Serial.read();
    
    if (signal == 'L') {
      digitalWrite(lampPin, HIGH);
      delay(1000);  // Keep the lamp on for 1 second
      digitalWrite(lampPin, LOW);
    }
  }
}
