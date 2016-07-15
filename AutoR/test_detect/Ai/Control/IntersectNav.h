#pragma once


#include "ControlMode.h"

namespace Control{
    class TapeFollow;
}


namespace Control{
    class IntersectNav : public ControlMode{
        private:
            Node *base;
            Node *dest;
            Node *start;
            bool[4] expectTapeDir = {};
            enum Phase{INIT_ALIGN, DRIVE_THRU, TRIP_INTER, TRIP_FOLLOW, END};
            Phase curPhase;
            int speed;
            TapeFollow* tapeFollower;
        public:
            IntersectNav();
            ~IntersectNav();
	    void step();
    };
}

