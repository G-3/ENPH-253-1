#pragma once

namespace Control{
    class PidControl{
        private:
	    int G;
            int P;
            int I;
            int D;
            int errp, errsum;
	    const int errsummax = 100;
            const int dt = 10; //time interval
        public:
            PidControl(int g=1, int p=1, int i=0, int d=1) : G(g), P(p), I(i), D(d){};
            ~PidControl(){};
            double step(int error, float derivative);
    };
} 
