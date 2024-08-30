#include <Adafruit_TinyUSB.h>

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Define the number of buttons and their corresponding pins
const int NUM_BUTTONS = 2;
const int BUTTON_PINS[NUM_BUTTONS] = {2, 3};

// Define the MIDI notes for each button
const byte MIDI_NOTES[NUM_BUTTONS] = {60, 62};  // C4, D4, E4, F4

// Variables to store button states
int buttonStates[NUM_BUTTONS] = {0};
int lastButtonStates[NUM_BUTTONS] = {0};

void setup() {
  // Initialize USB MIDI
  usb_midi.begin();
  
  // Wait for USB to be ready
  while (!TinyUSBDevice.mounted()) delay(1);

  // Initialize button pins as inputs with pull-up resistors
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
}

void sendMIDIMessage(uint8_t msg, uint8_t note, uint8_t velocity) {
  uint8_t buffer[3] = { msg, note, velocity };
  usb_midi.write(buffer, 3);
}

void loop() {
  // Check the state of each button
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttonStates[i] = digitalRead(BUTTON_PINS[i]);

    // If the button state has changed
    if (buttonStates[i] != lastButtonStates[i]) {
      if (buttonStates[i] == LOW) {
        // Button is pressed, send MIDI Note On message
        sendMIDIMessage(0x90, MIDI_NOTES[i], 127);
      } else {
        // Button is released, send MIDI Note Off message
        sendMIDIMessage(0x80, MIDI_NOTES[i], 0);
      }
      // Update the last button state
      lastButtonStates[i] = buttonStates[i];
    }
  }

  // Handle incoming MIDI messages (if needed)
  while (usb_midi.available()) {
    // Read a single byte
    uint8_t byte = usb_midi.read();
    // Process MIDI input here if needed
    // For example, you could print the byte to Serial for debugging
    // Serial.print(byte, HEX);
  }
}