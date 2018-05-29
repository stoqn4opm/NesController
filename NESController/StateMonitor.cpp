//
//  StateMonitor.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 28.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "StateMonitor.hpp"

#pragma mark - Constructor

StateMonitor::StateMonitor(int8_t isChargingPin, int8_t isChargedPin, int8_t stateLedPin) {
  chargingPin = isChargingPin;
  chargedPin = isChargedPin;
  ledPin = stateLedPin;

  pinMode(chargingPin, INPUT);
  pinMode(chargedPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void StateMonitor::update() {
  
}

