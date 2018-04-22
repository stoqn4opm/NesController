#include "HEF4021BP.hpp"

namespace {
HEF4021BP shiftRegister(2, 3, 4);
};

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  shiftRegister.update();
}
