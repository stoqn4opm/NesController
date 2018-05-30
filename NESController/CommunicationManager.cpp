//
//  CommunicationManager.cpp
//  NESController
//
//  Created by Stoyan Stoyanov on 30.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#include "CommunicationManager.hpp"

#pragma mark - Singleton Reference

CommunicationManager::CommunicationManager() {}

CommunicationManager* CommunicationManager::instance = 0;

CommunicationManager* CommunicationManager::shared() {
    if (instance == 0) {
        instance = new CommunicationManager();
    }
    return instance;
}

#pragma mark - Computed Variables

bool CommunicationManager::isConnected() {
    return true;
}
