#include <MIDI.h>
//MIDI_CREATE_DEFAULT_INSTANCE(); // uncomment if the code doensn't compile


void setup() {
  // put your setup code here, to run once:
  delay(1000);
  MIDI.begin();
  Serial.begin(31250); // use 115200 For Hairless MIDI or 31250 for physical 5-pin MIDI din
}

void loop() {

  // sends MIDI notes
  for (int i = 36; i < 48; i++) {
    MIDI.sendNoteOn(i, 127, 1); // note, velocity, channel
    delay(300);
    MIDI.sendNoteOn(i, 0, 1); // note, velocity, channel
    delay(300);
  }

  // sends MIDI control change
  //  for (int i = 1; i < 128; i++) {
  //    MIDI.sendControlChange(10, 10, 10); // cc number, cc value, channel
  //    delay(300);
  //  }

}
