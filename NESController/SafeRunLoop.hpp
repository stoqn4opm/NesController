//
//  SafeRunLoop.hpp
//  NESController
//
//  Created by Stoyan Stoyanov on 28.05.18.
//  Copyright © 2018 Stoyan Stoyanov. All rights reserved.
//

#ifndef SafeRunLoop_hpp
#define SafeRunLoop_hpp

#include "Arduino.h"
#include "HEF4021BP.hpp"

/*
   Here is where the application code will executes
*/

class SafeRunLoop {
  public:
    void run(HEF4021BP shiftRegirter);
};


#endif /* SafeRunLoop_hpp */
