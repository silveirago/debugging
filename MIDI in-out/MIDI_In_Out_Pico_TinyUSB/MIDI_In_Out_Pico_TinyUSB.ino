/*
by Gustavo Silveira | Nerd Musician
Learn how to build your MIDI controllers: https://go.musiconerd.com/nerd-musician-pro

This Arduino code is designed to interact with MIDI devices via USB, sending
and receiving MIDI messages using the Adafruit_TinyUSB and Arduino MIDI libraries.
*/

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// USB MIDI object with 1 port
Adafruit_USBD_MIDI usb_midi;

// Create an instance of the Arduino MIDI Library,
// and attach usb_midi as the transport.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, usbMIDI);

#define LED LED_BUILTIN
int ledState = LOW;

// Timing variables
unsigned long previousMillis = 0;
const long interval = 500;  // interval at which to perform MIDI actions (500ms)

void setup() {

  usb_midi.setStringDescriptor("TinyUSB MIDI");

  // Manual begin() is required on core without built-in support e.g. mbed rp2040
  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin(0);
  }

  // Set name for the MIDI port
  //usb_midi.setCableName(1, "MIDI");

  pinMode(LED, OUTPUT);  // Set Arduino board pin 13 to output

  // Initialize the MIDI Library
  usbMIDI.begin(MIDI_CHANNEL_OMNI);

  // Set function to call on MIDI messages received
  usbMIDI.setHandleNoteOn(MyHandleNoteOn);
  usbMIDI.setHandleNoteOff(MyHandleNoteOff);
  usbMIDI.setHandleProgramChange(handleProgramChange);
  usbMIDI.setHandlePitchBend(handlePitchBend);

  Serial.begin(115200);  // Begin serial communication
}

void loop() {

#ifdef TINYUSB_NEED_POLLING_TASK
  TinyUSBDevice.task();
#endif

  if (!TinyUSBDevice.mounted()) {
    return;
  }

  // Continuously check if MIDI data has been received
  usbMIDI.read();

  // Get the current time
  unsigned long currentMillis = millis();

  // Check if it's time to perform MIDI actions (based on the interval)
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Send Note On (C4, velocity 127) and Note Off
    usbMIDI.sendNoteOn(60, 127, 1);
    usbMIDI.sendNoteOff(60, 127, 1);

    // Send Control Change (Modulation Wheel)
    usbMIDI.sendControlChange(1, 127, 1);

    // Send Program Change (Change to program 10 on channel 1)
    usbMIDI.sendProgramChange(10, 1);

    // Send Pitch Bend (Bend pitch up to max)
    usbMIDI.sendPitchBend(8191, 1);

    // Send Polyphonic Aftertouch (C4, pressure 64 on channel 1)
    usbMIDI.sendPolyPressure(60, 64, 1);
  }
}

// Function to blink the LED
void blinkLED() {
  ledState = !ledState;
  digitalWrite(LED, ledState);
}

// MyHandleNoteOn is the function that will be called by the MIDI Library
// when a MIDI NOTE ON message is received.
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
  blinkLED();  // Blink LED when a Note On message is received

  // Print information about the received Note On message
  Serial.print("Note On received: ");
  Serial.print("Channel: ");
  Serial.print(channel);
  Serial.print(" Pitch: ");
  Serial.print(pitch);
  Serial.print(" Velocity: ");
  Serial.println(velocity);
}

// MyHandleNoteOff is the function that will be called by the MIDI Library
// when a MIDI NOTE OFF message is received.
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {
  blinkLED();  // Blink LED when a Note Off message is received

  // Print information about the received Note Off message
  Serial.print("Note Off received: ");
  Serial.print("Channel: ");
  Serial.print(channel);
  Serial.print(" Pitch: ");
  Serial.print(pitch);
  Serial.print(" Velocity: ");
  Serial.println(velocity);
}

void handleProgramChange(byte channel, byte program) {
  blinkLED();  // Blink LED when a Program Change message is received

  // Print information about the received Program Change message
  Serial.print("Program Change received: ");
  Serial.print("Channel: ");
  Serial.print(channel);
  Serial.print(" Program: ");
  Serial.println(program);
}

void handlePitchBend(byte channel, int value) {
  blinkLED();  // Blink LED when a Pitch Bend message is received

  // Print information about the received Pitch Bend message
  Serial.print("Pitch Bend received: ");
  Serial.print("Channel: ");
  Serial.print(channel);
  Serial.print(" Value: ");
  Serial.println(value);
}

void handleSysEx(byte* data, unsigned int length) {
  blinkLED();  // Blink LED when a SysEx message is received

  // Print information about the received SysEx message
  Serial.print("SysEx received: ");
  Serial.print("Length: ");
  Serial.println(length);
  Serial.print("Data: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print(data[i], HEX);
    if (i < length - 1) {
      Serial.print(" ");
    }
  }
  Serial.println();
}
