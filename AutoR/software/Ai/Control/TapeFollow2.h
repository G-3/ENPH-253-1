#pragma once

#include "ControlMode.h"
#include "../LLRobot.h"

namespace Control{
    class TapeFollow2: public ControlMode{
        private:
            LLRobot::Side currentSide = LLRobot::LEFT;
            int16_t dGain;
            int16_t pGain;
            int16_t base;
            int32_t transitionTime;
            int32_t timestamp;
        public:
            const int THLD_LEFT = 200;
            const int THLD_RIGHT = 200;
            const int HYSTERESIS = 20;
            const int eGain = 70;
            const int eBase = 0;
            TapeFollow2(int16_t dGain, int16_t pGain, int16_t base);
            ~TapeFollow2();
            void step();

    };
}
