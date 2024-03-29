//Vcc Red, Gnd Black, A Phase White, B Phase Green

long counter = 0;
long temp = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
}

void loop() {
  if(counter != temp) {
    Serial.print("\t");
    Serial.println(counter);
    temp = counter;
  }
  //Serial.println(counter);
}

void ai0() {
  if(digitalRead(3) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void ai1() {
  if(digitalRead(2) == LOW) {
    counter--;
  } else {
    counter++;
  }
}
