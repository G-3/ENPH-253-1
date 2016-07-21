#pragma once


#include "LLRobot.h"
namespace Event{
    class EDetect{
        private:
            EDetect(){};
            static EDetect *main_instance;
            int16_t count = 0;
            uint32_t timestamp = 0;
            const int16_t IR_TIME_DELAY = 3000;
            
            //FastSensorSchedule
            const char fSchedule [4]=[IRLB,IRRB,IRLM,IRRB];
            const uint8_t F_LENGHT = 4;
            const uint8_t fCounter=0;
            //SlowSensorSchedule
            sSchedule [2]= [IRLU,IRRU];
            const uint8_t S_LENGHT = 4;
            const uint8_t currentSSensor= 2;

            const uint8_t SLOW_DOWN_FACTOR = 4;
            const uint8_t sCounter = 0;
            uint8_t fLenght
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
