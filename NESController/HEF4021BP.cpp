//
//  HEF4021BP.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 22.04.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "HEF4021BP.hpp"

#pragma mark - Constants

//namespace {
//const int8_t A_BUTTON         = 0;
//const int8_t B_BUTTON         = 1;
//const int8_t SELECT_BUTTON    = 2;
//const int8_t START_BUTTON     = 3;
//const int8_t UP_BUTTON        = 4;
//const int8_t DOWN_BUTTON      = 5;
//const int8_t LEFT_BUTTON      = 6;
//const int8_t RIGHT_BUTTON     = 7;
//};

#pragma mark - Constructor

HEF4021BP::HEF4021BP(int8_t clock, int8_t latch, int8_t data) {
  clockPin = clock;
  latchPin = latch;
  dataPin = data;

  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  // Set initial states
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, LOW);
}

#pragma mark - Actions

void HEF4021BP::update() {

  int8_t tempData = 0xFF;

  for (int8_t currentButton = 0; currentButton <= 7; currentButton++) {
    pulse(currentButton == 0 ? latchPin : clockPin);
    clearBitOfTempDataIfNeeded(tempData, currentButton);
  }
  
  buttonStates = tempData;
}

int8_t HEF4021BP::getButtonStates() {
  return buttonStates;
}

#pragma mark - Helpers

void HEF4021BP::pulse(int8_t pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}

void HEF4021BP::clearBitOfTempDataIfNeeded(int8_t &tempData, int8_t bitPosition) {
  if (digitalRead(dataPin) == LOW)
    bitClear(tempData, bitPosition);
}

