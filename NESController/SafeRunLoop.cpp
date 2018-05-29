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

  StateMonitor stateMonitor(6, 7, 8); // StateMonitor(int8_t isChargingPin, int8_t isChargedPin, int8_t stateLedPin)
};

#pragma mark - Main Application Loop

/// this will get invoked until the power manager decides that it has to
/// shutdown the microcontroller

void SafeRunLoop::run(HEF4021BP shiftRegister) {
    Serial.print(shiftRegister.getButtonStates(), BIN);
    pinMode(6, INPUT);
    bool isCharging = digitalRead(6) == LOW;
    Serial.print(" ");
    Serial.println(isCharging);
}
