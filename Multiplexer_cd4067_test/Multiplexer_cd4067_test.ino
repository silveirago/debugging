#include "Multiplexer4067.h"

//* Define s0, s1, s2, s3, and x pins
#define s0 25
#define s1 26
#define s2 27
#define s3 28
#define x1 A2 // analog pin of the first mux


Multiplexer4067 mplex = Multiplexer4067(s0, s1, s2, s3, x1);

const int N_MUX_PINS = 16; // total number of components connected to the mux
int muxPin[N_MUX_PINS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; // pins used int the mux


void setup() {

  Serial.begin(115200);
  mplex.begin();

  pinMode(x1, INPUT_PULLUP);

}

void loop() {

  readMux();
  //Serial.println("??");
  delay(50);
}

// Reads the mux pins and prints its values in the serial monitor
void readMux() {

  //  for (int i = 0; i < N_MUX_PINS; i++) {
  //    Serial.print(i);
  //    Serial.print(": ");
  //    //Serial.print(map(mplex.readChannel(i), 0, 1022, 0, 127));
  //    Serial.print(mplex.readChannel(muxPin[i]));
  //    Serial.print("   ");
  //  }

  Serial.print(mplex.readChannel(0));

  Serial.println();
  delay(10);

}
