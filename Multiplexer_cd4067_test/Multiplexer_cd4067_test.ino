#include "Multiplexer4067.h"

// Define s0, s1, s2, s3, and analog signal pin x1
#define s0 9
#define s1 19
#define s2 20
#define s3 21
#define x1 A1  // analog pin connected to the mux output

Multiplexer4067 mplex = Multiplexer4067(s0, s1, s2, s3, x1);

const int N_MUX_PINS = 16; // Total number of multiplexer channels
int muxPin[N_MUX_PINS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

void setup() {
  Serial.begin(115200);
  mplex.begin();

  // Use plain INPUT for analog measurements (remove pull-down)
  pinMode(x1, INPUT_PULLUP);
  
  Serial.println("Starting multiplexer reading...");
}

void loop() {
  readMux();
  //delay(20); // overall delay between full scans
}

// Reads a subset of multiplexer channels and prints the values
void readMux() {
  for (int i = 0; i < 15; i++) {
    // Set the mux to the desired channel via the library (if implemented inside readChannel, this might already happen)
    // Otherwise, ensure the channel is properly set before the reading.
    // For extra settling time, you might add: delay(10);
    //delay(10); // allow the channel to settle
    Serial.print("Channel ");
    Serial.print(muxPin[i]);
    Serial.print(": ");
    Serial.print(mplex.readChannel(muxPin[i]));
    Serial.print("   ");
  }
  Serial.println();
}
