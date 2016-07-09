#ifndef __EDETECT_H_INCLUDED__
#define __EDETECT_H_INCLUDED__

#include "LLRobot.h"

class EDetect{
    private:
        static EDetect *ed_instance;
        EDetect(){};
        int count = 0;
    public:
        static EDetect *instance()
        {
            if(!ed_instance)
                ed_instance = new EDetect;
            return ed_instance;
        };

        void step();
};

#endif // __EDETECT_H_INCLUDED__ 
