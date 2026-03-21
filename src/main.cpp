#include "functions.h"
#define IR_SEND_PIN 5


void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_SEND_PIN);
}

void loop() {
  Serial.println("Sending Volume Up...");
  
  // Most car remotes use the NEC protocol
  IrSender.sendNEC(0x0, 0x40, 0); 
  delay(500); 
  IrSender.sendNEC(0x0, 0x44, 0); 
  delay(500); 
}