#pragma once

#include <Arduino.h>

void sendKeepAlive();
void setupR2R(int MRQ);
byte readI2C(int MRQ);

// IRremote is included only where needed to avoid duplicate definitions
enum IrSignals {
	BACK_TAKE_CALL = 0x47,
	SKIP_END_CALL = 0x45,
	VOLUME_UP = 0x44,
	VOLUME_DOWN = 0x40,
	MODE = 0x7,
	BAND = 0x46,
	PHONE_SWITCH = 0xD,
	PLAY_PAUSE = 0x9,
	MUTE = 0x46
};

enum WheelButtons {
	VOL_UP_PRESS = 0x03,
	VOL_UP_HOLD = 0x43,
	VOL_DOWN_PRESS = 0x04,
	VOL_DOWN_HOLD = 0x44,
	PAUSE = 0x05,
	SRC_R = 0x01,
	SRC_L = 0x02,
	OK = 0x00
};