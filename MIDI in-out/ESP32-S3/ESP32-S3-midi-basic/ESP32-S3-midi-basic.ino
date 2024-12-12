#include <Arduino.h>
#include "USBMIDI.h"

// Instantiate the USB MIDI class
USBMIDI usbMidi;

void setup() {
  // Initialize USB MIDI
  usbMidi.begin();

  // Wait for USB host to initialize
  while (!tud_mounted()) {
    delay(10);
  }

  Serial.begin(115200);
  Serial.println("USB MIDI Initialized");
}

void loop() {
}
