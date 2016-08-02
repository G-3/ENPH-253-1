#pragma once


#include "ControlMode.h"
#include "../World.h"

namespace Control{
    class TapeFollow2;
}

namespace Control{
    class IntersectSimp : public ControlMode{
        private:
            World::Node *base;
            World::Node *dest;
            World::Node *start;
            World::Dir destDir;
            bool expectTapeDir[4] = {};
            
            World::Dir linedUp;

            enum Phase{DRIVE_THRU, INTER_ALIGN, TRIP_INTER, TRIP_FOLLOW, END};
            Phase curPhase;

            int speed;
            TapeFollow2* tapeFollower;
        public:
			IntersectSimp(World::Node *start, World::Node *dest, World::Node *base);
            ~IntersectSimp();
            void step();
    };
}

