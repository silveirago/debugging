// You can choose the latch pin yourself.
const int ShiftPWM_latchPin = 18;

// ** uncomment this part to NOT use the SPI port and change the pin numbers. This is 2.5x slower **
#define SHIFTPWM_NOSPI
const int ShiftPWM_dataPin = 9;
const int ShiftPWM_clockPin = 19;


// If your LED's turn on if the pin is low, set this to true, otherwise set it to false.
const bool ShiftPWM_invertOutputs = false;

// You can enable the option below to shift the PWM phase of each shift register by 8 compared to the previous.
// This will slightly increase the interrupt load, but will prevent all PWM signals from becoming high at the same time.
// This will be a bit easier on your power supply, because the current peaks are distributed.
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!
// Download: https://github.com/elcojacobs/ShiftPWM

unsigned char maxBrightness = 255; // 0-255
unsigned char pwmFrequency = 75;
unsigned int numRegisters = 2; // number of registers
//unsigned int numOutputs = numRegisters * 8;
unsigned int numOutputs = 14;
unsigned int numRGBLeds = numRegisters * 8 / 3;
unsigned int fadingMode = 0; //start with all LED's off.

byte brightness = 0;

void setup() {

  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);

  ShiftPWM.SetAll(0);

  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);

  // SetPinGrouping allows flexibility in LED setup.
  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion

  ShiftPWM.Start(pwmFrequency, maxBrightness);

  //ShiftPWM.SetAll(maxBrightness);

}

void loop() {

  //  for (int i = 0; i < (8 *numRegisters) ; i++) {
  //    ShiftPWM.SetOne(i, maxBrightness);
  //  }
  //  delay(500);

  //  for (int i = 0; i < (8 *numRegisters); i++) {
  //    ShiftPWM.SetAll(0);
  //    ShiftPWM.SetOne(i, maxBrightness);
  //    delay(100);
  //  }

  for (int i = 0; i < numOutputs; i++) {
    ShiftPWM.SetAll(0);
    ShiftPWM.SetOne(i, maxBrightness);
    delay(300);
  }

}
