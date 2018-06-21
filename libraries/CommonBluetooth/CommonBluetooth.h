//
//  CommonBluetooth.hpp
//  strcatTest
//
//  Created by Stoyan Stoyanov on 20.06.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef CommonBluetooth_hpp
#define CommonBluetooth_hpp

//MARK: - Configuration

#define BAUD_RATE_ATMODE 38400
#define BAUD_RATE_NORMAL 9600

#define CONNECTION_CHECK_PIN ((uint8_t) 13)
#define MODE_CONTROL_KEY_PIN ((uint8_t) 12)
#define POWER_CONTROL_PIN    ((uint8_t) 9)

#define MAX_MESSAGE_LENGTH  ((uint8_t) 35) // bytes longest messege will be +INQ:98D3:32:2168EC,73F4,FFB7<0D><0A>OK<0D><0A>
#define BL_ADDRESS_LENGTH   ((uint8_t) 15) // bytes: 14 chars address + '\0'
#define BL_BOOT_TIME        3000 // miliseconds

#define MODE_NORMAL    ((uint8_t) 0x00)
#define MODE_ATCOMMAND ((uint8_t) 0x02)
#define MODE_SLEEP     ((uint8_t) 0x01)

//MARK: - Send/Receive Data Packet Types

#define PACKET_TYPE_1 ((uint8_t) 0b00000000) // for future use UNSAFE, because non set uint defaults to 0
#define PACKET_TYPE_2 ((uint8_t) 0b01000000) // used for sending 2 keypresses
#define PACKET_TYPE_3 ((uint8_t) 0b10000000) // used for sending battery percentage
#define PACKET_TYPE_4 ((uint8_t) 0b11000000) // used for sending 6 keypresses

#include "Arduino.h"
#include <Arduino_FreeRTOS.h>

namespace CommonBluetooth {
    
    typedef enum : uint8_t {
        bluetoothInitializing,
        bluetoothConnected,
        bluetoothNotConnected,
        bluetoothOff,
        bluetoothSearching
    } BluetoothState;
    
    static BluetoothState STATE = bluetoothOff;
    
    struct BluetoothPacket {
        uint8_t buttonData;
        uint8_t deviceState;
        bool isPopulated;
    };
    
    struct CommandResult {
        bool isOK;
        size_t byteCount;
        char responce[MAX_MESSAGE_LENGTH];
    };
    
    void enterMode(uint8_t mode);
    CommandResult sendCommand(char command[], int8_t timeOutInSecs);
    bool isConnected();
}

#endif /* CommonBluetooth_hpp */
