//
//  SlaveBluetooth.hpp
//  strcatTest
//
//  Created by Stoyan Stoyanov on 20.06.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef SlaveBluetooth_hpp
#define SlaveBluetooth_hpp

#include <stdio.h>
#include <CommonBluetooth.h>
#include <AVRUserDefaults.h>

namespace SlaveBluetooth {
    bool initModule();
    void send(CommonBluetooth::BluetoothPacket data, bool sendDeviceState);
}

#endif /* SlaveBluetooth_hpp */
