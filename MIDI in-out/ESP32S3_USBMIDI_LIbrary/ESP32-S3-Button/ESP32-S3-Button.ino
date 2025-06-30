#include <Arduino.h>
#include "USBMIDI.h"

// Create the USB MIDI instance
USBMIDI usbMidi;

const int numButtons = 2;
const int buttonPins[numButtons] = {4, 5};
const int midiNotes[numButtons]  = {60, 62};  // 60: Middle C, 62: D

// MIDI settings
const byte velocity = 127;
const byte channel = 1;

// Arrays to hold the last raw reading and the stable (debounced) state
int lastRawButtonStates[numButtons] = {HIGH, HIGH};  // using INPUT_PULLUP: HIGH = not pressed
int buttonStates[numButtons] = {HIGH, HIGH};           // Debounced stable state

// Arrays for debounce timing
unsigned long lastDebounceTimes[numButtons] = {0, 0};
const unsigned long debounceDelay = 50;  // milliseconds

void setup() {
  Serial.begin(115200);
  
  // Initialize button pins as inputs with internal pull-ups
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  
  // Initialize USB MIDI and wait until the USB host is ready
  usbMidi.begin();
  while (!tud_mounted()) {
    delay(10);
  }
  Serial.println("ESP32S3 USB MIDI Initialized");
}

void loop() {
  unsigned long currentMillis = millis();
  
  for (int i = 0; i < numButtons; i++) {
    int reading = digitalRead(buttonPins[i]);
    
    // If the raw reading has changed, reset the debounce timer
    if (reading != lastRawButtonStates[i]) {
      lastDebounceTimes[i] = currentMillis;
    }
    
    // If the reading has been stable for longer than debounceDelay,
    // consider it the new stable state.
    if ((currentMillis - lastDebounceTimes[i]) > debounceDelay) {
      if (reading != buttonStates[i]) {
        buttonStates[i] = reading;
        
        // Button pressed (transition to LOW)
        if (buttonStates[i] == LOW) {
          usbMidi.noteOn(midiNotes[i], velocity, channel);
          Serial.print("Button ");
          Serial.print(i);
          Serial.print(" pressed - Note On ");
          Serial.println(midiNotes[i]);
        }
        // Button released (transition to HIGH)
        else {
          usbMidi.noteOff(midiNotes[i], 0, channel);
          Serial.print("Button ");
          Serial.print(i);
          Serial.print(" released - Note Off ");
          Serial.println(midiNotes[i]);
        }
      }
    }
    
    // Save the raw reading for the next loop
    lastRawButtonStates[i] = reading;
  }
  
  delay(10);  // Small delay to reduce CPU usage
}
