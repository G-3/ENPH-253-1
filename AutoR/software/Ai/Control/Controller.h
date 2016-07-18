#pragma once

namespace Control{
    class ControlMode;
};


namespace Control{
    class Controller{
        private:
            Controller();
			~Controller();
            static Controller *main_instance;
            ControlMode *curController;
            int count = 0;


        public:
			static Controller *getInstance();
            void step();
            void swapController(ControlMode *newController);
    }; 
};
