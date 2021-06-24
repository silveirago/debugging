  #include <CapacitiveSensor.h>

/*
   CapitiveSense Library Demo Sketch
   Paul Badger 2008
   Uses a high value resistor e.g. 10M between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
*/

byte capSamples = 15;

CapacitiveSensor   cs_7_8 = CapacitiveSensor(7, 8);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup()
{
  //cs_7_8.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(115200);
}

void loop()
{
  long total1 =  cs_7_8.capacitiveSensor(capSamples);

  // tab character for debug windown spacing

  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");
  Serial.println();

  delay(10);                             // arbitrary delay to limit data to serial port
}
