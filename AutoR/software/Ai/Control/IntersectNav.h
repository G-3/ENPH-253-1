#pragma once


#include "ControlMode.h"
#include "../World.h"

namespace Control{
    class TapeFollow2;
}

namespace Control{
    class IntersectNav : public ControlMode{
        private:
            World::Node *base;
            World::Node *dest;
            World::Node *start;
			World::Dir destDir;
            bool expectTapeDir[4] = {};
            bool seenTapeDir[4] = {};
            World::Dir linedUp;
                
            bool checkMismatch(bool completed);

            enum Phase{INIT_ALIGN, DRIVE_THRU, INTER_ALIGN, TRIP_INTER, TRIP_FOLLOW, END};
            Phase curPhase;

            int speed;
            TapeFollow2* tapeFollower;
        public:
			IntersectNav(World::Node *start, World::Node *dest, World::Node *base);
            ~IntersectNav();
            void step();
            bool done();
            bool fail();
    };
}

