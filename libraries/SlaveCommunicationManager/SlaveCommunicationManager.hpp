//
//  SlaveCommunicationManager.hpp
//  AVRSleep
//
//  Created by Stoyan Stoyanov on 6.06.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef SlaveCommunicationManager_hpp
#define SlaveCommunicationManager_hpp

#include <BaseCommunicationManager.hpp>

class SlaveCommunicationManager: BaseCommunicationManager {
private:
    SlaveCommunicationManager();
protected:
    virtual bool performModuleInit();
public:
    static BaseCommunicationManager *shared();
    void update();
};

#endif /* SlaveCommunicationManager_hpp */
