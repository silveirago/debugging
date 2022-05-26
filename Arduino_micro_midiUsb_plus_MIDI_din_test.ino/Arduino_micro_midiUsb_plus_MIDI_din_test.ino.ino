// This sketch allows the user to send MIDI over USB and through 
// a 5-pin cable using the MIDIUSB and MIDI libraries


#include <MIDI.h>
#include <MIDIUSB.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midi2);


// MIDI init
//MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  //  Set serial baud rate:  31250 for MIDI  /  9600 for debugging
  Serial1.begin(31250);
  midi2.begin(1);                      // Launch MIDI and listen to channel 1
}

void loop() {


  for (int i = 36; i < 48; i++) {
    noteOn(0, i, 127);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    midi2.sendNoteOn(i, 127, 1); // note, velocity, channel
    // Serial1.write("Button 1\n");
    delay(300);

    noteOn(0, i, 0);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    //Serial1.write("Button 2\n");
    midi2.sendNoteOn(i, 0, 1); // note, velocity, channel
  }

 }

/////////////////////////////////////////////
// Arduino (pro)micro midi functions MIDIUSB Library
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
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
