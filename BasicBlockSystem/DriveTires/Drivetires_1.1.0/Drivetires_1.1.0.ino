// Pin definitions for Motor 1
const int in1Pin = 2;  // IN1 on H-Bridge
const int in2Pin = 3;  // IN2 on H-Bridge
const int enPin1 = 9;  // ENA (Enable) on H-Bridge (PWM pin)

// Pin definitions for Motor 2
const int in3Pin = 4;  // IN3 on H-Bridge
const int in4Pin = 5;  // IN4 on H-Bridge
const int enPin2 = 10; // ENB (Enable) on H-Bridge (PWM pin)

// Motor speed (0-255)
int motorSpeed1 = 255; // Set Motor 1 to full speed
int motorSpeed2 = 255; // Set Motor 2 to full speed

void setup() {
  // Set up the pin modes for Motor 1
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enPin1, OUTPUT);

  // Set up the pin modes for Motor 2
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(enPin2, OUTPUT);

  // Start with motors stopped
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin1, 0);

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  analogWrite(enPin2, 0);
}

void loop() {
  // Motor 1 Forward
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin1, motorSpeed1);  // Set Motor 1 speed

  // Motor 2 Forward
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enPin2, motorSpeed2);  // Set Motor 2 speed

  delay(2000);  // Run forward for 2 seconds

  // Stop both motors
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin1, 0);

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  analogWrite(enPin2, 0);

  delay(1000);  // Stop for 1 second

  // Motor 1 Backward
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enPin1, motorSpeed1);  // Set Motor 1 speed

  // Motor 2 Backward
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  analogWrite(enPin2, motorSpeed2);  // Set Motor 2 speed

  delay(2000);  // Run backward for 2 seconds

  // Stop both motors
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin1, 0);

  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  analogWrite(enPin2, 0);

  delay(1000);  // Stop for 1 second
}
