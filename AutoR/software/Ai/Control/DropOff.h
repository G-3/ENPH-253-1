#pragma once 
#include "ControlMode.h"
#include "../LLRobot.h"

using namespace LLRobot::Rel;

namespace Control{
    class DropOff : public ControlMode{
        private:
            //All values in milliseconds
            const int EXTENSION_DELAY = 500;
            const int RELEASE_DELAY = 500;
            const int RETRACTION_DELAY= 500;

            enum Phase {SETUP,EXTENSION,RELEASE,RETRACTION};
            Phase currentPhase;

            Claw claw;
            Arm arm;

            int16_t extensionTimestamp;
            int16_t releaseTimestamp;
            int16_t retractionTimestamp;

            void setup();
            void extension();
            void release();
            void retraction();
        public:
            DropOff(LLRobot::Side side);
            ~DropOff();
            void step();

    };
}
