#include <Keyboard.h>

// Define button pins
const int buttonPins[8] = {9, 8, 7, 6, 5, 4, 3, 2};
// Define corresponding keys for each button
const char keyMap[8] = {'3', '9', KEY_RETURN, '2', '8', '0', KEY_F8, KEY_F8};

// Store previous button states
bool lastButtonStates[8] = {false};
bool eStopState = false;

void setup() {
    Keyboard.begin(); // Initialize the keyboard
    
    // Set up button pins as inputs with internal pull-ups
    for (int i = 0; i < 8; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
}

void loop() {
    for (int i = 0; i < 8; i++) {
        bool currentState = !digitalRead(buttonPins[i]); // Read button (invert logic)

        if (currentState && !lastButtonStates[i]) { // If button is pressed and was NOT pressed before
            if (i == 6 && !eStopState) {
              eStopState = true;
              Keyboard.write(keyMap[6]);
            }
            else if (i == 7 && eStopState) {
              eStopState = false;
              Keyboard.write(keyMap[7]);
            }
            else {
              Keyboard.write(keyMap[i]); // Send the corresponding key
            }
            delay(50); // Small debounce delay
        }

        lastButtonStates[i] = currentState; // Update last state
    }
}
