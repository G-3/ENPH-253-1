#pragma once

#include "ControlMode.h"
#include "../LLRobot.h"

namespace Control{
    class TapeFollow2: public ControlMode{
        private:
            LLRobot::Side currentSide = LLRobot::LEFT;
            uint8_t lcdCount=0;
            int16_t dGain;
            int16_t pGain;
            int16_t iGain;
            int16_t base;
            int16_t eGain;
            int16_t eBase;
            int16_t hysteresis;
            uint32_t transitionTimeRight;
            uint32_t transitionTimeLeft;
            uint32_t timestamp;
            float integral;
        public:
            const int THLD_LEFT = 200;
            const int THLD_RIGHT = 200;
            TapeFollow2(int16_t dGain, int16_t pGain, int16_t base,int16_t iGain = 10,int16_t eBase = 30, int16_t eGain = 70,int16_t hysteresis = 10);
            ~TapeFollow2();
            void step();

    };
}
