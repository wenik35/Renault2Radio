#include <Arduino.h>
#include "Wire.h"

const byte ADDR = 0x23;

void sendKeepAlive();
void setupR2R(int MRQ);
byte readI2C(int MRQ);

void sendKeepAlive() {
  Wire.beginTransmission(ADDR);
  Wire.write(0x01);
  Wire.write(0x11);
  Wire.endTransmission();
}

void setupR2R(int MRQ) {
  Wire.begin();
  
  // 8kHz Slow Clock
  TWBR = 0xff;
  TWSR = 0x01;

  pinMode(MRQ, INPUT_PULLUP);
  Serial.println("Tuned Timing Mode: Adding Settling Delays...");
}

byte readI2C(int MRQ) {
  if (digitalRead(MRQ) == LOW) {
    byte data[5];
    
    // --- SETTLING DELAY ---
    // Give the display's slow CPU time to prepare the I2C hardware
    delayMicroseconds(600); 

    if (Wire.requestFrom(ADDR, 2) == 2) {
      byte header = Wire.read();
      byte status = Wire.read();

      if (header == 0x04) {
        // Wait for current pulse to end
        while(digitalRead(MRQ) == LOW); 
        
        // Wait for the "Instant" follow-up pulse
        unsigned long timeout = millis();
        while(digitalRead(MRQ) == HIGH && (millis() - timeout < 100)); 

        if (digitalRead(MRQ) == LOW) {
          // Another settling delay for the second pulse
          delayMicroseconds(600); 

          if (Wire.requestFrom(ADDR, 5) == 5) {
            for(int i=0; i<5; i++) data[i] = Wire.read();

            // Send keep-alive immediately
            sendKeepAlive();

            // Check if the data is valid (not just all 0xFF)
            if (data[0] != 0xFF) {
              Serial.print("SUCCESS: ");
              for(int i=0; i<5; i++) {
                if(data[i] < 0x10) Serial.print("0");
                Serial.print(data[i], HEX);
                Serial.print(" ");
              }
              Serial.println();
            }
          }
        }
      } 
      else if (header == 0x01 && status == 0x00) {
        sendKeepAlive();
      }
    }
    // Final clear to prevent double-triggering
    while (digitalRead(MRQ) == LOW);

    return data[4];
  }
}