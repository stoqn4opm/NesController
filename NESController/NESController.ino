#include "HEF4021BP.hpp"
#include "PowerManager.hpp"

namespace {
HEF4021BP shiftRegister(4, 3, 5); // clock, latch, data
PowerManager powerManager(2, 0b1100, 0b0000, 2, 7); // desiredDelay, checkForState, initialState, powerControl, isCharging
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
  shiftRegister.update();
  powerManager.shutdownIfNeeded(shiftRegister.getButtonStates());
  if (powerManager.isAboutToShutdown()) { return; }
  Serial.println(shiftRegister.getButtonStates(), BIN);
}
