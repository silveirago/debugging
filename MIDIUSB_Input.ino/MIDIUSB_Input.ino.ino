/*
   MIDIUSB_test.ino

   Created: 4/6/2015 10:47:08 AM
   Author: gurbrinder grewal
   Modified by Arduino LLC (2015)
*/

#include "MIDIUSB.h"

#define LED 13    // Arduino Board LED is on Pin 13

void setup() {
  //Serial.begin(115200);
}

void loop() {

  MIDIread();

}

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  //  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  //  MidiUSB.sendMIDI(noteOn);
  digitalWrite(LED, HIGH); //Turn LED on
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  //  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  //  MidiUSB.sendMIDI(noteOff);
  digitalWrite(LED, LOW); //Turn LED off
}


// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

// Functions to RECEIVE MIDI (MIDIUSB lib)
void MIDIread() {

  midiEventPacket_t rx = MidiUSB.read();

  switch (rx.header) {
    case 0:
      break; //No pending events

    case 0x9:
      handleNoteOn(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //pitch
        rx.byte3         //velocity
      );
      break;
  }
}
