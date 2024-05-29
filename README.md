# Debugging

## Troubleshooting / Finding the Problem

### Start using the codes in this folder.
Test your buttons and potentiometers to see if they are working correctly. They should have a steady response, like HIGH/LOW for buttons and 0-1023 for potentiometers. If they are not working fine with these examples, there might be a problem in your circuit.

### Your code is not compiling
In the IDE, try to read the dialogue box (the black box below the IDE) to understand what the problem is. Sometimes it might seem confusing, but it can give you a good idea of ​​what the issue could be.

- Did you choose the right board?
- Did you choose the right USB port?
- Have you downloaded and installed all libraries correctly?

If you have done everything right so far and still can't find any error, be humble. It's not because you have read your code 10 times that it means you read it correctly. Do not underestimate your tiredness! Take the time to read the code again. Often, it is a different letter that was written, or a missing semicolon (`;`). Search, rest, and search again.

### Your code compiles, but you do not know where the problem is
First, be humble. Do not blame the Arduino, the board, or the computer. The problem is (98% chance) you. In this case, the ideal is to first debug the circuit. You MUST have a multimeter. Use the multimeter to check the continuity of your circuit. First, check the continuity of all the GNDs, 5Vs, and each component. If you find a lack of continuity somewhere, redo the soldering or rearrange the jumpers. If the problem continues, you may have a faulty component.

### You checked your circuit and you're sure it's all right
Debugging the code is more complicated; there is no exact recipe. It requires reading the code line by line to find the possible problem. Often your algorithm is wrong, meaning you are not giving the correct instructions to the Arduino, something is in the wrong order, etc.

In this case, use the serial monitor extensively! Try printing what's coming out of various parts of your code, one at a time. Sometimes you think it should be outputting "10-100", but it's outputting "-2". Why? Then, you'll have to do a mental gymnastics to find out. It can be difficult, but for me, it's one of the nicest parts of the process.

A good practice is to put on paper every task your Arduino is performing and try to simulate the expected outputs, do the calculations, do the "IFs" and see what actually comes out.

### It still does not work, and you're in doubt
Take a step back. If you used a multiplexer and it is not working with your code, try using the library example. If it still does not work, it's because your system has problems. Using the native Arduino and library examples is a better way to test the problem in your circuit or code. If it works there, the problem is your code. If it does not work, the problem is in your circuit!

### The Potentiometer, or any other analog sensor, is sending a signal when it should not
Every potentiometer has an unstable nature. We try to solve this in the code by setting a minimum value that must be changed for an event to happen. In general, this minimum is stored in the variable `varThreshold`. Increase its value and see if it improves.



# Debugging Guide

This repository contains various code examples and tests for troubleshooting and debugging hardware circuits and Arduino projects.

## Getting Started

1. **Clone the Repository**
   ```bash
   git clone https://github.com/silveirago/debugging.git
   cd debugging
   ```

2. **Install Required Libraries**
   Ensure you have all the necessary libraries installed. You can find the required libraries in the respective folders.

3. **Testing Hardware Components**
   - **Buttons and Potentiometers:** Use the provided test codes to check if buttons and potentiometers are functioning correctly. They should give steady responses (HIGH/LOW for buttons and 0-1023 for potentiometers).
   - **Circuit Continuity:** Use a multimeter to check the continuity of GNDs, 5Vs, and each component.

4. **Code Compilation Issues**
   - Check if the correct board and USB port are selected in the Arduino IDE.
   - Ensure all libraries are installed correctly.
   - Read the error messages in the IDE's dialogue box carefully for clues.

5. **Debugging Circuits**
   - Use a multimeter to verify the continuity of the circuit.
   - Ensure all solder joints and connections are secure.
   - Test individual components if a specific part is not working.

6. **Debugging Code**
   - Use the Serial Monitor to print values from different parts of the code to identify where it might be going wrong.
   - Verify the logic and order of operations in your algorithm.

7. **Handling Sensor Noise**
   - Adjust the threshold value in the code to filter out noise from analog sensors like potentiometers.

## Folder Structure

- **74hc595_-_shiftpwm_lib:** Library for shift register control.
- **Addressable led strips:** Examples for controlling addressable LED strips.
- **Average-smoothingSignal:** Code for signal averaging and smoothing.
- **Buttons_test:** Test code for buttons.
- **CapacitiveSensor:** Examples for capacitive sensors.
- **ESP-32-BLE:** Bluetooth Low Energy examples for ESP32.
- **Encoder:** Test code for rotary encoders.
- **MCP23017:** Examples for MCP23017 I/O expander.
- **MIDI in-out:** MIDI input/output examples.
- **MotorizedFader:** Code for motorized faders.
- **Multiplexer_cd4051_test:** Tests for CD4051 multiplexer.
- **Multiplexer_cd4067_test:** Tests for CD4067 multiplexer.
- **Oled_Display_I2C:** I2C OLED display examples.
- **Pots_filtering_test:** Filtering test for potentiometers.
- **ResponsiveAnalogRead:** Library for responsive analog reads.
- **Teensy_MIDI_name:** Examples for Teensy MIDI device names.

For detailed troubleshooting steps and example codes, explore the specific folders in the repository.
