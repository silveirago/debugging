/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

// constants won't change. They're used here to set pin numbers:
const int buttonN = 3; // total number of buttons
const int buttonPin[buttonN] = {5, 18, 19}; // the number of the pushbutton pin
//const int buttonPin[buttonN] = {2}; // the number of the pushbutton pin

// variables will change:
int buttonState[buttonN] = {0};         // variable for reading the pushbutton status

void setup() {
  Serial.begin(115200);
  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:

  for (int i = 0; i < buttonN; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

}

void loop() {
  // read the state of the pushbutton value:

  for (int i = 0; i < buttonN; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
  }

  for (int i = 0; i < buttonN; i++) {
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState[i] == HIGH) {
      Serial.print(i);
      Serial.print(": OFF   ");
    } else {
      Serial.print(i);
      Serial.print(": ON    ");
    }
  }
  Serial.println();
delay(10);
}
