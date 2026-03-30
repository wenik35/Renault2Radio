#include "functions.h"
#include "IRremote.h"

#define IR_SEND_PIN 5
#define MRQ_PIN 10

void setup() {
  Serial.begin(115200);
  setupR2R(MRQ_PIN);
  IrSender.begin(IR_SEND_PIN);
}

void loop() {
  switch (readI2C(MRQ_PIN))
  {
  case VOL_UP_PRESS:
    IrSender.sendNEC(0x0, int(IrSignals::VOLUME_UP), 0);
    break;
  case VOL_UP_HOLD:
    for (int i = 0; i < 5; i++) {
      IrSender.sendNEC(0x0, int(IrSignals::VOLUME_UP), 0);
      delay(200); // Short delay between repeats
    }
    break;
  case VOL_DOWN_PRESS:
    IrSender.sendNEC(0x0, int(IrSignals::VOLUME_DOWN), 0);
    break;
  case VOL_DOWN_HOLD:
    for (int i = 0; i < 5; i++) {
      IrSender.sendNEC(0x0, int(IrSignals::VOLUME_DOWN), 0);
      delay(200); // Short delay between repeats
    }
    break;
  case PAUSE:
    IrSender.sendNEC(0x0, int(IrSignals::PLAY_PAUSE), 0);
    break;
  case SRC_R:
    IrSender.sendNEC(0x0, int(IrSignals::SKIP_END_CALL), 0);
    break;
  case SRC_L:
    IrSender.sendNEC(0x0, int(IrSignals::BACK_TAKE_CALL), 0);
    break;
  case OK:
    IrSender.sendNEC(0x0, int(IrSignals::PLAY_PAUSE), 0);
    break;
  default:
    break;
  }
}