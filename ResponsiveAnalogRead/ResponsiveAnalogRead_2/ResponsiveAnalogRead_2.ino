#include <ResponsiveAnalogRead.h>

// Create filter object: A0 pin, sleep mode enabled
ResponsiveAnalogRead sensor(A1, true);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(A0);       // Unfiltered value
  sensor.update();                // Update filter
  int filtered = sensor.getValue();

  // Format values with 4 digits (e.g., 0000, 0123, 1023)
  char rawStr[5];
  char filteredStr[5];
  sprintf(rawStr, "%04d", raw);
  sprintf(filteredStr, "%04d", filtered);

  Serial.print("Raw: ");
  Serial.print(rawStr);
  Serial.print("   Filtered: ");
  Serial.println(filteredStr);

  delay(50);
}
