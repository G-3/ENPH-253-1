#pragma once

#include "ControlMode.h"

namespace Control{
    class Idle: public ControlMode{
        public:
            Idle();
            ~Idle();
            void step();

    };
}
