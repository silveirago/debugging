#include <MIDI.h>
//MIDI_CREATE_DEFAULT_INSTANCE(); // uncomment if the code doensn't compile


void setup() {
  // put your setup code here, to run once:
  delay(1000);
  MIDI.begin();
  Serial.begin(31250);  // use 115200 For Hairless MIDI or 31250 for physical 5-pin MIDI din
}

void loop() {

  // sends MIDI notes
  for (int i = 36; i < 48; i++) {
    MIDI.sendNoteOn(i, 127, 1);  // note, velocity, channel
    delay(300);
    MIDI.sendNoteOn(i, 0, 1);  // note, velocity, channel
    delay(300);
  }

  /*
  // CONTROL CHANGE
    for (int i = 1; i < 128; i++) {
      MIDI.sendControlChange(10, 10, 10); // cc number, cc value, channel
      delay(300);
    }
    */

  /*
  
// PROGRAM CHANGE
for (int i = 0; i < 20; i++) {
MIDI.sendProgramChange(i, 0);
delay(500);
}
*/

  /*
// CHANNEL PRESSURE
for (int i = 0; i < 20; i++) {
MIDI.sendChannelPressure(i, 0);
delay(200);
}
*/

  /*
// AFTER TOUCH
for (int i = 0; i < 20; i++) {
MIDI.sendAfterTouch(i, 127, 0);
delay(200);
}
*/

  /*
// POLYPHONIC AFTER TOUCH
for (int i = 0; i < 20; i++) {
MIDI.sendPolyPressure(i, 127, 0);
delay(200);
}
*/

  /*
// PITCH BEND
for (int i = 0; i < 128; i++) {
int value = i * 128; // pitch bend values range from 0-16383
MIDI.sendPitchBend(value, 0);
delay(50);
}
*/

  /*
// SYSTEM EXCLUSIVE
byte sysexData[] = { 0xF0, 0x7E, 0x7F, 0x06, 0x01, 0xF7 }; // Example data for system exclusive message
MIDI.sendSysEx(sizeof(sysexData), sysexData);
delay(1000);
*/
}
