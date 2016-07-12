#pragma once

class PidControl;

#include "Ai/Control/ControlMode.h"

namespace Control{
    class TapeFollow : ControlMode{
        private:
            int err;
            bool dir;
            PidControl* controlProcess;
        public:
            const int THLD1 = 200;
            const int THLD2 = 200;
            double v = 0; //The speed scaling factor
            double base = 255; //The base speed of the motor
            TapeFollow();
            ~TapeFollow();
	    void step();
    };
}

