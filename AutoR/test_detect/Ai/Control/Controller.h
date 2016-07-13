#pragma once

namespace Control{
    class ControlMode;
};


namespace Control{
    class Controller{
        private:
            ControlMode *curMode;
            int count = 0;

        public:
            Controller();
	    ~Controller();
            void step();
    }; 
};
