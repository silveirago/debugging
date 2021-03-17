#include <Average.h>

int analogPin = A0;

// Reserve space for 10 entries in the average bucket.
// Change the type between < and > to change the entire way the library works.
Average<float> ave(10);

void setup() {
    Serial.begin(115200);
}

void loop() {
    int minat = 0;
    int maxat = 0;
    
    // Add a new random value to the bucket
    ave.push(analogRead(analogPin));

    // Display the current data set
//    for (int i = 0; i < 10; i++) {
//        Serial.print(ave.get(i));
//        Serial.print(" ");
//    }
//    Serial.println();

    // And show some interesting results.
    Serial.print("Raw:   "); Serial.print(analogRead(analogPin));
    Serial.print("  | Mean:   "); Serial.print(ave.mean());
    Serial.print("  | Mode:   "); Serial.print(ave.mode());
    Serial.print("  | Max:    "); Serial.print(ave.maximum(&maxat));
    Serial.print(" at:    "); Serial.print(maxat);
    Serial.print("   | Min:    "); Serial.print(ave.minimum(&minat));
    Serial.print(" at:    "); Serial.print(minat);
    Serial.print("  | StdDev: "); Serial.println(ave.stddev());
    delay(15);
}
