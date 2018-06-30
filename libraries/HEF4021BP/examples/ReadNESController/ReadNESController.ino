#include <HEF4021BP.h>

namespace {
  HEF4021BP shiftRegister(26, 27, 28); // (3,4,5); // clock, latch, data
};


void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
	int8_t oldButtonStates = shiftRegister.getButtonStates();	
	shiftRegister.update();
	int8_t buttonStates = shiftRegister.getButtonStates();
	if (oldButtonStates != buttonStates) {
		Serial.println(buttonStates, BIN);
	}
}
