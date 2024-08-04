/*
  Reads analog input values from potentiometers and prints the results
  to the Serial Monitor.

  The circuit:
  - Potentiometers connected to analog pins 2 and 4.
    Center pin of each potentiometer goes to the corresponding analog pin.
    Side pins of the potentiometers go to +5V and ground.

  by Gustavo Silveira

  This example code is in the public domain.
*/

// Number of potentiometers
const int potN = 2; // Total number of potentiometers

// Analog input pins for the potentiometers
const int analogInPin[potN] = {2, 4}; // Analog input pins

// Variables to store sensor values
int sensorValue[potN] = {0}; // Raw value read from each potentiometer

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud rate
}

void loop() {
  // Read analog input values
  for (int i = 0; i < potN; i++) {
    sensorValue[i] = analogRead(analogInPin[i]); // Read raw analog value
  }

  // Print the raw values to the Serial Monitor
  for (int i = 0; i < potN; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.print(sensorValue[i]); // Print raw value
    Serial.print("    ");
  }
  Serial.println();

  // Short delay to allow the analog-to-digital converter to settle
  delay(2);
}
