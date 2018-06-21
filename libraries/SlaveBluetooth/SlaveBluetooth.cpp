//
//  SlaveBluetooth.cpp
//  strcatTest
//
//  Created by Stoyan Stoyanov on 20.06.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "SlaveBluetooth.h"

bool SlaveBluetooth::initModule() {
   
    CommonBluetooth::enterMode(MODE_ATCOMMAND);
    if (CommonBluetooth::sendCommand((signed char *) "AT+ORGL",                  1).isOK == false) { return false; }
    if (CommonBluetooth::sendCommand((signed char *) "AT+RMAAD",                 1).isOK == false) { return false; }
    if (CommonBluetooth::sendCommand((signed char *) "AT+UART=9600,0,0",         1).isOK == false) { return false; }
    if (CommonBluetooth::sendCommand((signed char *) "AT+NAME=NES Controller",   1).isOK == false) { return false; }
    if (CommonBluetooth::sendCommand((signed char *) "AT+PSWD=0000",             1).isOK == false) { return false; }
    if (CommonBluetooth::sendCommand((signed char *) "AT+ROLE=0",                1).isOK == false) { return false; }
    if (CommonBluetooth::sendCommand((signed char *) "AT+CMODE=1",               1).isOK == false) { return false; }
    if (CommonBluetooth::sendCommand((signed char *) "AT+SENM=3,2",              1).isOK == false) { return false; }
    if (CommonBluetooth::sendCommand((signed char *) "AT+CLASS=73F4",            1).isOK == false) { return false; } // custom so that its harder to be discovered
    if (CommonBluetooth::sendCommand((signed char *) "AT+IAC=9E8B33",            1).isOK == false) { return false; } // liac
    
    Serial.end();
    AVRUserDefaults::setIsBluetoothAlreadyConfigured(true);
    return true;
}

void SlaveBluetooth::send(CommonBluetooth::BluetoothPacket data, bool sendDeviceState) {
    data.isPopulated = true;
    if (CommonBluetooth::isConnected() == false) { return; }
    
    uint8_t packet1 = PACKET_TYPE_4;
    packet1 = packet1 | (data.buttonData >> 2);
    Serial.write(packet1);
    
    uint8_t packet2 = PACKET_TYPE_2;
    packet2 = packet2 | ((uint8_t)(data.buttonData << 6) >> 2);
    Serial.write(packet2);
    
    if (sendDeviceState == false) { return; }
    
    uint8_t packet3 = PACKET_TYPE_3;
    packet3 = packet3 | ((uint8_t)(data.deviceState << 2) >> 2);
    Serial.write(packet3);
}
