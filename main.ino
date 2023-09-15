#include <Wire.h>
#include "Haptic_Driver.h"

Haptic_Driver hapDrive;
const int MAX_PATTERNS = 10; // Maximum number of patterns we can store
int patternCount = 0;
int currentPatternID = -1;
int currentFrame = 0;
unsigned long frameStartTime = 0;

struct HapticPattern {
  uint8_t gain[MAX_PATTERNS];
  uint8_t timeBase[MAX_PATTERNS];
  int length;
};

HapticPattern patterns[MAX_PATTERNS];

void setup(){
  Wire.begin();
  Serial.begin(115200);
  hapDrive.begin();
  hapDrive.defaultMotor();
  hapDrive.enableFreqTrack(false);
  hapDrive.setOperationMode(DRO_MODE);
}

void loop(){
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command.startsWith("DEFINE:")) {
      definePattern(command);
    } else if (command.startsWith("PLAY:")) {
      playPattern(command);
    } else if (command == "STOP") {
      hapDrive.setVibrate(0);
    }
  }
  updatePatternPlayback();
}

void definePattern(String command) {
  // Extract pattern ID
  int colonIndex = command.indexOf(':');
  int secondColonIndex = command.indexOf(':', colonIndex + 1);
  int patternID = command.substring(colonIndex + 1, secondColonIndex).toInt();

  command = command.substring(secondColonIndex + 1);
  patterns[patternID].length = 0;
  
  while (command.length() > 0) {
    // Parse gain and timeBase values
    int gain = command.substring(0, command.indexOf(',')).toInt();
    command = command.substring(command.indexOf(',') + 1);
    int timeBase = command.indexOf(':') != -1 ? command.substring(0, command.indexOf(':')).toInt() : command.toInt();

    // Store them in the pattern structure
    patterns[patternID].gain[patterns[patternID].length] = gain;
    patterns[patternID].timeBase[patterns[patternID].length] = timeBase;
    patterns[patternID].length++;
    
    // Move to the next frame in the command
    int nextFrameIndex = command.indexOf(':');
    if (nextFrameIndex != -1) {
      command = command.substring(nextFrameIndex + 1);
    } else {
      command = "";
    }
  }
  
  // Debug output
  Serial.print("Defined pattern with ID: ");
  Serial.println(patternID);
}

void playPattern(String command) {
  int patternID = command.substring(5).toInt();
  
  // If a new pattern is requested or no pattern is currently playing, start the new pattern
  if (currentPatternID != patternID || currentPatternID == -1) {
    currentPatternID = patternID;
    currentFrame = 0;
    frameStartTime = millis();
    hapDrive.setVibrate(patterns[currentPatternID].gain[currentFrame]);
    Serial.print("Playing frame ");
    Serial.print(currentFrame);
    Serial.print(" with gain ");
    Serial.print(patterns[patternID].gain[currentFrame]);
    Serial.print(" for ");
    Serial.print(patterns[patternID].timeBase[currentFrame] * 10);
    Serial.println(" ms.");

  }
}

void updatePatternPlayback() {
  if (currentPatternID != -1) {
    // Check if the current frame's duration has elapsed
    Serial.print("Time elapsed for frame ");
    Serial.print(currentFrame);
    Serial.print(": ");
    Serial.println(millis() - frameStartTime);

    if (millis() - frameStartTime >= patterns[currentPatternID].timeBase[currentFrame] * 10) {
      // Move to the next frame
      currentFrame++;
      frameStartTime = millis();
      
      // If there are more frames in the pattern, play the next frame
      if (currentFrame >= patterns[currentPatternID].length) {
        hapDrive.setVibrate(0); // Stop vibration
        currentPatternID = -1; // Reset pattern playback
        currentFrame = 0;
        return;
      }

      if (currentFrame < patterns[currentPatternID].length) {
        hapDrive.setVibrate(patterns[currentPatternID].gain[currentFrame]);
      } else {
        // If no more frames in the pattern, stop the vibration and reset pattern playback state
        hapDrive.setVibrate(0);
        currentPatternID = -1;
      }
    }
  }
}

