# MIDI and ESP32 Projects

This repository contains various projects for MIDI and ESP32 boards, organized by the libraries they use. Below is a guide to which boards can be used with each library and the corresponding projects.

---

## **1. TinyUSB Library**
The `TinyUSB` library is used for USB-based MIDI communication with Raspberry Pi Pico boards.

### Supported Boards:
- **Raspberry Pi Pico** (RP2040)

### Projects:
- `MIDI_In_Pico_TinyUSB`: Handles MIDI input using the TinyUSB library.
- `MIDI_Out_Pico_TinyUSB`: Handles MIDI output using the TinyUSB library.
- `MIDI_In_Out_Pico_TinyUSB`: Combines MIDI input and output functionality using TinyUSB.
- `MIDI_Pico_bare_minimum`: A minimal example for MIDI communication using TinyUSB.

---

## **2. MIDIUSB Library**
The `MIDIUSB` library provides USB-MIDI communication for Pro Micro boards.

### Supported Boards:
- **Arduino Pro Micro** (ATmega32U4)

### Projects:
- `MIDI_In_ProMicro_MIDIUSB`: Handles MIDI input using the MIDIUSB library.
- `MIDI_In_ProMicro_MIDIUSB_Advanced`: Advanced example of MIDI input using MIDIUSB.
- `MIDI_Out_ProMicro_MIDIUSB`: Handles MIDI output using the MIDIUSB library.

---

## **3. MIDI_Lib_Classic**
This folder includes projects using the classic `MIDI` library or MIDI communication without advanced USB libraries.

### Supported Boards:
- **Arduino Pro Micro** (ATmega32U4)
- **Arduino Uno** (ATmega328P)

### Projects:
- `MIDI_In_ProMicro_MIDI_Lib`: Handles MIDI input using the classic `MIDI` library on Pro Micro.
- `MIDI_Out_ProMicro_MIDI_Lib_MIDIUSB`: Combines MIDI output using MIDI Lib and MIDIUSB.
- `MIDI_In_Uno_MIDI`: Handles MIDI input for Arduino Uno.
- `MIDI_Out_Uno_MIDI`: Handles MIDI output for Arduino Uno.

---

## **4. ESP32_BLE**
The `ESP32_BLE` folder contains projects for Bluetooth Low Energy (BLE) MIDI communication using ESP32 boards.

### Supported Boards:
- **ESP32** (Classic BLE models)

### Projects:
- `ESP-32-BLE`: Basic BLE MIDI example.
- `ESP_32_BLE_Advanced`: Advanced BLE MIDI example with additional features.

---

## **5. ESP32_S3**
The `ESP32_S3` folder contains projects designed specifically for the ESP32-S3 board, which offers improved BLE and USB functionality.

### Supported Boards:
- **ESP32-S3**

### Projects:
- `ESP32-S3`: Example projects optimized for ESP32-S3.
