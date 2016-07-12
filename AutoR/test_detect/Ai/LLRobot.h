#pragma once

namespace LLRobot{
    enum DMot {DML, DMR};
    int readTF(LLRobot::QRD position);
    enum QRD {TFLF=0, TFRF=1, TFLB=2, TFRB=3, IDLF=4, IDRF=5, IDLB=6, IDRB=7};
    int[] QRD_THRESH = {200, 200, 200, 200, 200, 200, 200, 200};
    bool driveMotor(LLRobot::DMot motorpos, int16_t speed);
};
