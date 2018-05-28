//
//  SafeRunLoop.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 28.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "SafeRunLoop.hpp"

#pragma mark - Main Application Loop

/// this will get invoked until the power manager decides that it has to
/// shutdown the microcontroller

void SafeRunLoop::run(HEF4021BP shiftRegister) {
    Serial.println(shiftRegister.getButtonStates(), BIN);
}
