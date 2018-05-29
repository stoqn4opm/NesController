//
//  LightPattern.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 29.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "LightPattern.hpp"

#pragma mark - Charging Pattern

ChargingPattern::ChargingPattern(int8_t pinNumber) { pin = pinNumber; pinMode(pin, OUTPUT);};

void ChargingPattern::update() {
    if (!isFirstExecution) return;
    digitalWrite(pin, HIGH);
    isFirstExecution = false;
}

#pragma mark - Charged Pattern

ChargedPattern::ChargedPattern(int8_t pinNumber) { pin = pinNumber; pinMode(pin, OUTPUT);};

void ChargedPattern::update() {
    if (!isFirstExecution) return;
    digitalWrite(pin, LOW);
    isFirstExecution = false;
}

#pragma mark - Connected Pattern

ConnectedPattern::ConnectedPattern(int8_t pinNumber, int8_t verticalCosineTranslation, int timePeriod) {
    pin = pinNumber;
    verticalTranslation = verticalCosineTranslation;
    period = timePeriod;
    pinMode(pin, OUTPUT);
}

void ConnectedPattern::update() {
    int value = 127 * cos(2 * PI / period * millis()) + verticalTranslation;
    if (value < 0) { value = 0; analogWrite(pin, value); return; };
    if (value > 255) { value = 255; analogWrite(pin, value); return; };
    analogWrite(pin, value);
}

#pragma mark - Low Battery

LowBatteryPattern::LowBatteryPattern(int8_t pinNumber, int8_t period) {
    pin = pinNumber;
    pinMode(pin, OUTPUT);
    startTime = millis();
    blinkPerionInSecs = period;
}

void LowBatteryPattern::update() {
    unsigned long currentTime = millis();
    if (currentTime > startTime && currentTime - startTime >= (long)blinkPerionInSecs * 1000) {
        digitalWrite(pin, lastState ? LOW : HIGH);
        lastState = !lastState;
        startTime = currentTime; // so that overflow will never occur
    }
}

#pragma mark - Not Connected Pattern

NotConnectedPattern::NotConnectedPattern(int8_t pinNumber, int8_t delaysTimes, int8_t timesCount) {
    pin = pinNumber;
    *delays = delaysTimes;
    count = timesCount;
    currentDelayIndex = 0;
    pinMode(pin, OUTPUT);
    startTime = millis();
}

void NotConnectedPattern::update() {
    int8_t delay = delays[currentDelayIndex];
    
    unsigned long currentTime = millis();
    if (currentTime > startTime && currentTime - startTime >= (long)delay * 1000) {
        currentDelayIndex = (int8_t)((currentDelayIndex + 1) % count);
        digitalWrite(pin, lastState ? LOW : HIGH);
        lastState = !lastState;
        startTime = currentTime; // so that overflow will never occur
    }
}
