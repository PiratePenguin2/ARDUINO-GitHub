#include <Bounce2.h>

// Number of switches and buttons
#define NUM_SWITCHES 1
#define NUM_BUTTONS 1

// Pins for switches (NO and NC for each switch)
const int switchPins[NUM_SWITCHES][2] = {
  {4, 5}  // Switch 1: NO=4, NC=5
  //{6, 7},  // Switch 2: NO=6, NC=7
  //{8, 9},  // Switch 3: NO=8, NC=9
  //{10, 11},  // Switch 4: NO=10, NC=11
  //{12, 13},// Switch 5: NO=12, NC=13
  //{14, 15} // Switch 6: NO=14, NC=15
};

// Pins for buttons (NO and NC for each button)
const int buttonPins[NUM_BUTTONS][2] = {
  {12, 13} // Button 1: NO=16, NC=17
  //{18, 21}  // Button 2: NO=18, NC=21
};

// Debouncer objects for switches and buttons
Bounce debouncedSwitches[NUM_SWITCHES][2]; // [switch][NO/NC]
Bounce debouncedButtons[NUM_BUTTONS][2];  // [button][NO/NC]

void setup() {
  Serial.begin(115200);

  // Initialize switches
  for (int i = 0; i < NUM_SWITCHES; i++) {
    for (int j = 0; j < 2; j++) { // 0 = NO, 1 = NC
      pinMode(switchPins[i][j], INPUT_PULLUP);               // Use internal pull-up resistors
      debouncedSwitches[i][j].attach(switchPins[i][j]);      // Attach the pin to the debouncer
      debouncedSwitches[i][j].interval(50);                  // Set debounce interval (50ms)
    }
  }

  // Initialize buttons
  for (int i = 0; i < NUM_BUTTONS; i++) {
    for (int j = 0; j < 2; j++) { // 0 = NO, 1 = NC
      pinMode(buttonPins[i][j], INPUT_PULLUP);               // Use internal pull-up resistors
      debouncedButtons[i][j].attach(buttonPins[i][j]);       // Attach the pin to the debouncer
      debouncedButtons[i][j].interval(50);                   // Set debounce interval (50ms)
    }
  }
}

void loop() {
  // Check switches
  for (int i = 0; i < NUM_SWITCHES; i++) {
    for (int j = 0; j < 2; j++) { // Update debouncers
      debouncedSwitches[i][j].update();
    }

    // Read current states
    bool noState = debouncedSwitches[i][0].read(); // NO pin state
    bool ncState = debouncedSwitches[i][1].read(); // NC pin state

    // Check for errors
    if (noState == ncState) { // Both HIGH or both LOW
      Serial.print("ERROR: Switch ");
      Serial.print(i + 1);
      Serial.println(" has a wiring issue!");
    } else if (!noState) { // NO pressed (LOW)
      Serial.print("Switch ");
      Serial.print(i + 1);
      Serial.println(" turned ON (NO).");
    } else if (!ncState) { // NC pressed (LOW)
      Serial.print("Switch ");
      Serial.print(i + 1);
      Serial.println(" turned OFF (NC).");
    }
  }

  // Check buttons
  for (int i = 0; i < NUM_BUTTONS; i++) {
    for (int j = 0; j < 2; j++) { // Update debouncers
      debouncedButtons[i][j].update();
    }

    // Read current states
    bool noState = debouncedButtons[i][0].read(); // NO pin state
    bool ncState = debouncedButtons[i][1].read(); // NC pin state

    // Check for errors
    if (noState == ncState) { // Both HIGH or both LOW
      Serial.print("ERROR: Button ");
      Serial.print(i + 1);
      Serial.println(" has a wiring issue!");
    } else if (!noState) { // NO pressed (LOW)
      Serial.print("Button ");
      Serial.print(i + 1);
      Serial.println(" pressed (NO).");
    } else if (!ncState) { // NC pressed (LOW)
      Serial.print("Button ");
      Serial.print(i + 1);
      Serial.println(" released (NC).");
    }
  }
  delay(100);
}
