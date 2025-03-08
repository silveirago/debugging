#include <Arduino.h>
#include "USBMIDI.h"

// Enable or disable debug prints
//#define DEBUG_PRINTS 1

// Instantiate the USB MIDI class
USBMIDI usbMidi;

const int delayTime = 50;  // Delay time in milliseconds

void setup() {
  // Initialize USB MIDI
  usbMidi.begin();

  // Wait for USB host to initialize
  while (!tud_mounted()) {
    delay(10);
  }

  Serial.begin(115200);

#ifdef DEBUG_PRINTS
  Serial.println("USB MIDI Initialized");
#endif
}

void loop() {  

  // Send MIDI notes from C2 to B2
  for (int i = 36; i < 48; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Note On: Note=");
    Serial.print(i);
    Serial.println(", Velocity=127, Channel=1");
#endif
    usbMidi.noteOn(i, 127, 1);  // note, velocity, channel
    delay(delayTime);

#ifdef DEBUG_PRINTS
    Serial.print("Sending Note Off: Note=");
    Serial.print(i);
    Serial.println(", Velocity=0, Channel=1");
#endif
    usbMidi.noteOff(i, 0, 1);  // note, velocity, channel
    delay(delayTime);
  }

  // Send Control Change messages
  for (int i = 1; i < 128; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Control Change: CC Number=10, Value=");
    Serial.print(i);
    Serial.println(", Channel=10");
#endif
    usbMidi.controlChange(10, i, 10);  // cc number, cc value, channel
    delay(delayTime);
  }

  // Send Program Change messages
  for (int i = 0; i < 128; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Program Change: Program=");
    Serial.print(i);
    Serial.println(", Channel=1");
#endif
    usbMidi.programChange(i, 1);  // program number, channel
    delay(delayTime);
  }

  // Send Pitch Bend messages
  for (int i = -8192; i <= 8191; i += 512) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Pitch Bend: Value=");
    Serial.print(i);
    Serial.println(", Channel=1");
#endif
    usbMidi.pitchBend((int16_t)i, 1);  // Cast `i` to int16_t
    delay(delayTime);
  }

  // Send Channel Pressure messages
  for (int i = 0; i < 128; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Channel Pressure: Pressure=");
    Serial.print(i);
    Serial.println(", Channel=1");
#endif
    usbMidi.channelPressure(i, 1);  // pressure value, channel
    delay(delayTime);
  }

  // Send Polyphonic Aftertouch messages
  for (int i = 36; i < 48; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Polyphonic Aftertouch: Note=");
    Serial.print(i);
    Serial.println(", Pressure=64, Channel=1");
#endif
    usbMidi.polyPressure(i, 64, 1);  // note, pressure, channel
    delay(delayTime);
  }

  // Send SysEx messages
  uint8_t sysexData[3] = { 0x7E, 0x7F, 0x09 };  // Example SysEx data
#ifdef DEBUG_PRINTS
  Serial.println("Sending SysEx Message: Data=7E 7F 09");
#endif
  usbMidi.writePacket((midiEventPacket_t*)sysexData);
  delay(delayTime);

  // Send Real-Time Clock messages
  for (int i = 0; i < 24; i++) {
#ifdef DEBUG_PRINTS
    Serial.println("Sending Real-Time Clock");
#endif
    usbMidi.write(0xF8);  // Clock message
    delay(20);            // Send 24 clock messages per quarter note
  }

  // Send Real-Time Start and Stop messages
#ifdef DEBUG_PRINTS
  Serial.println("Sending Real-Time Start");
#endif
  usbMidi.write(0xFA);  // Start message
  delay(delayTime);

#ifdef DEBUG_PRINTS
  Serial.println("Sending Real-Time Stop");
#endif
  usbMidi.write(0xFC);  // Stop message
  delay(delayTime);
}
