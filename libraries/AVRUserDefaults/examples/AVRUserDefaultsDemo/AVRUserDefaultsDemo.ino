#include <AVRUserDefaults.h>

/*
 * Sample code to show how to use AVRUserDefaults.
 * Think of it as a set of attributes(properties with getters and setters),
 * that are stored in a non volatile memory. ON CHIP ERASE THESE VALUES ARE LOST
 * AND THE WHOLE MEMORY IS FILLED WITH 0xFF.
 */

void setup() {
  // put your setup code here, to run once:
  pinMode(9, INPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, AVRUserDefaults::isBluetoothAlreadyConfigured() ? HIGH : LOW);
}

void loop() {

  if (digitalRead(9) == HIGH) { // use a pull down to LOW
     AVRUserDefaults::setIsBluetoothAlreadyConfigured(true);
  }
}
