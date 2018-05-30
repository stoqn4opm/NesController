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
    
#pragma mark - Configuration
    
private:
    PowerManager();
    int8_t desiredState                   = 0b1100;
    int8_t startState                     = 0b0000;
    int8_t delayBeforeExecutionInSecs   = 2;
    int8_t powerControlPin              = 2;
    int8_t autoShutDownDelay            = 120; // seconds
    
#pragma mark - Instance Variables

protected:
    unsigned long patternStartTime;
    unsigned long autoShutdownStartTime;
    bool isInMiddleOfPattern;
    bool isInMiddleOfAutoShutdown;
    bool isAboutToDie;
    bool initialStateEntered;
    void breakPattern();
    void shutdown();
    void handleExpectedInput();
    void autoShutdownIfNeeded(int8_t input);
    static PowerManager *instance;

#pragma mark - Public Interface
    
public:
    static PowerManager *shared();
    void shutdownIfNeeded(int8_t input);
    bool wantsShutdown();
};

#endif /* PowerManager_hpp */
