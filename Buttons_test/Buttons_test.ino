/*
Wiring Instructions:
1. Connect one terminal of the pushbutton to digital pin 10 on the Arduino.
2. Connect the other terminal of the pushbutton to the GND (ground) pin on the Arduino.
3. The internal pull-up resistor will be used to keep the pin HIGH when the button is not pressed.
*/

// Constants for pin numbers and button count
const int buttonN = 6;                                // Total number of buttons
const int buttonPin[buttonN] = { 4, 5, 6, 7, 8, 9 };  // Pin number for the button

// Variable to store button state
int buttonState[buttonN] = { 0 };  // State of the button (0 = not pressed, 1 = pressed)

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
  for (int i = 0; i < buttonN; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
  }
}

void loop() {
  // Read the state of each button and store it in buttonState array
  for (int i = 0; i < buttonN; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);  // Read button state (HIGH if not pressed, LOW if pressed)
  }

  // Print the state of each button to the Serial Monitor
  for (int i = 0; i < buttonN; i++) {
    if (buttonState[i] == HIGH) {  // Button not pressed
      Serial.print(i);
      Serial.print(": OFF   ");
    } else {  // Button pressed
      Serial.print(i);
      Serial.print(": ON    ");
    }
  }
  Serial.println();  // Print a newline for readability in Serial Monitor
  delay(10);         // Short delay to prevent excessive serial output
}
