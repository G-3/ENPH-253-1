#pragma once

#include "ControlMode.h"

namespace Control{
    class TurnAround : public ControlMode{
        private:
            enum Phase {SETUP,FIND_LEFT,FIND_RIGHT};
            Phase currentPhase;
        public:
            const double ROTATION_SPEED = 50; //The speed scaling factor
            TurnAround();
            ~TurnAround();
	    void step();
    };
}
