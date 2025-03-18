#include <Keyboard.h>
#include <Wire.h>
#include <Adafruit_PCF8574.h>

Adafruit_PCF8574 pcf1;
Adafruit_PCF8574 pcf2;

#define NUM_BUTTONS 8

// Define button pins
// const int buttonPins[NUM_BUTTONS][2] = {
//   {9, 8},
//   {7, 6},
//   {5, 4},
//   {3, 2}
// };
// Define corresponding keys for each button
const char keyMap[NUM_BUTTONS][2] = {
  {'1', '2'},
  {'3', '4'},
  {KEY_RETURN, '0'},
  {'8', '2'},
  {'9', '3'},
  {'4', '6'},
  {'KEY_RETURN', '0'},
  {KEY_F8, KEY_F8}
};
// const char keyMap[NUM_BUTTONS][2] = {
//   {'1', '2'},           // Mode A
//   {'3', '4'},           // Mode B
//   {'c', '0'},    // Dispatch A
//   {'v', 't'},           // Harness
//   {'C', 'V'},           // Gates
//   {'4', '6'},           // Special
//   {'c', '0'},  // Dispatch B
//   {KEY_F8, KEY_F8}
// };
//const char keyMap[NUM_BUTTONS] = {'3', '9', KEY_RETURN, '2', '8', '0', KEY_F8, KEY_F8};

// Store previous button states
bool eStopState = false;
bool currentButtonState = false;
bool lastButtonStates[NUM_BUTTONS][2] = {false, false};
bool buttonsTripped[NUM_BUTTONS][2] = {false, false};
bool buttonsUntripped[NUM_BUTTONS][2] = {false, false};
static bool dispatchToggled = false;

void setup() {
  //Serial.begin(115200);
  //while (!// Serial);
  // Serial.println("// Serial Initialized!");

  Wire.begin();
  // Serial.println("Wire Initialized!");

  if (!pcf1.begin(0x20)) { // Initialize I²C
    // Serial.println("PCF 1 not found");
  }
  else {
    // Serial.println("PCF 1 Initialized!");
  }
  if (!pcf2.begin(0x21)) { // Initialize I²C
    // Serial.println("PCF 2 not found");
  }
  else {
    // Serial.println("PCF 2 Initialized!");
  }

  Keyboard.begin(); // Initialize the keyboard
  
    //pcf1.pinMode(i, INPUT_PULLUP);
    //pinMode(buttonPins[i], INPUT_PULLUP);

  // Set up button pins as inputs with internal pull-ups
  for (int i = 0; i < NUM_BUTTONS; i++) {
    for (int j = 0; j < 2; j++) {
      if (i < 4) {
        pcf1.pinMode((i * 2) + j, INPUT_PULLUP);
        lastButtonStates[i][j] = !pcf1.digitalRead((i * 2) + j);
      }
      // else if (i < 8) {
      //   pinMode((i * 2) + j, INPUT_PULLUP);
      //   lastButtonStates[i][j] = !digitalRead(buttonPins[i - 4][2]);
      // }
      // else if (i < 8) {
      //   pcf2.pinMode((i * 2) + j, INPUT_PULLUP);
      //   lastButtonStates[i][j] = !pcf2.digitalRead((i * 2) + j);
      // }
    }
  }
  // Serial.println("Everything initialized!");
}

void loop() {
  updateButtons();
  if (lastButtonStates[0][0] == true || lastButtonStates[1][0] == true) {
    // DispatchL
    if (lastButtonStates[2][0] && lastButtonStates[6][0]) {
      if (!dispatchToggled) { // If the key is not pressed yet
        Keyboard.press(keyMap[2][0]); // Press the key
        dispatchToggled = true;
      }
    } else {
      if (dispatchToggled) { // If the key was pressed before
        Keyboard.release(keyMap[2][0]); // Release the key
        dispatchToggled = false;
      }
    }

    // Toggle 1: Restraings
    if (buttonsTripped[3][0] == true) {
      Keyboard.write(keyMap[3][0]);
    }
    else if (buttonsTripped[3][1] == true) {
      Keyboard.write(keyMap[3][1]);
    }
    
    // Toggle 2: Gates
    if (buttonsTripped[4][0] == true) {
      Keyboard.write(keyMap[4][0]);
    }
    else if (buttonsTripped[4][1] == true) {
      Keyboard.write(keyMap[4][1]);
    }
    // if (buttonsTripped[4][0] == true) {
    //   Keyboard.press(KEY_LEFT_SHIFT);  // Hold Shift
    //   Keyboard.press('c');             // Press 'C'
    //   delay(10);                       // Small delay to ensure proper key press
    //   Keyboard.releaseAll();           // Release both keys
    // }
    // else if (buttonsTripped[4][1] == true) {
    //   Keyboard.press(KEY_LEFT_SHIFT);  // Hold Shift
    //   Keyboard.press('v');             // Press 'C'
    //   delay(10);                       // Small delay to ensure proper key press
    //   Keyboard.releaseAll();           // Release both keys
    // }

    // Toggle 3: Flier Lock
    if (buttonsTripped[5][0] == true) {
      Keyboard.write(keyMap[5][0]);
    }
    else if (buttonsTripped[5][1] == true) {
      Keyboard.write(keyMap[5][1]);
    }

    // if (buttonsTripped[6][0] == true) {
    //   Keyboard.write(keyMap[6][0]);
    // }

    // while (lastButtonStates[7][0] == true || lastButtonStates[8][1] == false) {
      if (buttonsTripped[7][0] == true) {
        Keyboard.write(keyMap[7][0]);
      }
      else if (buttonsTripped[7][1] == true) {
        Keyboard.write(keyMap[7][1]);
      }
    //   delay(100);
    // }
  }
  delay(50);
}

void updateButtons() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    for (int j = 0; j < 2; j++) {
      buttonsTripped[i][j] = false;
      buttonsUntripped[i][j] = false;
      if (i < 4) {
        currentButtonState = !pcf1.digitalRead((i * 2) + j); // Read button (invert logic)
      }
      // else if (i < 8) {
      //   currentButtonState = !digitalRead(buttonPins[i - 4][2]);
      // }
      else if (i < 8) {
        currentButtonState = !pcf2.digitalRead(((i - 4) * 2) + j); // Read button (invert logic)
      }
      else {
        continue;
      }

      if (currentButtonState == !lastButtonStates[i][j]) {
        if (currentButtonState) {
          buttonsTripped[i][j] = true;
          // Serial.print("Button pressed: ");
          // Serial.print(i);
          // Serial.print(" ");
          // Serial.println(j);
        }
        else {
          buttonsUntripped[i][j] = true;
          // // Serial.print("Button released: ");
          // // Serial.print(i);
          // // Serial.print(" ");
          // // Serial.println(j);
        }
        lastButtonStates[i][j] = currentButtonState;
      }
    }
    // if (currentButtonStates[i][0] == true && currentButtonStates[i][1] == true) {
    //   //// Serial.print("Both NO and NC states for button: ");
    //   //// Serial.println(i);
    // }
    // else if (!currentButtonStates[i][0] == false && !currentButtonStates[i][1] == false) {
    //   //// Serial.print("Wire disconnected for button: ");
    //   //// Serial.println(i);
    // }
  }
}
    // currentButtonState = !digitalRead(buttonPins[i]); // Read button (invert logic)

  //   if (currentButtonState && !lastButtonStates[i]) { // If button is pressed and was NOT pressed before
  //     if (i == 6 && !eStopState) {
  //       eStopState = true;
  //       Keyboard.write(keyMap[6]);
  //     }
  //     else if (i == 7 && eStopState) {
  //       eStopState = false;
  //       Keyboard.write(keyMap[7]);
  //     }
  //     else {
  //       Keyboard.write(keyMap[i]); // Send the corresponding key
  //     }
  //     delay(50); // Small debounce delay
  //   }

  //   lastButtonStates[i] = currentButtonState; // Update last state
  // }