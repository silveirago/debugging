#include <BLEMidi.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing Bluetooth");
  BLEMidiServer.begin("Advanced MIDI Device"); // Set the name of the BLE MIDI device
  Serial.println("Waiting for connections...");
  // BLEMidiServer.enableDebugging();  // Uncomment to enable debugging output
}

void loop() {
  if (BLEMidiServer.isConnected()) {
    // Send a Note On message (A4, velocity 127)
    Serial.println("Sending Note On");
    BLEMidiServer.noteOn(0, 69, 127);
    delay(1000);

    // Send a Note Off message (A4, velocity 127)
    Serial.println("Sending Note Off");
    BLEMidiServer.noteOff(0, 69, 127);
    delay(1000);

    // Send a Control Change message (Control number 7, value 100)
    Serial.println("Sending Control Change");
    BLEMidiServer.controlChange(0, 7, 100);
    delay(1000);

    // Send a Program Change message (Program number 5)
    Serial.println("Sending Program Change");
    BLEMidiServer.programChange(0, 5);
    delay(1000);

    // Send a Pitch Bend message (center position)
    Serial.println("Sending Pitch Bend");
    BLEMidiServer.pitchBend(0, 8192); // Center position (0x2000)
    delay(1000);

    // Send Aftertouch message (pressure 64)
    Serial.println("Sending Aftertouch");
    BLEMidiServer.afterTouch(0, 64);
    delay(1000);

    // Send a simple SysEx message (Educational use ID)
    byte sysExMessage[] = {0xF0, 0x7D, 0x01, 0x02, 0x03, 0xF7}; // Start, Manufacturer ID, data, End
    Serial.println("Sending SysEx Message");
    BLEMidiServer.sendSysEx(sysExMessage, sizeof(sysExMessage));
    delay(1000);
  }
}
