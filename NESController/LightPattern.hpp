//
//  LightPattern.hpp
//  NESController
//
//  Created by Stoyan Stoyanov on 29.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef LightPattern_hpp
#define LightPattern_hpp

#include "Arduino.h"

#pragma mark - Base Class Definition

class LightPattern {
protected: int8_t pin;
public: virtual void update() = 0;
};

#pragma mark - Concrete Classes

class ChargingPattern: public LightPattern {
private: bool isFirstExecution = true;
public:
    ChargingPattern(int8_t pinNumber);
    virtual void update() = 0;
};

class ChargedPattern: public LightPattern {
private: bool isFirstExecution = true;
public:
    ChargedPattern(int8_t pinNumber);
    virtual void update() = 0;
};

class ConnectedPattern: public LightPattern {
private:
    int8_t verticalTranslation;
    int period;
public:
    ConnectedPattern(int8_t pinNumber, int8_t verticalCosineTranslation, int timePeriod);
    virtual void update() = 0;
};

class NotConnectedPattern: public LightPattern {
private:
    int8_t delays[];
    int8_t count;
    int8_t currentDelayIndex;
    unsigned long startTime;
    bool lastState = false;
public:
    NotConnectedPattern(int8_t pinNumber, int8_t delaysTimes, int8_t timesCount);
    virtual void update() = 0;
};

class LowBatteryPattern: public LightPattern {
private:
    unsigned long startTime;
    bool lastState = false;
    int8_t blinkPerionInSecs;
public:
    LowBatteryPattern(int8_t pinNumber, int8_t period);
    virtual void update() = 0;
};

#endif /* LightPattern_hpp */
