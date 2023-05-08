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
  // Do something with the note on message
  digitalWrite(LED, HIGH); //Turn LED on
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  // Do something with the note off message
  digitalWrite(LED, LOW); //Turn LED off
}

void handleControlChange(byte channel, byte control, byte value) {
  // Do something with the control change message
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

// Functions to RECEIVE MIDI (MIDIUSB lib)
void MIDIread() {
  midiEventPacket_t rx = MidiUSB.read();

  switch (rx.header) {
    case 0:
      break; //No pending events

    case 0x8:
      handleNoteOff(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //pitch
        rx.byte3         //velocity
      );
      break;

    case 0x9:
      handleNoteOn(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //pitch
        rx.byte3         //velocity
      );
      break;

    case 0xB:
      handleControlChange(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //control number
        rx.byte3         //control value
      );
      break;

    case 0xC:
      handleProgramChange(
        rx.byte1 & 0xF,  //channel
        rx.byte2         //program number
      );
      break;

    case 0xD:
      handleAftertouch(
        rx.byte1 & 0xF,  //channel
        rx.byte2         //pressure
      );
      break;

    case 0xE:
      {
        int value = (rx.byte3 << 7) | rx.byte2;
        handlePitchBend(
          rx.byte1 & 0xF,  //channel
          value            //pitch bend value
        );
      }
      break;

    case 0xF:
      {
        // The first byte of a system exclusive message is always 0xF0
        if (rx.byte1 == 0xF0) {
          // We have a valid system exclusive message
          byte* data = rx.data;
          unsigned int length = rx.byte2;
          handleSysEx(data, length);
        }
      }
      break;
  }
}
