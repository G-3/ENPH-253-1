#ifndef __LLROBOT_H_INCLUDED__
#define __LLROBOT_H_INCLUDED__

#include <phys253.h>

class LLRobot{
    private:
        enum AIn {pinTFL=0, pinTFR=1, pinIDL=2, pinIDR=3};
        enum DOut {pinMPQRD=8};
        static const bool MPQRD_state = 0;
        enum DIn {};
    public:
        enum TF {TFLF, TFRF, TFLB, TFRB};
        static int readQRD(TF position);
};


#endif
