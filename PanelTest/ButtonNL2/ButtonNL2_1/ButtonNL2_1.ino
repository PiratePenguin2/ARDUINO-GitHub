#include <Keyboard.h>

// Define the button pins
const int button1_no = 3;  // Normally open button for set 1
const int button1_nc = 2;  // Normally closed button for set 1
const int button2_no = 4;  // Normally open button for set 2
const int button2_nc = 5;  // Normally closed button for set 2

void setup() {
  // Initialize the button pins as input with pull-up resistors
  pinMode(button1_no, INPUT_PULLUP);
  pinMode(button1_nc, INPUT_PULLUP);
  pinMode(button2_no, INPUT_PULLUP);
  pinMode(button2_nc, INPUT_PULLUP);

  // Start the keyboard emulation
  Keyboard.begin();
}

void loop() {
  // Read the state of the buttons (LOW means pressed, HIGH means not pressed)
  int button1_no_state = digitalRead(button1_no);
  int button1_nc_state = digitalRead(button1_nc);
  int button2_no_state = digitalRead(button2_no);
  int button2_nc_state = digitalRead(button2_nc);


  if (button1_no_state == LOW && button1_nc_state == LOW) {
    Serial.println("ERROR: Both NO and NC readings of button 1 are pressed");
  }
  else if (button1_no_state == HIGH && button1_nc_state == HIGH) {
    Serial.println("ERROR: Wire disconnected on button 1");
  }
  else if (button1_no_state == LOW) {
    Keyboard.press('2');  // Simulate 'a' key press
  }
  else if (button1_nc_state == LOW) {
    Keyboard.release('2');  // Release 'a' key
  }

  if (button2_no_state == LOW && button2_nc_state == LOW) {
    Serial.println("ERROR: Both NO and NC readings of button 2 are pressed");
  }
  else if (button2_no_state == HIGH && button2_nc_state == HIGH) {
    Serial.println("ERROR: Wire disconnected on button 2");
  }
  else if (button2_no_state == LOW) {
    Keyboard.press(KEY_RETURN);  // Simulate 'a' key press
  }
  else if (button2_nc_state == LOW) {
    Keyboard.release(KEY_RETURN);  // Release 'a' key
  }


  // Add a small delay to avoid flooding the keyboard with multiple key presses
  delay(50);
}

void finish() {
  Keyboard.end();
}
