//
//  UnusedPinsHandler.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 20.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "UnusedPinsHandler.hpp"

#pragma mark - Constructor

UnusedPinsHandler::UnusedPinsHandler(int8_t pins[], int8_t size) {

  // enabling the internal pull up, so that the IC is in stable state
   for (int8_t i = 0; i < size; i++) {
      pinMode(pins[i], INPUT);
      digitalWrite(pins[i], HIGH);
   }
}

