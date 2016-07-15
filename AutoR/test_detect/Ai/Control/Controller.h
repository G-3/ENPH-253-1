#pragma once

namespace Control{
    class ControlMode;
};


namespace Control{
    class Controller{
        private:
            Controller();
            static Controller *main_instance;
            ControlMode *curController;
            int count = 0;

        public:

            void step();
            void swapController(ControlMode *newController);
    }; 
};
