#include <Wire.h>

void setup() {
  delay(2000);  // Give time for USB to initialize
  Serial.begin(9600);
  delay(500);   // Let Serial stabilize

  Serial.println("Scanning I2C devices...");
  Wire.begin();

  bool found = false;

  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Device found at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      found = true;
    }
  }

  if (!found) {
    Serial.println("No I2C devices found.");
  } else {
    Serial.println("Scan complete.");
  }
}

void loop() {
  // Nothing here
}
