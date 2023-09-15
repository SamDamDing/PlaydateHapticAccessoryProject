# Playdate Haptic Accessory Project
A project that makes your Playdate vibrate. *PHAP*

### This project is very much a work in progress. So far it only works over serial. Not on Playdate quite yet. Proceed at your own risk......

---

# Haptic Feedback Control with Teensy and DA7280

Control and play haptic feedback patterns on a DA7280 haptic driver connected to a Teensy 4.1 microcontroller, using serial commands from a Playdate console.

## Overview

This project allows the user to define and play back haptic feedback patterns on a device equipped with the DA7280 haptic driver. Patterns can be defined with varying intensities and durations, and then played back in response to user input or predefined triggers.

## Features

- **Define Haptic Patterns**: Create custom vibration patterns with varying intensity and duration.
- **Play Patterns**: Trigger the playback of a defined pattern using simple serial commands.
- **Non-blocking Playback**: Patterns are played back without blocking the main execution loop, allowing for smooth and responsive haptic feedback.
  
## How to Use

1. Connect the DA7280 to the Teensy 4.1 using the I2C protocol.
2. Upload the provided code to the Teensy 4.1 using the Arduino IDE.
3. Open a serial connection to the Teensy 4.1, e.g., using the Playdate console or another serial terminal.
4. Define a haptic pattern using the `DEFINE` command:
   ```
   DEFINE:<patternID>:<gain1>,<timeBase1>:<gain2>,<timeBase2>:...
   ```
   - `patternID`: An integer identifier for the pattern.
   - `gain`: Intensity of vibration (0 to 100).
   - `timeBase`: Duration for that intensity in tenths of a second.
5. Play the defined pattern using the `PLAY` command:
   ```
   PLAY:<patternID>
   ```

## Serial Command Examples

- Define a pattern with ID `1` that vibrates at intensity `25` for `2` seconds, then at intensity `50` for `5` seconds:
  ```
  DEFINE:1:25,200:50,500
  ```
- Play the pattern with ID `1`:
  ```
  PLAY:1
  ```
- Stop a pattern with
  ```
  STOP
  ```
## Troubleshooting

- Ensure the baud rate of the serial connection matches the one specified in the code (`115200`).
- If patterns are not playing as expected, check the serial monitor for debug output.

## Dependencies

- DA7280 Haptic Driver Library (provided)

## Future Enhancements

- Implement a non-blocking pattern definition mechanism.
- Extend support for additional haptic drivers.
- Fix bugs
- Make a 3d printed case and a custom pcb probably inspired by the Playdate Camera project.
