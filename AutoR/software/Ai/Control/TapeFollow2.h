#pragma once

#include "ControlMode.h"
#include "../LLRobot.h"
#include "../Config.h"

namespace Control{
    class TapeFollow2: public ControlMode{
        private:
            LLRobot::Side currentSide = LLRobot::LEFT;
            uint8_t lcdCount=0;
            bool isIntersect;
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
            TapeFollow2(bool isIntersect,
                        int16_t base = Config::driveSpeed,
                        int16_t dGain = Config::TF::dGain, 
                        int16_t pGain = Config::TF::pGain, 
                        int16_t iGain = Config::TF::iGain,
                        int16_t eBase = Config::TF::eBase, 
                        int16_t eGain = Config::TF::eGain,
                        int16_t hysteresis = Config::TF::hysterisis);
            ~TapeFollow2();
            void step();

    };
}
