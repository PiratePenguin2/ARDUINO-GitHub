#include <Keyboard.h>
#include "PTsensor.h"

// Define the button pins
const int pin_keyL_no = 2; const int pin_keyL_nc = 3;
const int pin_keyR_no = 4; const int pin_keyR_nc = 5;

const int pin_btnL_no = 6; const int pin_btnL_nc = 7;
//const int btnR_no = 8; const int btnR_nc = 9;

const int pin_toggle1_no = 8; const int pin_toggle1_nc = 9;
const int pin_toggle2_no = 10; const int pin_toggle2_nc = 11;
//const int pin_toggle3_no = 14; const int pin_toggle3_nc = 15;

const int pin_eStop_no = 12; const int pin_eStop_nc = 13;

// Initialize the button pins as input with pull-up resistors
Sensor keyL_no = Sensor();  Sensor keyL_nc = Sensor();
Sensor keyR_no = Sensor();  Sensor keyR_nc = Sensor();

Sensor btnL_no = Sensor();  Sensor btnL_nc = Sensor();
Sensor btnR_no = Sensor();  Sensor btnR_nc = Sensor();

Sensor toggle1_no = Sensor();  Sensor toggle1_nc = Sensor();
Sensor toggle2_no = Sensor();  Sensor toggle2_nc = Sensor();
Sensor toggle3_no = Sensor();  Sensor toggle3_nc = Sensor();

Sensor eStop_no = Sensor();  Sensor eStop_nc = Sensor();

void setup() {
  keyL_no.attach(pin_keyL_no); keyL_nc.attach(pin_keyL_nc);
  keyR_no.attach(pin_keyR_no); keyR_nc.attach(pin_keyR_nc);

  btnL_no.attach(pin_btnL_no); btnL_nc.attach(pin_btnL_nc);
  //btnR_no.attach(pin_btnR_no); btnR_nc.attach(pin_btnR_nc);
  
  toggle1_no.attach(pin_toggle1_no); toggle1_nc.attach(pin_toggle1_nc);
  toggle2_no.attach(pin_toggle2_no); toggle2_nc.attach(pin_toggle2_nc);
  //toggle3_no.attach(pin_toggle3_no); toggle3_nc.attach(pin_toggle3_nc);

  //eStop_no.attach(pin_eStop_no); eStop_nc.attach(pin_eStop_nc);

  // Start the keyboard emulation
  Keyboard.begin();
}

/*void loop() {
  // Read the state of the buttons (LOW means pressed, HIGH means not pressed)
  Serial.print(keyL_no.read()); Serial.print(" "); Serial.println(keyL_nc.read());
  updateToggle("KeyL", keyL_no, keyL_nc, '8', '2');
  Serial.print(keyL_no.read()); Serial.print(" "); Serial.println(keyL_nc.read());
  //updateToggle("KeyR", keyR_no, keyR_nc, '9', '3');

  //updatePush("ButtonL", btnL_no, btnL_nc, KEY_RETURN);
  //updatePush("ButtonR", btnR_no, btnR_nc, KEY_RETURN);

  //updateToggle("Toggle1", toggle1_no, toggle1_nc, '8', '2');
  //updateToggle("Toggle2", toggle2_no, toggle2_nc, '9', '3');
  //updateToggle("Toggle3", toggle3_no, toggle3_nc, '7', '1');

  //updateToggle("E-Stop", eStop_no, eStop_nc, KEY_F8, KEY_F8);

  // Add a small delay to avoid flooding the keyboard with multiple key presses
  Serial.println("loop");
  delay(500);
}*/

void updatePush(String name, Sensor buttonNO, Sensor buttonNC, char key) {
  buttonNO.update(); buttonNC.update();

  if (buttonNO.read() == true && buttonNC.read() == true) {
    Serial.println("ERROR: Both NO and NC readings of " + name + " are pressed");
  }
  else if (buttonNO.read() == false && buttonNC.read() == false) {
    Serial.println("ERROR: Wire disconnected on " + name);
  }
  else if (buttonNO.isTripped()) {
    Keyboard.press(key);  // Simulate key press
    Serial.println("Key " + String(key) + " pressed");
  }
  else if (buttonNC.isTripped()) {
    Keyboard.release(key);  // Release key
    Serial.println("Key " + String(key) + " released");
  }
}

/*void updateToggle(String name, Sensor buttonNO, Sensor buttonNC, char keyOn, char keyOff) {
  buttonNO.update(); buttonNC.update();

  if (buttonNO.read() == true && buttonNC.read() == true) {
    Serial.println("ERROR: Both NO and NC readings of " + name + " are pressed");
  }
  else if (!buttonNO.read() && !buttonNC.read()) {
    Serial.println("ERROR: Wire disconnected on " + name);
  }
  else if (buttonNO.isTripped()) {
    Serial.println("Key on pushed");
    //Keyboard.press('2');  // Simulate key press & release
    //Keyboard.release('2'); // Release key
  }
  else if (buttonNC.isTripped()) {
    Keyboard.press(keyOff);  // Simulate key press & release
    Keyboard.release(keyOff); // Release key
    Serial.println("Key off pushed");
  }
}*/

void updateToggle(String name, Sensor buttonNO, Sensor buttonNC, char keyOn, char keyOff) {
  buttonNO.update(); buttonNC.update();

  if (buttonNO.read() && buttonNC.read()) {
    Serial.println("ERROR: Both NO and NC readings of " + name + " are pressed");
  }
  else if (!buttonNO.read() && !buttonNC.read()) {
    Serial.println("ERROR: Wire disconnected on " + name);
  }
  if (buttonNO.isTripped()) {
    Serial.println("Key ON pushed");
    Keyboard.press(keyOn);
    Keyboard.release(keyOn);
  }
  if (buttonNC.isTripped()) {
    Serial.println("Key OFF pushed");
    Keyboard.press(keyOff);
    Keyboard.release(keyOff);
  }
}




void loop() {
  keyL_no.update();
  keyL_nc.update();

  // Key ON logic
  if (keyL_no.isTripped()) {
    Serial.println("Key ON pushed");
    //Keyboard.press('8');
    //Keyboard.release('8');
  }

  // Key OFF logic
  if (keyL_nc.isTripped()) {
    Serial.println("Key OFF pushed");
    //Keyboard.press('2');
    //Keyboard.release('2');
  }

  delay(50);  // Small delay for loop stability
}



void finish() {
  Keyboard.end();
}

