//
//  AVRUserDefaults.cpp
//  AVRSleep
//
//  Created by Stoyan Stoyanov on 3.06.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "AVRUserDefaults.h"

//MARK: - Bluetooth Configured

bool AVRUserDefaults::isBluetoothAlreadyConfigured() {
    byte storage;
    eeprom_read_block((void*)&storage, (void*)0, sizeof(storage)); // read container, address, length of the read 
    return storage == 0;
}

void AVRUserDefaults::setIsBluetoothAlreadyConfigured(bool isConfigured) {

    if (isBluetoothAlreadyConfigured() == isConfigured) { return; }
    
    byte record = isConfigured ? 0x00 : 0xFF;
    eeprom_write_block((const void*)&record, (void*)0, sizeof(record)); // value to be written, address, length of the write
}

//MARK: - Slave Found

bool AVRUserDefaults::isSlaveAlreadyConfigured() {
    byte storage;
    eeprom_read_block((void*)&storage, (void*)1, sizeof(storage)); // read container, address, length of the read
    return storage == 0;
}

void AVRUserDefaults::setIsSlaveAlreadyConfigured(bool isConfigured) {
    
    if (isSlaveAlreadyConfigured() == isConfigured) { return; }
    
    byte record = isConfigured ? 0x00 : 0xFF;
    eeprom_write_block((const void*)&record, (void*)1, sizeof(record)); // value to be written, address, length of the write
}
