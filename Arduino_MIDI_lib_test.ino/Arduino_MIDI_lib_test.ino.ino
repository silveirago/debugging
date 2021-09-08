#include <MIDI.h>
//MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  MIDI.begin();
  Serial1.begin(115200);
}

void loop() {

  // sends MIDI notes
  //  for (int i = 36; i < 48; i++) {
  //    MIDI.sendNoteOn(i, 127, 1); // note, velocity, channel
  //    delay(300);
  //    MIDI.sendNoteOn(i, 0, 1); // note, velocity, channel
  //  }

  // sends MIDI control change
  for (int i = 1; i < 128; i++) {
    MIDI.sendControlChange(10, 10, 10); // cc number, cc value, channel
    delay(300);
  }

}
