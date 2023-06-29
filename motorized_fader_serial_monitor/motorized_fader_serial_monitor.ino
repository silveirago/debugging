/*
  Open the Serial monitor and input numbers form 0-1023 to move the motorized fader

  by Gustavo Silveira
  go.musiconerd.com
*/

// Arduino Pin Assignments
const int motorDown = 7; // Pin for motor down control
const int motorUp = 8; // Pin for motor up control
const int enableMotor = 9; // Pin for enabling the motor

// Inputs
const int wiper = A0; // Pin for reading the position of the fader
const int touchSend = 7; // Pin for touch send
const int touchReceive = 8; // Pin for touch receive

// Variables
double faderMax = 0; // Variable to store the maximum fader value
double faderMin = 0; // Variable to store the minimum fader value

void setup() {
  Serial.begin(115200); // Initialize serial communication
  pinMode (motorUp, OUTPUT); // Set motorUp pin as output
  pinMode (motorDown, OUTPUT); // Set motorDown pin as output
  pinMode (enableMotor, OUTPUT); // Set enableMotor pin as output
  analogWrite(enableMotor, 255); // Set enableMotor pin to maximum PWM value
  delay(1000); // Delay for 1 second
  calibrateFader(); // Calibrate the fader
}

void loop() {
  // Check if there is data available from the serial monitor
  if (Serial.available() > 0) {
    int state = Serial.parseInt(); // Read the value from the serial monitor
    if (state < analogRead(wiper) - 10 && state > faderMin) {
      digitalWrite(motorDown, HIGH); // Activate motor down
      while (state < analogRead(wiper) - 10) {}; // Wait until the fader reaches the desired state
      digitalWrite(motorDown, LOW); // Deactivate motor down
    }
    else if (state > analogRead(wiper) + 10 && state < faderMax ) {
      digitalWrite(motorUp, HIGH); // Activate motor up
      while (state > analogRead(wiper) + 10) {}; // Wait until the fader reaches the desired state
      digitalWrite(motorUp, LOW); // Deactivate motor up
    }
  }
}

void calibrateFader() {
  digitalWrite(motorUp, HIGH); // Activate motor up
  delay(1000); // Delay for 1 second
  digitalWrite(motorUp, LOW); // Deactivate motor up
  faderMax = analogRead(wiper); // Read and store the maximum fader value
  Serial.print("fader max: "); // Print "fader max: " to the serial monitor
  Serial.println(faderMax); // Print the faderMax value to the serial monitor

  digitalWrite(motorDown, HIGH); // Activate motor down
  delay(1000); // Delay for 1 second
  digitalWrite(motorDown, LOW); // Deactivate motor down
  faderMin = analogRead(wiper); // Read and store the minimum fader value
  Serial.print("fader min: "); // Print "fader min: " to the serial monitor
  Serial.println(faderMin); // Print the faderMin value to the serial monitor
}
