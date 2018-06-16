//
//  AVRUserDefaults.hpp
//  AVRSleep
//
//  Created by Stoyan Stoyanov on 3.06.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef AVRUserDefaults_hpp
#define AVRUserDefaults_hpp

#include "Arduino.h"
#include <avr/eeprom.h>

#pragma mark - Permanent Storage Interface

/*
 * Add New properties/flags in a similar fashion.
 * THE KEY THING TO REMEMBER IS THAT WHEN PROGRAMMING THE FLASH(CODE UPLOAD),
 * AVRDUDE MAKES THE MCU PERFORMS CHIP ERASE AND WHEN IT DOES IT ERASES THE EEPROM
 * MEMORY TOO AND IT FILLS IT WITH 0xFF IN EVERY BYTE
 * 
 * Atmega328p has 1024 bytes EEPROM and each cell's life expectancy is 10 000 - 100 000 writes,
 * so write as less as you can and read as much as you want. (when you want to store something
 * always read that address to check if the value is not the desired one already. On ATMega328p,
 * have atleast 2.2v supply to be on the safe side for a successful write operation.
 * 
 * AVR's always write and read a byte at once and they need address (for 1kB EEPROM addresses are [0 : 1023]) for this
 * and when writing they need the byte to be written to this address.
 */

namespace AVRUserDefaults {
    bool isBluetoothAlreadyConfigured();
    void setIsBluetoothAlreadyConfigured(bool isConfigured);
    
    bool isSlaveAlreadyConfigured();
    void setIsSlaveAlreadyConfigured(bool isConfigured);
}


#endif /* AVRUserDefaults_hpp */

