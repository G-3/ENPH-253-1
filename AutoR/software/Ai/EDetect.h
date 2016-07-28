#pragma once


#include "LLRobot.h"
using namespace LLRobot::Rel;

namespace Event{
    class EDetect{
        private:
            EDetect(){};
            static EDetect *main_instance;
            uint16_t count = 0;
            uint32_t timestampIR = 0;
            const int16_t IR_TIME_DELAY = 10000;

            uint8_t consecutiveBumps = 0;

            int16_t irCounter = 0;

            uint16_t slowDownCounter = 0;
            const uint8_t SLOW_DOWN_FACTOR = 4;
        public:
            static EDetect *getInstance();
            bool checkBumpers();
            bool checkIntersect();
            bool checkIR();
            void step();
    };
    
    /*
     *  Checks for intersections ahead. 
     *  Will call appropriate handler if front intersection detectors are tripped.
     */
};
