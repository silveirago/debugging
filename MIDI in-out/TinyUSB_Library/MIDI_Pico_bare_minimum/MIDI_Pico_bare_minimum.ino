#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup(){}
void loop(){}
#else

#include <Adafruit_TinyUSB_MIDI.h>

// Uncomment the line below to enable debug prints
//#define DEBUG_PRINTS

Adafruit_TinyUSB_MIDI MIDI;

void setup() {
  MIDI.begin();

#ifdef DEBUG_PRINTS
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  while (!Serial) {
    // Wait for Serial to initialize
  }
  Serial.println("MIDI communication started.");
#endif
}

void loop() {
}

#endif /* ARDUINO_USB_MODE */