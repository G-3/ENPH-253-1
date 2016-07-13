#pragma once


#include "ControlMode.h"

namespace Control{
    class TapeFollow;
}


namespace Control{
    class IntersectNav : public ControlMode{
        private:
            TapeFollow* tapeFollower;
        public:
            IntersectNav();
            ~IntersectNav();
	    void step();
    };
}

