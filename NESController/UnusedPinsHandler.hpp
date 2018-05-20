//
//  UnusedPinsHandler.hpp
//  NESController
//
//  Created by Stoyan Stoyanov on 20.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef UnusedPinsHandler_hpp
#define UnusedPinsHandler_hpp

#include "Arduino.h"

/*
   PART of Atmel's original guideline

   "13.2.6 Unconnected Pins
   If some pins are unused, it is recommended to ensure that these pins have a defined level.
   Even though most of the digital inputs are disabled in the deep sleep modes as described above,
   floating inputs should be avoided to reduce current consumption in all other modes where
   the digital inputs are enabled (Reset, Active mode and Idle mode).
   The simplest method to ensure a defined level of an unused pin, is to enable the internal pull-up.
   In this case, the pull-up will be disabled during reset. If low power consumption during reset is important,
   it is recommended to use an external pull-up or pull-down. Connecting unused pins directly to VCC or GND is not recommended,
   since this may cause excessive currents if the pin is accidentally configured as an output."
*/

class UnusedPinsHandler {
  public:
    UnusedPinsHandler(int8_t pins[], int8_t size);
};

#endif /* UnusedPinsHandler_hpp */
