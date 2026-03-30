#include "functions.h"
#include "IRremote.h"

#define IR_SEND_PIN 5
#define MRQ_PIN 2

void setup() {
  Serial.begin(115200);
  setupR2R(MRQ_PIN);
  IrReceiver.begin(IR_SEND_PIN);
}

void loop() {
  Serial.println("R2R Live");
  switch (readI2C(MRQ_PIN))
  {
  case VOL_UP_PRESS:
    IrSender.sendNEC(0x0, int(IrSignals::VOLUME_UP), 0);
    break;
  case VOL_UP_HOLD:
    IrSender.sendNEC(0x0, int(IrSignals::VOLUME_UP), 5);
    break;
  case VOL_DOWN_PRESS:
    IrSender.sendNEC(0x0, int(IrSignals::VOLUME_DOWN), 0);
    break;
  case VOL_DOWN_HOLD:
    IrSender.sendNEC(0x0, int(IrSignals::VOLUME_DOWN), 5);
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
    IrSender.sendNEC(0x0, int(IrSignals::MODE), 0);
    break;
  default:
    break;
  }
}