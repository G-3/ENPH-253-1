#pragma once


#include "ControlMode.h"
#include "../World.h"

namespace Control{
    class TapeFollow2;
}

namespace Control{
    class IntersectCheck : public ControlMode{
        private:
            World::Node *base;
            World::Node *dest;
            World::Node *start;
            World::Dir destDir;
            bool expectTapeDir[4] = {};
            bool seenTapeDir[4] = {};
            
            World::Dir linedUp;

            enum Phase{DRIVE_THRU, INTER_ALIGN, TRIP_INTER, TRIP_FOLLOW, END};
            Phase curPhase;

            int speed;
            TapeFollow2* tapeFollower;
        public:
			IntersectCheck(World::Node *start, World::Node *dest, World::Node *base);
            ~IntersectCheck();
            void step();
    };
}

