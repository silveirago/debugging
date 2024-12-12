//#include <usbMIDI.h>

void setup() {
  Serial.begin(115200); // Initialize serial for debugging
  usbMIDI.setHandleNoteOn(OnNoteOn);   // Set callback for Note On
  usbMIDI.setHandleNoteOff(OnNoteOff); // Set callback for Note Off
  usbMIDI.setHandleControlChange(OnControlChange); // Set callback for Control Change
}

void loop() {
  usbMIDI.read();  // Continuously read incoming MIDI messages
}

// Callback for Note On messages
void OnNoteOn(byte channel, byte note, byte velocity) {
  Serial.print("Note On - Channel: ");
  Serial.print(channel);
  Serial.print(", Note: ");
  Serial.print(note);
  Serial.print(", Velocity: ");
  Serial.println(velocity);
}

// Callback for Note Off messages
void OnNoteOff(byte channel, byte note, byte velocity) {
  Serial.print("Note Off - Channel: ");
  Serial.print(channel);
  Serial.print(", Note: ");
  Serial.print(note);
  Serial.print(", Velocity: ");
  Serial.println(velocity);
}

// Callback for Control Change messages
void OnControlChange(byte channel, byte control, byte value) {
  Serial.print("Control Change - Channel: ");
  Serial.print(channel);
  Serial.print(", Control: ");
  Serial.print(control);
  Serial.print(", Value: ");
  Serial.println(value);
}
