/*
  This Arduino code interfaces with a button matrix and controls LEDs based on button presses.
  It was created by Gustavo Silveira, a.k.a. the Nerd Musician.
  Website: go.musiconerd.com
*/

// Define the pins for rows and columns
const int numRows = 2;
const int numCols = 4;
const int N_BUTTONS = numCols * numRows;
int rowPins[numRows] = { 14, 15 };          // Pins for rows
int colPins[numCols] = { 16, 17, 18, 19 };  // Pins for columns

// Placeholder for storing button states
int buttonStates[numRows][numCols];
int buttonState[N_BUTTONS] = { 0 };
int buttonPState[N_BUTTONS] = { 0 };

// LEDs
const int N_LEDS = 8;
int ledPin[N_LEDS] = { 9, 8, 7, 6, 5, 4, 3, 2 };  // Pins for LEDs

void setup() {
  // Initialize row pins as outputs
  for (int row = 0; row < numRows; row++) {
    pinMode(rowPins[row], OUTPUT);
    digitalWrite(rowPins[row], HIGH);  // Set to HIGH initially
  }

  // Initialize column pins as inputs with internal pull-up resistors
  for (int col = 0; col < numCols; col++) {
    pinMode(colPins[col], INPUT_PULLUP);
  }

  // Initialize LED pins as outputs
  for (int i = 0; i < N_LEDS; i++) {
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW);  // Turn off all LEDs initially
  }

  Serial.begin(9600);  // Start serial communication for debugging
}

void loop() {
  scanButtonMatrix();  // Scan the button matrix
}

// Function to scan the button matrix
void scanButtonMatrix() {
  for (int row = 0; row < numRows; row++) {
    digitalWrite(rowPins[row], LOW);  // Set the current row LOW
    for (int col = 0; col < numCols; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        // Button pressed
        buttonStates[row][col] = 1;
        buttonState[row * numCols + col] = 1;   // Corrected indexing
        printButtonState(row * numCols + col);  // Print button state
      } else {
        // Button released
        buttonStates[row][col] = 0;
        buttonState[row * numCols + col] = 0;   // Corrected indexing
        printButtonState(row * numCols + col);  // Print button state
      }
    }
    digitalWrite(rowPins[row], HIGH);  // Reset the row pin to HIGH after checking
  }
}

// Function to print the state of buttons and control LEDs accordingly
void printButtonState(int index) {
  if (buttonPState[index] != buttonState[index]) {
    Serial.print("Button ");
    Serial.print(index);

    if (buttonState[index] > 0) {
      // Button pressed, turn on corresponding LED
      digitalWrite(ledPin[index], HIGH);
      Serial.println(": on");
    } else {
      // Button released, turn off corresponding LED
      digitalWrite(ledPin[index], LOW);
      Serial.println(": off");
    }

    buttonPState[index] = buttonState[index];
  }
}
