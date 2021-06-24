/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int potN = 1; // total number of pots
const int analogInPin[potN] = {A0}; // Analog input pin that the potentiometers are attached to

int sensorValue[potN] = {0};        // value read from the pot
int sensorPValue[potN] = {0};        // previous val
int potVar[potN] = {0};        // previous val

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);

  //pinMode(A1, INPUT_PULLUP);

  //  for (int i = 0; i < potN; i++) {
  //    pinMode(analogInPin[i], INPUT_PULLUP);
  //  }

}

void loop() {

  // read the analog in value:
  for (int i = 0; i < potN; i++) {
    //sensorValue[i] = analogRead(analogInPin[i]);

    // one pole filter
    // y[n] = A0 * x[n] + B1 * y[n-1];
    // A = 0.15 and B = 0.85
    int reading = analogRead(analogInPin[i]);
    float filteredVal = 0.5 * reading + 0.5 * sensorPValue[i];
    sensorValue[i] = filteredVal;

    potVar[i] = abs(sensorValue[i] - sensorPValue[i]);
    sensorPValue[i] = sensorValue[i];
  }


  // print the results to the Serial Monitor:
  for (int i = 0; i < potN; i++) {
    Serial.print(i);
    Serial.print(": ");
    //Serial.print(sensorValue[i]);
    Serial.print(sensorPValue[i]);
    Serial.print("    ");

  }
  Serial.println();

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
