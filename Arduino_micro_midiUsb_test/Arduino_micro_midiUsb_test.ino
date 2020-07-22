#include "MIDIUSB.h"

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  for (int i = 36; i < 48; i++) {
    noteOn(0, i, 127);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    delay(300);
    noteOn(0, i, 0);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
  }

}

/////////////////////////////////////////////
// Arduino (pro)micro midi functions MIDIUSB Library
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
