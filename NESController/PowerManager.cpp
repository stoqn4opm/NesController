//
//  PowerManager.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 22.04.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "PowerManager.hpp"

#pragma mark - Singleton Reference

PowerManager::PowerManager() {
    
  pinMode(powerControlPin, OUTPUT);
  digitalWrite(powerControlPin, LOW);

  isInMiddleOfPattern = false;
  isInMiddleOfAutoShutdown = false;
  isAboutToDie = false;
  initialStateEntered = false;
}

PowerManager* PowerManager::instance = 0;

PowerManager* PowerManager::shared() {
    if (instance == 0) {
        instance = new PowerManager();
    }
    return instance;
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
  if (isInMiddleOfAutoShutdown && autoShutdownStartTime < currentTime && currentTime - autoShutdownStartTime > (unsigned long)autoShutDownDelay * 1000) {
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

bool PowerManager::wantsShutdown() {
  return isAboutToDie;
}

