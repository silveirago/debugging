#include <Adafruit_TinyUSB_MIDI.h>

// Uncomment the line below to enable debug prints
//#define DEBUG_PRINTS

Adafruit_TinyUSB_MIDI MIDI;

void setup() {
  MIDI.begin();
  // Initialize Serial communication at 115200 baud
  Serial.begin(115200);

  // Wait for the Serial Monitor to open
  while (!Serial) {
    // Optionally, you can add a small delay here
  }

  Serial.println("Serial communication started!");
}

void loop() {
  // Print a test message
  Serial.println("Hello, this is a serial print test!");

  // Wait for 1 second
  delay(1000);
}
