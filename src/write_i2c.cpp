#include "functions.h"

const int MRQ = 2;
const byte ADDR = 0x23;

// Display State
char currentDisplayText[9] = "        "; 
char nextDisplayText[9]    = "START   ";
bool textNeedsUpdate = true;

// The 8-byte magic header
byte displayHeader[] = {0x0F, 0x90, 0x7F, 0x55, 0xFF, 0x3F, 0x60, 0x81};

// Function to update the buffer (call this anywhere in your logic)
void updateText(const char* newText) {
  strncpy(nextDisplayText, newText, 8);
  nextDisplayText[8] = '\0'; // Ensure null termination
  textNeedsUpdate = true;
}

void writeText() {
    // 1. Monitor the MRQ line
  if (digitalRead(MRQ) == LOW) {
    delayMicroseconds(600); // The "Tuned" delay we found earlier

    if (textNeedsUpdate) {
      // --- SEND TEXT FRAME ---
      Wire.beginTransmission(ADDR);
      for(int i = 0; i < 8; i++) Wire.write(displayHeader[i]);
      
      for(int i = 0; i < 8; i++) {
        if(i < strlen(nextDisplayText)) Wire.write(nextDisplayText[i]);
        else Wire.write(0x20); // Pad with spaces
      }
      
      if(Wire.endTransmission() == 0) {
        strcpy(currentDisplayText, nextDisplayText);
        textNeedsUpdate = false;
        Serial.print("Updated Display: ");
        Serial.println(currentDisplayText);
      }
    } 
    else {
      // --- SEND KEEP-ALIVE (HEARTBEAT) ---
      // This keeps the display from timing out
      Wire.beginTransmission(ADDR);
      Wire.write(0x01);
      Wire.write(0x11);
      Wire.endTransmission();
    }

    // Wait for pulse to end
    while(digitalRead(MRQ) == LOW);
  }
}

void example_loop() {
  // Example: Cycle text every 2 seconds
  static unsigned long lastChange = 0;
  static int toggle = 0;
  if (millis() - lastChange > 2000) {
    if (toggle == 0) updateText("HELLO   ");
    else if (toggle == 1) updateText("RENAULT ");
    else if (toggle == 2) updateText("LAGUNA  ");
    else if (toggle == 3) updateText("SPOTIFY ");
    
    toggle = (toggle + 1) % 4;
    lastChange = millis();
  }
}