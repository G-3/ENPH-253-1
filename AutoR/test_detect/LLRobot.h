#pragma once
//#ifndef __LLROBOT_H_INCLUDED__
//#define __LLROBOT_H_INCLUDED__

#include <phys253.h>

namespace LLRobot{
    enum DMot {DML, DMR};
    enum TF {TFLF, TFRF, TFLB, TFRB};
    static int readQRD(TF position);
    bool driveMotor(DMot motorpos, int16_t speed);
};


//#endif
