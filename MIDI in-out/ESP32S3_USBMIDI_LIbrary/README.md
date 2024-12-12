# ESP32-S3 MIDI Controller Setup

This repository contains the code and instructions for setting up an ESP32-S3 as a MIDI controller. Follow the steps below to get started.

## Getting Started

### Step 1: Install the ESP32 Boards in Arduino IDE
1. Open **Arduino IDE**.
2. Go to **File > Preferences**.
3. In the **Additional Boards Manager URLs** field, add this link:
   ```
   https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
   ```
   If there are already URLs present, separate them with a comma.
4. Click **OK** to save.

### Step 2: Install the ESP32 Board Package
1. Go to **Tools > Board > Boards Manager**.
2. In the search bar, type **Espressif ESP32**.
3. Locate the **ESP32 by Espressif** package and click **Install**.
4. Wait for the installation to complete.

### Step 3: Connect Your ESP32-S3
1. Use a **USB-C cable** to connect your ESP32-S3 to your computer.
2. Ensure you're using the USB connector labeled **USB** on your board (not the UART connector).

### Step 4: Put the Board in Bootloader Mode
Before uploading the code, follow these steps to put your ESP32-S3 in bootloader mode:
1. Press and hold the **BOOT** button on the ESP32-S3.
2. While holding **BOOT**, press and release the **RST** button.
3. Release the **BOOT** button.

### Step 5: Select the ESP32-S3 in Arduino IDE
1. Go to **Tools > Board**.
2. Navigate to **esp32** and select **ESP32S3 Dev Module**.

### Step 6: Configure the USB Settings
1. Go to **Tools > Port** and select the correct port (e.g., `cu.usbmodem`, not a `wch` or UART port).
2. Set the following options in the **Tools** menu:
   - **USB Firmware MSC on Boot**: Enable
   - **Upload Mode**: Tiny USB
   - **USB Mode**: Tiny USB

### Step 7: Upload MIDI Controller Code
1. Copy the provided MIDI controller code into a new Arduino IDE sketch.
2. Click the **Verify** button to ensure the code compiles without errors.
3. Click the **Upload** button to program your ESP32-S3.

### Step 8: Test the MIDI Controller
1. Open a MIDI monitoring software on your computer, such as:
   - **MIDI-OX** (Windows)
   - **Audio MIDI Setup** (macOS)
   - **QJackCtl** or **aconnect** (Linux)
2. Verify that the ESP32-S3 appears as a MIDI device.
3. Interact with your ESP32-S3 and observe MIDI messages being sent.

## Notes
- Ensure your ESP32-S3 has the appropriate power supply through the USB connection.
- Use the debug prints in the code (enabled with `#define DEBUG_PRINTS 1`) to troubleshoot any issues.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

