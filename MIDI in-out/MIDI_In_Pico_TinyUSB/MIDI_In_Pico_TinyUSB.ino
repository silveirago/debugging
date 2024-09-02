/*
by Gustavo Silveira | Nerd Musician
Learn how to build your MIDI controllers: https://go.musiconerd.com/nerd-musician-pro

This Arduino code is designed to interface with MIDI devices via USB using the
Adafruit_TinyUSB and Arduino MIDI libraries. The code listens for various MIDI messages—such
as Note On, Note Off, Program Change, Channel Aftertouch, and Pitch Bend—and
provides visual feedback by blinking the onboard LED each time a message is received. 
Additionally, it prints detailed information about each received message to the serial monitor.
*/


#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Create a new instance of the Arduino MIDI Library,
// and attach usb_midi as the transport.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, usbMIDI);

#define LED LED_BUILTIN
int ledState = LOW;

void setup() {
  pinMode(LED, OUTPUT);  // Set Arduino board pin 13 to output

  usbMIDI.begin(MIDI_CHANNEL_OMNI);                      // Initialize the Midi Library.
  usbMIDI.setHandleNoteOn(MyHandleNoteOn);               // Set function to call on NOTE ON.
  usbMIDI.setHandleNoteOff(MyHandleNoteOff);             // Set function to call on NOTE OFF.
  usbMIDI.setHandleProgramChange(handleProgramChange);   // Set function to call on Program Change.
  usbMIDI.setHandleAfterTouchChannel(handleAftertouch);  // Set function to call on Channel Aftertouch.
  usbMIDI.setHandlePitchBend(handlePitchBend);           // Set function to call on Pitch Bend.


  Serial.begin(115200);  // Set baud rate for MIDI communication
}

void loop() {
  usbMIDI.read();  // Continuously check if MIDI data has been received.
}

// Function to blink the LED
void blinkLED() {
  ledState = !ledState;
  digitalWrite(LED, ledState);
}

// MyHandleNoteOn is the function that will be called by the Midi Library
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

// MyHandleNoteOff is the function that will be called by the Midi Library
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

// Function to handle Program Change messages
void handleProgramChange(byte channel, byte program) {
  blinkLED();  // Blink LED when a Program Change message is received

  // Print information about the received Program Change message
  Serial.print("Program Change received: ");
  Serial.print("Channel: ");
  Serial.print(channel);
  Serial.print(" Program: ");
  Serial.println(program);
}

// Function to handle Aftertouch messages
void handleAftertouch(byte channel, byte pressure) {
  blinkLED();  // Blink LED when an Aftertouch message is received

  // Print information about the received Aftertouch message
  Serial.print("Aftertouch received: ");
  Serial.print("Channel: ");
  Serial.print(channel);
  Serial.print(" Pressure: ");
  Serial.println(pressure);
}

// Function to handle Pitch Bend messages
void handlePitchBend(byte channel, int value) {
  blinkLED();  // Blink LED when a Pitch Bend message is received

  // Print information about the received Pitch Bend message
  Serial.print("Pitch Bend received: ");
  Serial.print("Channel: ");
  Serial.print(channel);
  Serial.print(" Value: ");
  Serial.println(value);
}