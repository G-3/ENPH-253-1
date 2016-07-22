#pragma once

#include "ControlMode.h"
#include "../LLRobot.h"

using namespace LLRobot::Rel;

namespace Control{
    class Pickup : public ControlMode{
        public:
            enum Phase {SETUP,ALIGMENT,EXTENSION,CLOSE,RETRACTION,FAIL};
            Pickup(LLRobot::Side side,Phase phase=SETUP);
            ~Pickup();
        void step();
        private:

            const uint16_t CLAW_DELAY = 500; //milliseconds
            const uint16_t SERVO_RATE = 10; //milliseconds per degree
            const int16_t pValuesSize = 0;
            const uint16_t THRESHOLD = 10;
            int16_t pValues[4] = {0,0,0,0};
            int16_t currentPointer = 0;
            uint16_t maxAmp = 0;

            uint16_t motorDirection = true;
            uint16_t motorAmplitude = 80;
            uint16_t motorStepDown = 20;

            Phase currentPhase;
            LLRobot::Side currentSide;
            Claw claw;
            Arm arm;
            ArmTrip at;
            QSD fS;
            QSD mS;
            QSD bS;


            unsigned long extensionTimestamp = 0;
            unsigned long clawTimestamp = 0;


            void updatePValues(int16_t value);
            int16_t readPValue(int16_t stepsBack);


            void setup();
            void alignment();
            void extension();
            void close();
            void retraction();
            void fail();
    };
};
