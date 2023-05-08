#include <MIDI.h>  // Add Midi Library

#define LED 13  // Arduino Board LED is on Pin 13

//Create an instance of the library with default name, serial port and settings
//MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(LED, OUTPUT);  // Set Arduino board pin 13 to output

  MIDI.begin(MIDI_CHANNEL_OMNI);  // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it
  // to respond to notes on channel 2 only.
  MIDI.setHandleNoteOn(MyHandleNoteOn);  // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  MIDI.setHandleNoteOff(MyHandleNoteOff);  // This command tells the Midi Library
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.

  Serial.begin(31250);  // use 115200 For Hairless MIDI or 31250 for physical 5-pin MIDI din
}

void loop() {   // Main loop
  MIDI.read();  // Continuously check if Midi data has been received.
}

// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
  digitalWrite(LED, HIGH);  //Turn LED on
}

// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {
  digitalWrite(LED, LOW);  //Turn LED off
}

void handleProgramChange(byte channel, byte program) {
  // Do something with the program change message
}

void handleAftertouch(byte channel, byte pressure) {
  // Do something with the aftertouch message
}

void handlePitchBend(byte channel, int value) {
  // Do something with the pitch bend message
}

void handleSysEx(byte* data, unsigned int length) {
  // Do something with the system exclusive message
}
