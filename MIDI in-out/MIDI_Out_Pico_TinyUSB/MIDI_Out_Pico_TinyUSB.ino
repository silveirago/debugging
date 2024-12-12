#include <Adafruit_TinyUSB_MIDI.h> // https://github.com/silveirago/Adafruit_TinyUSB_MIDI

// Uncomment the line below to enable debug prints
//#define DEBUG_PRINTS

Adafruit_TinyUSB_MIDI MIDI;

int delayTime = 50;

void setup() {
  MIDI.begin();

#ifdef DEBUG_PRINTS
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  while (!Serial) {
    // Wait for Serial to initialize
  }
  Serial.println("MIDI communication started.");
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
    MIDI.sendNoteOn(i, 127, 1);  // note, velocity, channel

    delay(delayTime);

#ifdef DEBUG_PRINTS
    Serial.print("Sending Note Off: Note=");
    Serial.print(i);
    Serial.println(", Velocity=0, Channel=1");
#endif
    MIDI.sendNoteOff(i, 0, 1);  // note, velocity, channel

    delay(delayTime);
  }

  // Send Control Change messages
  for (int i = 1; i < 128; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Control Change: CC Number=10, Value=");
    Serial.print(i);
    Serial.println(", Channel=10");
#endif
    MIDI.sendControlChange(10, i, 10);  // cc number, cc value, channel
    delay(delayTime);
  }

  // Send Program Change messages
  for (int i = 0; i < 128; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Program Change: Program=");
    Serial.print(i);
    Serial.println(", Channel=1");
#endif
    MIDI.sendProgramChange(i, 1);  // program number, channel
    delay(delayTime);
  }

  // Send Pitch Bend messages
  for (int i = -8192; i <= 8191; i += 512) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Pitch Bend: Value=");
    Serial.print(i);
    Serial.println(", Channel=1");
#endif
    MIDI.sendPitchBend(i, 1);  // bend value, channel
    delay(delayTime);
  }

  // Send Channel Pressure messages
  for (int i = 0; i < 128; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Channel Pressure: Pressure=");
    Serial.print(i);
    Serial.println(", Channel=1");
#endif
    MIDI.sendChannelPressure(i, 1);  // pressure value, channel
    delay(delayTime);
  }

  // Send Aftertouch messages
  for (int i = 36; i < 48; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Aftertouch: Note=");
    Serial.print(i);
    Serial.println(", Pressure=64, Channel=1");
#endif
    MIDI.sendAfterTouch(i, 64, 1);  // note, pressure, channel
    delay(delayTime);
  }

  // Send Polyphonic Aftertouch messages
  for (int i = 36; i < 48; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Polyphonic Aftertouch: Note=");
    Serial.print(i);
    Serial.println(", Pressure=64, Channel=1");
#endif
    MIDI.sendPolyPressure(i, 64, 1);  // note, pressure, channel
    delay(delayTime);
  }

  // Send SysEx messages
  uint8_t sysexData[3] = {0x7E, 0x7F, 0x09};  // Example SysEx data
#ifdef DEBUG_PRINTS
  Serial.println("Sending SysEx Message: Data=7E 7F 09");
#endif
  MIDI.sendSysEx(3, sysexData);
  delay(delayTime);

  // Send Time Code Quarter Frame messages
  for (int i = 0; i < 8; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Time Code Quarter Frame: TypeNibble=");
    Serial.print(i);
    Serial.println(", ValueNibble=0");
#endif
    MIDI.sendTimeCodeQuarterFrame(i, 0);
    delay(delayTime);
  }

  // Send Song Position Pointer
  for (int i = 0; i < 16384; i += 128) {  // Value range 0 - 16383
#ifdef DEBUG_PRINTS
    Serial.print("Sending Song Position Pointer: Beats=");
    Serial.println(i);
#endif
    MIDI.sendSongPosition(i);
    delay(delayTime);
  }

  // Send Song Select messages
  for (int i = 0; i < 128; i++) {
#ifdef DEBUG_PRINTS
    Serial.print("Sending Song Select: SongNumber=");
    Serial.println(i);
#endif
    MIDI.sendSongSelect(i);
    delay(delayTime);
  }

  // Send Tune Request message
#ifdef DEBUG_PRINTS
  Serial.println("Sending Tune Request");
#endif
  MIDI.sendTuneRequest();
  delay(delayTime);

  // Send System Real-Time Messages
  // Clock
  for (int i = 0; i < 24; i++) {
#ifdef DEBUG_PRINTS
    Serial.println("Sending Real-Time Clock");
#endif
    MIDI.sendRealTime(0xF8);
    delay(20);  // Send 24 clock messages per quarter note
  }

  // Start
#ifdef DEBUG_PRINTS
  Serial.println("Sending Real-Time Start");
#endif
  MIDI.sendRealTime(0xFA);
  delay(delayTime);

  // Stop
#ifdef DEBUG_PRINTS
  Serial.println("Sending Real-Time Stop");
#endif
  MIDI.sendRealTime(0xFC);
  delay(delayTime);

  // Active Sensing
#ifdef DEBUG_PRINTS
  Serial.println("Sending Real-Time Active Sensing");
#endif
  MIDI.sendRealTime(0xFE);
  delay(delayTime);

  // System Reset
#ifdef DEBUG_PRINTS
  Serial.println("Sending Real-Time System Reset");
#endif
  MIDI.sendRealTime(0xFF);
  delay(delayTime);
}
