//
//  SafeRunLoop.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 28.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "SafeRunLoop.hpp"
#include "StateMonitor.hpp"

namespace {

  StateMonitor stateMonitor(6, 7, A0, 1); // StateMonitor(int8_t isChargingPin, int8_t isChargedPin, int8_t stateLedPin, int8_t secondsToNextCheck)
};

#pragma mark - Main Application Loop

/// this will get invoked until the power manager decides that it has to
/// shutdown the microcontroller

void SafeRunLoop::run(HEF4021BP shiftRegister) {
    Serial.print(shiftRegister.getButtonStates(), BIN);
    stateMonitor.update();
    Serial.print(" ");
    State state = stateMonitor.getCurrentState();
    Serial.println(state);
}
