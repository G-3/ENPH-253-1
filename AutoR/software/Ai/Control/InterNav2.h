#pragma once

#include "ControlMode.h"
#include "../LLRobot.h"
#include "../World.h"
#include "TapeFollow2.h"

using namespace LLRobot::Rel;

namespace Control{
    class InterNav2: public ControlMode{
        private:
            enum Phase {SETUP,ALIGN_NAVIGATORS,TURN_P1,TURN_P2,GO_STRAIGHT,EXIT_INTER};
            Phase currentPhase = SETUP;
            World::Dir direction;

            TapeFollow2* tapeFollower;
            
            LLRobot::Side currentDirection;
            bool xl;
            bool xr;
            bool xf;
            bool xb;
            int16_t spinSpeed1;
            int16_t spinSpeed2;
            int16_t driveSpeed;
            
            // default values when entering an intersection;
            bool leftBackTrip = false;
            bool rightBackTrip = false;
            bool motorDirection = false;

            //Phase functions;
            void setup();
            void alignNavigators();
            void turnPhase1();
            void turnPhase2();
            void goStraight();
            void exitInter();

            //for detetecting collisions mid intersection
            void checkBumpers();
            uint32_t bumperTimestamp = 0;
            const uint16_t BUMPER_DELAY = 700;
        public:
            InterNav2(bool expectedTapeDir[],World::Dir direction,int16_t ss1,int16_t ss2,int16_t ds);
            ~InterNav2();
            void step();
    };
}
