#pragma once


#include "ControlMode.h"

namespace Control{
    class TapeFollow;
}


namespace Control{
    class IntersectNav : public ControlMode{
        private:
            Node &intersection;
            Node &destination;
            Node &start;

            TapeFollow* tapeFollower;
        public:
            IntersectNav();
            ~IntersectNav();
	    void step();
    };
}

