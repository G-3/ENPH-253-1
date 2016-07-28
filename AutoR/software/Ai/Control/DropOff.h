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

            enum Phase {SETUP,EXTENSION,RELEASE,RETRACTION,ONE_EIGHTY_P1,ONE_EIGHTY_P2};
            Phase currentPhase;

            Claw claw;
            Arm arm;
            LLRobot::Side side;

            int32_t extensionTimestamp;
            int32_t releaseTimestamp;
            int32_t retractionTimestamp;

            void setup();
            void extension();
            void release();
            void retraction();
            void oneEightyP1();
            void oneEightyP2();
        public:
            DropOff(LLRobot::Side side);
            ~DropOff();
            void step();
    };
}
