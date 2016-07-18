#pragma once

#include "World.h"

namespace Event{
    class EDetect{
        private:
            EDetect(){};
            static EDetect *main_instance;
            int count = 0;
        public:
            static EDetect *getInstance();
            void step();
    };
    
    /*
     *  Checks for intersections ahead. 
     *  Will call appropriate handler if front intersection detectors are tripped.
     */
    void checkIntersect();

    void checkBumpers();
};
