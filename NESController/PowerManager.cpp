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

PowerManager::PowerManager(int8_t desiredDelay, int8_t checkForState, int8_t initialState, int8_t powerControl, int8_t isCharging, int8_t secondsBeforeAutoShutdown) {
  delayBeforeExecutionInSecs = desiredDelay;
  desiredState = checkForState;
  powerControlPin = powerControl;
  isChargingPin = isCharging;
  startState = initialState;
  autoShutDownDelay = secondsBeforeAutoShutdown;

  pinMode(powerControlPin, OUTPUT);
  pinMode(isChargingPin, INPUT);
  digitalWrite(powerControlPin, LOW);

  isInMiddleOfPattern = false;
  isInMiddleOfAutoShutdown = false;
  isAboutToDie = false;
  initialStateEntered = false;
}

#pragma mark - Shutdown Procedures

void PowerManager::shutdownIfNeeded(int8_t input) {

  if (input == startState) { initialStateEntered = true; }
  if (!initialStateEntered) { return; }

  if (isAboutToDie == true) {
    shutdown(); // just in case
    return;
  }

  autoShutdownIfNeeded(input);

  if (input == desiredState) {
    handleExpectedInput();
  } else {
    breakPattern();
  }
}

void PowerManager::autoShutdownIfNeeded(int8_t input) {
  
  unsigned long currentTime = millis();
  if (isInMiddleOfAutoShutdown && autoShutdownStartTime < currentTime && currentTime - autoShutdownStartTime > autoShutDownDelay * 1000) {
    isInMiddleOfAutoShutdown = false;
    shutdown();
    return;
  }

  if (input == startState) {
    if (!isInMiddleOfAutoShutdown) {
      autoShutdownStartTime = millis();
      isInMiddleOfAutoShutdown = true;
    }
  } else {
    isInMiddleOfAutoShutdown = false;
  }
}


void PowerManager::handleExpectedInput() {

  if (isInMiddleOfPattern) {
    // check if variable overflow occured
    unsigned long currentTime = millis();
    if (currentTime < patternStartTime) {
      breakPattern();
      return;
    }

    // check if pattern is completely recognized
    if ((currentTime - patternStartTime) >= (delayBeforeExecutionInSecs * 1000)) {
      shutdown();
      breakPattern();
    }
  } else {
    // pattern recognition begins
    patternStartTime = millis();
    isInMiddleOfPattern = true;
  }
}

#pragma mark - Helper Methods

void PowerManager::breakPattern() {
  isInMiddleOfPattern = false;
}

void PowerManager::shutdown() {
  initialStateEntered = false;
  isAboutToDie = true;
  digitalWrite(powerControlPin, HIGH);
}

#pragma mark - Computed Variables

bool PowerManager::isCurrentlyCharging() {
  return digitalRead(isChargingPin) == LOW;
}

bool PowerManager::isAboutToShutdown() {
  return isAboutToDie;
}

