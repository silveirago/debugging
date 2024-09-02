/*
  by Gustavo Silveira | Nerd Musician
  Learn how to build your MIDI controllers: https://go.musiconerd.com/nerd-musician-pro

  This Arduino sketch demonstrates how to send various MIDI messages over USB using the Adafruit TinyUSB and Arduino MIDI libraries. 
  The code initializes a USB MIDI device and then repeatedly sends a sequence of MIDI commands, including Note On, Note Off, Control Change,
  Program Change, and Pitch Bend. Each command is sent on MIDI channel 1 with a short delay between them. 
  This setup is ideal for controlling MIDI-compatible hardware or software, allowing you to test and explore different MIDI message types.

*/

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// USB MIDI object with 1 port
Adafruit_USBD_MIDI usb_midi;

// Create an instance of the Arduino MIDI Library, using usb_midi as the transport layer.
// This will allow us to send and receive MIDI messages over USB.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, usbMIDI);

void setup() {
  // Set the USB MIDI device name as it appears on the computer.
  usb_midi.setStringDescriptor("TinyUSB MIDI");

  // Manual initialization is required on platforms without built-in USB support, such as mbed RP2040.
  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin(0);  // Start the USB device
  }

  // Optional: Set a custom name for the MIDI port.
  // usb_midi.setCableName(1, "MIDI");

  // Initialize the MIDI Library to listen on all MIDI channels (OMNI mode).
  usbMIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  // 1. Send a Note On message
  // This sends a "Note On" message for middle C (MIDI note number 60) on channel 1 with maximum velocity (127).
  usbMIDI.sendNoteOn(60, 127, 1);
  delay(500);

  // 2. Send a Note Off message
  // This sends a "Note Off" message for middle C (MIDI note number 60) on channel 1 with a velocity of 127.
  usbMIDI.sendNoteOff(60, 127, 1);
  delay(500);

  // 3. Send a Polyphonic Aftertouch message
  // This sends an "Aftertouch" message for middle C (MIDI note number 60) with a pressure value of 64 on channel 1.
  usbMIDI.sendPolyPressure(60, 64, 1);
  delay(500);

  // 4. Send a Control Change message
  // This sends a "Control Change" message to modify the Modulation Wheel (controller number 1) to its maximum value (127) on channel 1.
  usbMIDI.sendControlChange(1, 127, 1);  // Control Change 1 is Modulation Wheel
  delay(500);

  // 5. Send a Program Change message
  // This sends a "Program Change" message to select program number 10 on channel 1.
  usbMIDI.sendProgramChange(10, 1);
  delay(500);

  // 6. Send a Channel Aftertouch message
  // This sends a "Channel Aftertouch" message with a pressure value of 64 on channel 1.
  usbMIDI.sendAfterTouch(64, 1);
  delay(500);

  // 7. Send a Pitch Bend message
  // This sends a "Pitch Bend" message with the maximum upward bend on channel 1. The range is -8192 to 8191, where 8191 is the maximum upward bend.
  usbMIDI.sendPitchBend(8191, 1);
  delay(500);

  // 8. Send a System Exclusive (SysEx) message
  // SysEx messages are used to send manufacturer-specific or device-specific data.
  // Here, we're sending an example SysEx message with three data bytes.
  // Uncomment the following lines if you want to use this part of the code.
  // byte sysexData[] = { 0x7D, 0x10, 0x20 };
  // usbMIDI.sendSysEx(sizeof(sysexData), sysexData, true);
  // delay(500);

  // 9. Send a Time Code Quarter Frame message
  // This sends a MIDI Time Code (MTC) Quarter Frame message with type 1 and value 2.
  usbMIDI.sendTimeCodeQuarterFrame(0x01, 0x02);
  delay(500);

  // 10. Send a Song Position Pointer message
  // This sends a "Song Position Pointer" message with a position value of 1024 beats from the start of the song.
  usbMIDI.sendSongPosition(1024);
  delay(500);

  // 11. Send a Song Select message
  // This sends a "Song Select" message to select song number 5.
  usbMIDI.sendSongSelect(5);
  delay(500);

  // 12. Send a Tune Request message
  // This sends a "Tune Request" message, which tells the receiving device to tune its oscillators.
  usbMIDI.sendTuneRequest();
  delay(500);

  // The loop will repeat after all the messages have been sent, creating a sequence of MIDI events.
}
