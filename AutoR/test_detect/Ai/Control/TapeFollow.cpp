#include "Ai/Control/TapeFollow.h"
#include "Ai/Control/PidControl.h"

namespace Control{
    /*
     * Tape Following Mode
     */
    TapeFollow::TapeFollow(){
        controlProcess = new PidControl();
        err = dir = 0;
    }

    TapeFollow::~TapeFollow(){
       delete controlProcess; 
    }

    //TODO remove knob controls from controller.

    // Note error is defined in the x direction with a robot to the right
    // of the tape having positive error.
    void TapeFollow::step(){
        
        int sensorL = LLRobot::readQRD(LLRobot::TFLF, false);
        int sensorR = LLRobot::readQRD(LLRobot::TFRF, false);
        int l,r;
        if (sensorL < THLD1) l = 0;
        else l = 1;

        if (sensorR < THLD2) r = 0;
        else r = 1;

        //Determine the new error signal
        if (l == 0 && r == 1){
            err -= 1;
            dir = 0;
        } else if (l == 1 && r == 0){
            err += 1;
            dir = 1;
        } else if (l == 0 && r == 0){
        if (dir == 0){
            err -= 5;
        } else {
            err += 5;
        }
        } else if (l == 1 && r == 1){
            err = 0;
        }

        int Vc = controlProcess->step(err); 
        
        v = knob(7)/4.;
        // With a positive reaction needed, we need to increase the left motor.
        int powerL = v*(base + Vc);
        if (powerL > 255) powerL = 255;
        if (powerL < 0) powerL = 0;

        // With a positive reaction needed, we need to decrease the right motor.
        int powerR = v*(base - Vc);
        if (powerR > 255) powerR = 255;
        if (powerR < 0) powerR = 0;

        LLRobot::driveMotor(LLRobot::DML, powerL);
        LLRobot::driveMotor(LLRobot::DMR, powerR);
    }
}
