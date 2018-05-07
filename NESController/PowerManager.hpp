//
//  PowerManager.hpp
//  NESController
//
//  Created by Stoyan Stoyanov on 07.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef PowerManager_hpp
#define PowerManager_hpp

#include "Arduino.h"

class PowerManager {
  private:
    int8_t desiredState;
    int8_t delayBeforeExecutionInSecs;
    int8_t powerControlPin;
    int8_t isChargingPin;

    unsigned long patternStartTime;
    bool isInMiddleOfPattern;
    bool isAboutToDie;
    
    void breakPattern();
    void shutdown();
  public:
    PowerManager(int8_t desiredDelay, int8_t checkForState, int8_t powerControl, int8_t isCharging);
    void shutdownIfNeeded(int8_t input);
    bool isCurrentlyCharging();
    bool isAboutToShutdown();
};

#endif /* PowerManager_hpp */
