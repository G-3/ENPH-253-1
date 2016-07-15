#pragma once

namespace Control{
    class ControlMode;
};


namespace Control{
    class Controller{
        private:
            ControlMode *curController;
            int count = 0;

        public:
            Controller();
	    ~Controller();
            void step();
            void swapController(ControlMode *newController);
    }; 
};
