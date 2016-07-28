#pragma once

#include "ControlMode.h"
#include "../LLRobot.h"

using namespace LLRobot::Rel;

namespace Control{
    class Pickup : public ControlMode{
        public:
            enum Phase {SETUP,ALIGMENT,EXTENSION,CLOSE,RETRACTION,FAIL,REFIND_TAPE,ONE_EIGHTY_P1,ONE_EIGHTY_P2};
            Pickup(LLRobot::Side side,Phase phase=SETUP);
            ~Pickup();
        void step();
        private:
            const uint16_t CLAW_DELAY = 500; //milliseconds
            const uint16_t SERVO_RATE = 15; //milliseconds per degree
            const uint32_t ALIGMENT_T = 2000000; //microsecond
            const uint16_t IR_DELAY = 3000;//microseconds
            const int16_t pValuesSize = 3;
            const uint16_t THRESHOLD = 30;
            int16_t pValues[3] = {0,0,0};
            int16_t currentPointer = 0;
            int16_t maxAmp = 0;

            uint16_t motorDirection = true;
            uint16_t motorAmplitude = 60;
            uint16_t motorStepDown = 10;

            Phase currentPhase;
            LLRobot::Side currentSide;
            Claw claw;
            Arm arm;
            ArmTrip at;
            QSD fS;
            QSD mS;
            QSD bS;


            uint32_t aligmentTimestamp = 0;
            uint32_t extensionTimestamp = 0;
            uint32_t clawTimestamp = 0;
            uint32_t retractionTimestamp = 0;


            void updatePValues(int16_t value);
            int16_t readPValue(int16_t stepsBack);


            void setup();
            void alignment();
            void extension();
            void close();
            void retraction();
            void fail();
            void refindTape();
            void oneEightyP1();
            void oneEightyP2();
    };
};
