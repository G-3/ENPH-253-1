#pragma once

#include "ControlMode.h"

namespace Control{
    class TurnAround : public ControlMode{
        private:
            enum Phase {SETUP,FIND_LEFT,FIND_RIGHT};
        public:
            double rotationSpeed = 50; //The speed scaling factor
            TurnAround();
            ~TurnAround();
	    void step();
    };
}
