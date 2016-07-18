#pragma once'

#include "ControlMode.h"

namespace Grab{
    /*
     * Grab is a control mode that should retrieve the passenger given we are lined up with it.:
     */
    class Grab : public ControlMode{
        private:
            int counter = 0;
        public:
            Grab();
            ~Grab();
	    void step();
    };
}

