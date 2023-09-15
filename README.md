# PlaydateHapticAccessoryProject
A project that makes your Playdate vibrate. PHAP

Breaking it down:
    DEFINE:1:10,100:20,100
    DEFINE:1: This defines a pattern with the ID 2.
    The following pairs represent the gain and timeBase (in tenths of a second) for each frame of the pattern:
        10,100: Start with an intensity of 10 for 1 second.
        20,100: Increase to an intensity of 20 for 1 second.
    PLAY:1
      Plays the pattern
    STOP
      Stops the pattern
