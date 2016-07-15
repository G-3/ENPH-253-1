#pragma once

#include <stdint.h>

namespace LLRobot{
    enum DMot {DML, DMR};
    enum QRD {
    TFLF=0, TFRF=1, TFLB=2, TFRB=3, IDLF=4, IDRF=5, IDLB=6, IDRB=7};
    
    /*
     * Reads the analog output of the given QRD. If applyThresh is
     * true, will return 1/0 depending on if the sensor is on the 
     * tape. Returns the raw analog reading otherwise.
     */
    int readQRD(LLRobot::QRD position, bool applyThresh=false);
    const int QRD_THRESH[] = {200, 200, 200, 200, 200, 200, 200, 200};
    bool driveMotor(LLRobot::DMot motorpos, int16_t speed);
};
