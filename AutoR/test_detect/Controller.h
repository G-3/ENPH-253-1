#pragma once


class Controller{
    private:
        static Controller *ed_instance;
        Controller(){};
        int count = 0;
        
        void followTape();
        const int THLD1 = 200;
        const int THLD2 = 200;
        const int dt = 10; //time interval
        double errsum = 0; //sum or all errors
        int err = 0;
        boolean dir = 0;
        double v = 0; //The speed scaling factor
        double base = 255; //The base speed of the motor
        double G = 1;
        double P = 1;
        double I = 0;
        double D = 1;
    
    public:
        static Controller *instance()
        {
            if(!ed_instance)
                ed_instance = new Controller;
            return ed_instance;
        };

        void step();
};
