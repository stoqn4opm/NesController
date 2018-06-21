//
//  CommonBluetooth.cpp
//  strcatTest
//
//  Created by Stoyan Stoyanov on 20.06.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "CommonBluetooth.h"

void CommonBluetooth::enterMode(uint8_t mode) {
    if (mode == MODE_SLEEP) {
        digitalWrite(POWER_CONTROL_PIN, LOW);
        digitalWrite(MODE_CONTROL_KEY_PIN, LOW);
        return;
    }
    
    digitalWrite(POWER_CONTROL_PIN, LOW); // for N Channel mosfet base control
    digitalWrite(MODE_CONTROL_KEY_PIN, mode == MODE_NORMAL ? LOW : HIGH);
    vTaskDelay(10);
    digitalWrite(POWER_CONTROL_PIN, HIGH); // for N Channel mosfet base control
    vTaskDelay(BL_BOOT_TIME); // because i saw it fail on 700
}

CommonBluetooth::CommandResult CommonBluetooth::sendCommand(char command[], int8_t timeOutInSecs) {
    //    delay(300); // works just fine without it but lets be on the safe side
    Serial.end();
    Serial.begin(BAUD_RATE_ATMODE);
    Serial.println(command);
    Serial.flush(); // Waits for the transmission of outgoing serial data to complete.
    
    size_t countOfBytes = 0;
    char responce[MAX_MESSAGE_LENGTH]; // OK\0
    
    Serial.setTimeout(timeOutInSecs * 1000);
    
    do {
        countOfBytes = Serial.readBytesUntil('\n', responce, MAX_MESSAGE_LENGTH - 2);
        responce[countOfBytes] = '\n';
        responce[countOfBytes + 1] = '\0';
    } while (countOfBytes == 0);
    
    Serial.setTimeout(1000);
    
    CommandResult result;
    result.byteCount = countOfBytes;
    
    strcpy(result.responce, responce);
    
    if ((responce[0] != 'O')  ||
        (responce[1] != 'K')  ||
        (responce[2] != '\r') ||
        (responce[3] != '\n')) { result.isOK = false; return result; }
    
    result.isOK = true;
    return result;
}

//MARK: - Computed Variables

bool CommonBluetooth::isConnected() {
    return digitalRead(CONNECTION_CHECK_PIN) == HIGH;
}
