//
//  StateMonitor.hpp
//  NESController
//
//  Created by Stoyan Stoyanov on 28.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef StateMonitor_hpp
#define StateMonitor_hpp

#include "Arduino.h"
#include "CommunicationManager.hpp"
#include "PowerManager.hpp"
#include "LightPattern.hpp"

#pragma mark - Device States

enum State {
    off,
    notConnected,
    charging,
    connected,
    charged,
    lowBattery
};

#pragma mark - Class Definition

class StateMonitor {
private:
    int8_t chargingPin;
    int8_t chargedPin;
    int8_t ledPin;
    void switchBlinkPatternToState(State state);
    LightPattern *currentBlinkPattern;
    State lastState;
    bool isCharing();
    bool isCharged();
    unsigned long lastCheckTime;
    int8_t checkDelayInSeconds;
public:
    StateMonitor(int8_t isChargingPin, int8_t isChargedPin, int8_t stateLedPin, int8_t secondsToNextCheck);
    State getCurrentState();
    void update();
    
};


#endif /* StateMonitor_hpp */
