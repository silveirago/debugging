#include <Adafruit_TinyUSB.h>

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Define the MIDI notes to be sent automatically
const byte MIDI_NOTES[] = {60, 62};  // C4, D4
const int NUM_NOTES = sizeof(MIDI_NOTES) / sizeof(MIDI_NOTES[0]);

// Variable to track which note to send
int currentNoteIndex = 0;

void setup() {
  // Initialize USB MIDI
  usb_midi.begin();
  
  // Wait for USB to be ready
  while (!TinyUSBDevice.mounted()) delay(1);
}

void sendMIDIMessage(uint8_t msg, uint8_t note, uint8_t velocity) {
  uint8_t buffer[3] = { msg, note, velocity };
  usb_midi.write(buffer, 3);
}

void loop() {
  // Send MIDI Note On message for the current note
  sendMIDIMessage(0x90, MIDI_NOTES[currentNoteIndex], 127);

  // Delay for a brief moment before sending the Note Off message
  delay(500);  // Adjust delay as needed

  // Send MIDI Note Off message
  sendMIDIMessage(0x80, MIDI_NOTES[currentNoteIndex], 0);

  // Move to the next note
  currentNoteIndex++;
  if (currentNoteIndex >= NUM_NOTES) {
    currentNoteIndex = 0;
  }

  // Delay for 1000ms before sending the next note
  delay(500);
}
