#include "HEF4021BP.hpp"
#include "PowerManager.hpp"
#include "UnusedPinsHandler.hpp"
#include "SafeRunLoop.hpp"

namespace {
HEF4021BP shiftRegister(4, 3, 5); // clock, latch, data
PowerManager powerManager(2, 0b1100, 0b0000, 2, 6, 120); // desiredDelay, checkForState, initialState, powerControl, isCharging, secondsBeforeAutoShutdown
SafeRunLoop safeLoop;

int8_t unusedPins[] = {9, 10, 11, 12, 13, A0, A1, A2, A3, A4, A5};
UnusedPinsHandler handler(unusedPins, 12);
};

void setup() {
  Serial.begin(9600);
}

void loop() {

  shiftRegister.update();
  powerManager.shutdownIfNeeded(shiftRegister.getButtonStates());
  if (powerManager.isAboutToShutdown()) { return; }
  safeLoop.run(shiftRegister);
}
