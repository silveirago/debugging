/*

  The purpose of this code is to read the state of multiple rotary encoders and track the position of each encoder by counting
  the number of times the encoder has been turned.
  The code uses the Adafruit_MCP23X17 library to interface with the MCP23017 I2C port expander,
  which is used to read the state of the encoder pins. The number of encoders and the pin assignments for each encoder are defined
  by the ENCODER_N and encoderPin variables respectively.

  The loop function iterates through all the encoders defined by ENCODER_N and calls the readEncoder function for each encoder.
  The readEncoder function first reads the state of the A and B channel of the encoder, then it compares the current state of
  the A channel with the previous state stored in lastEncoderA[encIndex]. If the state of the A channel has changed and it is
  now LOW, the function checks the state of the B channel. If the state of B channel is also LOW, the count for this encoder is
  decremented, otherwise it is incremented. The previous state of the A channel is updated to the current state, and if the count
  has changed since the last reading, it is printed to the serial monitor along with the encoder number.

  This code will output the current position of the encoder in the format "Encoder [encoder number]: [current count]" every time the encoder position changes.

*/

#include <Adafruit_MCP23X17.h>  // Include the Adafruit_MCP23X17 library
Adafruit_MCP23X17 mcp;          // Create an instance of the Adafruit_MCP23X17 class

const int I2C_ADDRESS = 0x20;  // MCP23017 I2C address

const int ENCODER_N = 6;                                                                          // Number of encoders used
int encoderPin[ENCODER_N][2] = { { 0, 1 }, { 2, 3 }, { 4, 5 }, { 6, 7 }, { 8, 9 }, { 10, 11 } };  // Pin numbers for the A and B channels of each encoder

int count[ENCODER_N] = { 0 };      // Current count of each encoder
int lastCount[ENCODER_N] = { 0 };  // Previous count of each encoder

int encoderA[ENCODER_N] = { 0 };         // Current state of the A channel of each encoder
int encoderB[ENCODER_N] = { 0 };         // Current state of the B channel of each encoder
int lastEncoderA[ENCODER_N] = { HIGH };  // Previous state of the A channel of each encoder
int lastEncoderB[ENCODER_N] = { HIGH };  // Previous state of the B channel of each encoder

void setup() {

  Serial.begin(9600);

  while (!Serial) {
    Serial.println("waiting...");
  }
  Serial.println();

  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C(I2C_ADDRESS, &Wire)) {  // Wire1 or Wire
    //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("MCP23017 Error.");
    while (1)
      ;
  } else {
    Serial.println("MCP23017 Success.");
  }

  // Set the pin mode of each encoder pin to INPUT_PULLUP
  for (int i = 0; i < ENCODER_N; i++) {
    for (int j = 0; j < 2; j++) {
      mcp.pinMode(encoderPin[i][j], INPUT_PULLUP);
    }
  }

  Serial.begin(9600);  // Start serial communication
}

void loop() {

  for (int i = 0; i < ENCODER_N; i++) {
    readEncoder(i);  // Call the readEncoder function for each encoder | uses polling (slower)
  }
}

void readEncoder(int encIndex) {
  int encoderA = mcp.digitalRead(encoderPin[encIndex][0]);  // Read the state of the A channel of the current encoder
  int encoderB = mcp.digitalRead(encoderPin[encIndex][1]);  // Read the state of the B channel of the current encoder

  if (encoderA != lastEncoderA[encIndex]) {  // Check if the state of the A channel has changed
    if (encoderA == LOW) {                   // If the state of the A channel is LOW
      if (encoderB == LOW) {                 // If the state of the B channel is also LOW
        count[encIndex]--;                   // Decrement the count for this encoder
      } else {
        count[encIndex]++;  // Otherwise, increment the count for this encoder
      }
    }
    lastEncoderA[encIndex] = encoderA;  // Update the previous state of the A channel
  }
  if (count[encIndex] != lastCount[encIndex]) {  // If the count has changed
    Serial.print("Encoder [");                   // Print the encoder number
    Serial.print(encIndex);
    Serial.print("]: ");
    Serial.println(count[encIndex]);        // Print the current count
    lastCount[encIndex] = count[encIndex];  // Update the previous count
  }
}

/*
  The Difference between polling and using interrupts

  Polling involves continuously checking the state of the encoder in the main loop of the program.
  This is done by repeatedly calling a function that reads the state of the encoder and updates the
  count of the encoder's position. The main loop runs as fast as possible, so it will check the state
  of the encoder as quickly as it can. This method is simple to implement, but it can cause the processor
  to spend a lot of time reading the encoder, which can affect the performance of other tasks.

  Interrupts, on the other hand, allow the processor to go into a low-power mode and wait for an external
  event to happen. In the case of an encoder, the processor can wait for a change in the encoder's state to
  occur. When a change in the encoder's state is detected, an interrupt is triggered, and the processor wakes
  up to execute an interrupt service routine (ISR) that reads the state of the encoder and updates the count of
  the encoder's position. This method is more efficient, as the processor doesn't spend as much time reading the
  encoder, but it can be more complex to implement.

  In summary, polling is simpler to implement but may not be as efficient as using interrupts. On the other hand,
  using interrupts is more efficient but requires more code to set up and manage the interrupts.
*/
