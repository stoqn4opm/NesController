//
//  CommunicationManager.hpp
//  NESController
//
//  Created by Stoyan Stoyanov on 30.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef CommunicationManager_hpp
#define CommunicationManager_hpp

#include "Arduino.h"

class CommunicationManager {
private:
    static CommunicationManager *instance;
    CommunicationManager();
public:
    static CommunicationManager *shared();
    bool isConnected();
};

#endif /* CommunicationManager_hpp */
