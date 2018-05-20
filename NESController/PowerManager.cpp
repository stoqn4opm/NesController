//
//  PowerManager.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 22.04.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//
/*
  int8_t desiredState;
    int8_t delayBeforeExecutionInSecs;
    int8_t powerControlPin;
    int8_t isChargingPin;

    int patternStartTime;
    int currentExecutionTime;
*/
#include "PowerManager.hpp"

#pragma mark - Constructor

PowerManager::PowerManager(int8_t desiredDelay, int8_t checkForState, int8_t initialState, int8_t powerControl, int8_t isCharging) {
  delayBeforeExecutionInSecs = desiredDelay;
  desiredState = checkForState;
  powerControlPin = powerControl;
  isChargingPin = isCharging;
  initialState = initialState;
  
  pinMode(powerControlPin, OUTPUT);
  pinMode(isChargingPin, INPUT);
  digitalWrite(powerControlPin, LOW);

  isInMiddleOfPattern = false;
  isAboutToDie = false;
  initialStateEntered = false;
}

#pragma mark - Shutdown Procedure

void PowerManager::shutdownIfNeeded(int8_t input) {

  if (input == initialState) { initialStateEntered = true; }
  if (!initialStateEntered) { return; }

  if (isAboutToDie == true) {
    shutdown(); // just in case
    return;
  }

  if (input == desiredState) {
    if (isInMiddleOfPattern) {
      unsigned long currentTime = millis();
      // check if variable overflow occured
      if (currentTime < patternStartTime) {
        breakPattern();
        return;
      }

      // check if pattern is completely recognized
      if ((currentTime - patternStartTime) >= (delayBeforeExecutionInSecs * 1000)) {
        shutdown();
        breakPattern();
        isAboutToDie = true;
      }
    } else {
      // pattern recognition begins
      patternStartTime = millis();
      isInMiddleOfPattern = true;
    }
  } else {
    breakPattern();
  }
}

#pragma mark - Helper Methods

void PowerManager::breakPattern() {
  isInMiddleOfPattern = false;
}

void PowerManager::shutdown() {
  initialStateEntered = false;
  digitalWrite(powerControlPin, HIGH);
}

#pragma mark - Computed Variables

bool PowerManager::isCurrentlyCharging() {
  return digitalRead(isChargingPin) == LOW;
}

bool PowerManager::isAboutToShutdown() {
  return isAboutToDie;
}
