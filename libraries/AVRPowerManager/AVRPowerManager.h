//
//  AVRPowerManager.hpp
//  NESController
//
//  Created by Stoyan Stoyanov on 07.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef AVRPowerManager_hpp
#define AVRPowerManager_hpp

#include "Arduino.h"

class AVRPowerManager {

//MARK: - Configuration

private:
    AVRPowerManager();
    int8_t desiredState                   = 0b1100;
    int8_t startState                     = 0b0000;
    int8_t delayBeforeExecutionInSecs   = 2;
    int8_t autoShutDownDelay            = 120; // seconds

//MARK: - Instance Variables

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
    static AVRPowerManager *instance;
    void waitForStartState(int8_t input);

//MARK: - Public Interface

  public:
    static AVRPowerManager *shared();
    void shutdownIfNeeded(int8_t input);
    bool wantsShutdown();
};

#endif /* AVRPowerManager_hpp */
