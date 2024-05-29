#include <MIDIUSB.h>

/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(3, 2);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
}

int oldPosition = -999;

void loop() {
  int newPosition = myEnc.read();

  if (newPosition != oldPosition) {

    if (newPosition > 127) {
      newPosition = 127;
      myEnc.write(127);
    }
    if (newPosition < 1) {
      newPosition = 0;
      myEnc.write(0);
    }

    if (newPosition != oldPosition) {
      Serial.println(newPosition);

      controlChange(0, 1, newPosition);  // Channel 0, cc number, cc value
      MidiUSB.flush();
    }

    oldPosition = newPosition;
  }
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = { 0x0B, 0xB0 | channel, control, value };
  MidiUSB.sendMIDI(event);
}