//
//  StateMonitor.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 28.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "StateMonitor.hpp"

#pragma mark - Constructor

StateMonitor::StateMonitor(int8_t isChargingPin, int8_t isChargedPin, int8_t stateLedPin, int8_t secondsToNextCheck) {
    chargingPin = isChargingPin;
    chargedPin = isChargedPin;
    ledPin = stateLedPin;
    lastCheckTime = millis();
    checkDelayInSeconds = secondsToNextCheck;
    pinMode(chargingPin, INPUT);
    pinMode(chargedPin, INPUT);
    lastState = getCurrentState();
    switchBlinkPatternToState(lastState);
}

#pragma mark - Helpers

bool StateMonitor::isCharing() { return digitalRead(chargingPin) == LOW && digitalRead(chargedPin) == HIGH; }
bool StateMonitor::isCharged() { return digitalRead(chargingPin) == LOW && digitalRead(chargedPin) == LOW; }

State StateMonitor::getCurrentState() {
    if (isCharing()) return charging;
    if (isCharged()) return charged;
    if (PowerManager::shared()->wantsShutdown()) return off;
    return CommunicationManager::shared()->isConnected() ? connected : notConnected;
}

void StateMonitor::switchBlinkPatternToState(State state) {
    
    switch (state) {
        case off:           currentBlinkPattern = new OffPattern(ledPin); break;
        case notConnected:  currentBlinkPattern = new NotConnectedPattern(ledPin, 1, 1); break; // update later
        case charging:      currentBlinkPattern = new ChargingPattern(ledPin); break;
        case connected:     currentBlinkPattern = new ConnectedPattern(ledPin, -80, 10000); break;
        case charged:       currentBlinkPattern = new ChargedPattern(ledPin); break;
        case lowBattery:    currentBlinkPattern = new LowBatteryPattern(ledPin, 1); break;
        default:            currentBlinkPattern = new OffPattern(ledPin); break;
    }
}

#pragma mark - Update Loop

void StateMonitor::update() {
    unsigned long currentTime = millis();
    currentBlinkPattern->update();
    if (currentTime > lastCheckTime && currentTime - lastCheckTime >= (long)checkDelayInSeconds * 1000) {
        lastCheckTime = currentTime;
        State currentState = getCurrentState();
        if (currentState == lastState) return;
        switchBlinkPatternToState(currentState);
        lastState = currentState;
    }
    
    // in case of overload (reachable after 50 days)
    if (currentTime < lastCheckTime) {
        lastCheckTime = currentTime;
    }
}
