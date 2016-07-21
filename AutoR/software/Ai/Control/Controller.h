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
            ControlMode *curController = 0;
            ControlMode *nextController = 0;
            int count = 0;
            void swapController();

        public:
			static Controller *getInstance();
            void step();
            void setNextController(ControlMode *newController);
    }; 
};
