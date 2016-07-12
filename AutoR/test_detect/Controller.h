#pragma once


namespace Control{

    class PidControl{
        private:
	    double G;
            int P;
            int I;
            int D;
            int errp, errsum;
	    const int errsummax = 100;
            const int dt = 10; //time interval
        public:
            PidControl(int g=1, int p=1, int i=0, int d=1) : G(g), P(p), I(i), D(d){};
            ~PidControl(){};
            int step(int error);
    };
 

    struct ControlMode{
        void step(){};
    };

    struct TapeFollow : ControlMode{
        private:
            int err;
            bool dir;
            PidControl* controlProcess;
        public:
            const int THLD1 = 200;
            const int THLD2 = 200;
            double v = 0; //The speed scaling factor
            double base = 255; //The base speed of the motor
            TapeFollow();
            ~TapeFollow();
	    void step();
    };

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
