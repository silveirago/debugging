#include <ResponsiveAnalogRead.h> // https://github.com/dxinteractive/ResponsiveAnalogRead

const byte N_POTS_ARDUINO = 1;
const byte POT_ARDUINO_PIN[N_POTS_ARDUINO] = {A0}; //* pins of each pot connected straight to the Arduino

// make a ResponsiveAnalogRead object, pass in the pin, and either true or false depending on if you want sleep enabled
// enabling sleep will cause values to take less time to stop changing and potentially stop changing more abruptly,
// where as disabling sleep will cause values to ease into their correct position smoothly and more accurately

float snapMultiplier = 0.01;
ResponsiveAnalogRead responsivePot[N_POTS_ARDUINO] = {
  ResponsiveAnalogRead(0, true, snapMultiplier),
  //ResponsiveAnalogRead(0, true, snapMultiplier)
};

// the next optional argument is snapMultiplier, which is set to 0.01 by default
// you can pass it a value from 0 to 1 that controls the amount of easing
// increase this to lessen the amount of easing (such as 0.1) and make the responsive values more responsive
// but doing so may cause more noise to seep through if sleep is not enabled

void setup() {

  Serial.begin(115200);

}

void loop() {

  for (int i = 0; i < N_POTS_ARDUINO; i++) {
    // update the ResponsiveAnalogRead object every loop
    int reading = analogRead(POT_ARDUINO_PIN[i]);
    responsivePot[i].update(reading);
    Serial.print("Raw:");
    Serial.print(reading);
    Serial.print("  Responsive:");
    Serial.print(responsivePot[i].getValue());
    Serial.print("  MIDI:");
    Serial.print(responsivePot[i].getValue() >> 3);
    //Serial.print(map(responsivePot[i].getValue(), 0, 1023, 0, 127));
    Serial.print("  | ");
  }

//  for (int i = 0; i < N_POTS_ARDUINO; i++) {
//    Serial.print(responsivePot[i].getValue() >> 3);
//    //Serial.print(map(responsivePot[i].getValue(), 0, 1023, 0, 127));
//    Serial.print("  ");
//  }

  Serial.println();

}
