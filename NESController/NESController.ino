#include "HEF4021BP.hpp"
#include "PowerManager.hpp"

namespace {
HEF4021BP shiftRegister(2, 3, 4);
PowerManager powerManager(3, 4, 5, 7);
};

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  shiftRegister.update();
  powerManager.shutdownIfNeeded(shiftRegister.getButtonStates());
  if (powerManager.isAboutToShutdown()) { return; }
}
