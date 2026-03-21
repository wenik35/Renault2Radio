#include <Arduino.h>
#include "Wire.h"
#include "IRremote.h"

void sendKeepAlive();
void setupR2R(int MRQ);
void readI2C(int MRQ);