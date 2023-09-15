# PlaydateHapticAccessoryProject
A project that makes your Playdate vibrate. *PHAP*

### This project is very much a work in progress. Proceed at your own risk......

# Breaking it down:

``DEFINE:1:10,100:20,100``
    
    DEFINE:1: This defines a pattern with the ID 1.
    The following pairs represent the gain and timeBase (in tenths of a second) for each frame of the pattern:
        10,100: Start with an intensity of 10 for 1 second.
        20,100: Increase to an intensity of 20 for 1 second.
``PLAY:1``

    Plays the pattern with the ID 1.
``STOP``

    Stops the pattern.

# Requirements:

* Teensy 4.1 (Possibly overkill. An STM32 with usb hosting might work.
* Sparkfun LRA DA7280
* Some jumper wires
* A female usb port breakout board
* A power source for the Teensy 4.1
* The arduino library for the LRA DA7280
