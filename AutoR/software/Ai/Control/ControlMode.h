#pragma once

namespace Control{
    class ControlMode{
        public:
            virtual void step() = 0;
    };
}
