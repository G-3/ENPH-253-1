#include "LLRobot.h"

namespace LLRobot{
    namespace{
        enum AIn {pinTFL=0, pinTFR=1, pinIDL=2, pinIDR=3};
        enum DOut {pinMPQRD=8};
        enum MOut {pinDML=0, pinDMR=1};
        enum DIn {};
        
        // Current Multiplexer States
        static const bool MPQRD_state = 0;
    }   
    
    int readQRD(TF position){
        switch(position){
            case TFLF:
                if(!MPQRD_state){
                    digitalWrite(pinMPQRD, 1);
                }
                analogRead(pinTFL);

            case TFRF:
                if(!MPQRD_state){
                    digitalWrite(pinMPQRD, 1);
                }
                analogRead(pinTFR);

            case TFLB:
                if(MPQRD_state){
                    digitalWrite(pinMPQRD, 0);
                }
                analogRead(pinTFL);

            case TFRB:
                if(MPQRD_state){
                    digitalWrite(pinMPQRD, 0);
                }
                analogRead(pinTFR);
        }
    }

    
    // Move the specified motor at speed 
    bool driveMotor(DMot motorpos, int16_t speed){
        switch(motorpos){
            case DML:
                motor.speed(pinDML, speed);
            case DMR:
                motor.speed(pinDMR, speed);
        } 
    }
}
