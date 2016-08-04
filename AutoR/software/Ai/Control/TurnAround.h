#pragma once
#include <Arduino.h>
#include "ControlMode.h"

namespace Control{
    class TurnAround : public ControlMode{
        private:
            enum Phase {SETUP,FIND_LEFT,FIND_RIGHT};
            Phase currentPhase;
            bool turnAround = true;
            uint32_t timestamp = 0;
            static const uint16_t TIMEOUT_MILLIS = 2000;
        public:
            const double ROTATION_SPEED = 50; //The speed scaling factor
            TurnAround();
            ~TurnAround();
	    void step();
    };
}
