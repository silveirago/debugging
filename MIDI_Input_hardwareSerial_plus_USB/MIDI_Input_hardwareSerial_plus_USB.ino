#include <MIDI.h>  // Add midi2 Library

#define LED 9    // connect an led to pin 9 with t 220Ω resistor

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midi2);

void setup() {
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output

  midi2.begin(MIDI_CHANNEL_OMNI); // Initialize the midi2 Library.
  // OMNI sets it to listen to all channels.. midi2.begin(2) would set it
  // to respond to notes on channel 2 only.
  midi2.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the midi2 Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  midi2.setHandleNoteOff(MyHandleNoteOff); // This command tells the midi2 Library
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.

  Serial1.begin(31250); // use 115200 For Hairless midi2 or 31250 for physical 5-pin midi2 din
}

void loop() { // Main loop
  midi2.read(); // Continuously check if midi2 data has been received.
}

// MyHandleNoteON is the function that will be called by the midi2 Library
// when a midi2 NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
  digitalWrite(LED, HIGH); //Turn LED on
}

// MyHandleNoteOFF is the function that will be called by the midi2 Library
// when a midi2 NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {
  digitalWrite(LED, LOW); //Turn LED off
}
