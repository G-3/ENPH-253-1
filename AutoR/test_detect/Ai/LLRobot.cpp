#include "LLRobot.h"
#include <phys253.h>

namespace LLRobot{
    namespace{
        enum AIn {pinTFL=0, pinTFR=1, pinIDL=2, pinIDR=3};
        enum DOut {pinMPQRD=8};
        enum MOut {pinDML=0, pinDMR=1};
        enum DIn {};
        // Current Multiplexer States
        static const bool MPQRD_state = 0;
    }   

    int threshQRD(LLRobot::QRD position){
        return QRD_THRESH[position];
    }
    
    int readQRD(LLRobot::QRD position, bool applyThresh){
        int val = -1;
        switch(position){
            case TFLF:
                if(!MPQRD_state){
                    digitalWrite(pinMPQRD, 1);
                }
                val = analogRead(pinTFL);
                break;

            case TFRF:
                if(!MPQRD_state){
                    digitalWrite(pinMPQRD, 1);
                }
                val = analogRead(pinTFR);
                break;

            case TFLB:
                if(MPQRD_state){
                    digitalWrite(pinMPQRD, 0);
                }
                val = analogRead(pinTFL);
                break;

            case TFRB:
                if(MPQRD_state){
                    digitalWrite(pinMPQRD, 0);
                }
                val = analogRead(pinTFR);
                break;

            case IDLF:
                if(!MPQRD_state){
                    digitalWrite(pinMPQRD, 1);
                }
                val = analogRead(pinIDL);
                break;

            case IDRF:
                if(!MPQRD_state){
                    digitalWrite(pinMPQRD, 1);
                }
                val = analogRead(pinIDR);
                break;

            case IDLB:
                if(MPQRD_state){
                    digitalWrite(pinMPQRD, 0);
                }
                val = analogRead(pinIDL);
                break;

            case IDRB:
                if(MPQRD_state){
                    digitalWrite(pinMPQRD, 0);
                }
                val = analogRead(pinIDR);
                break;
            
            default:
                return -1;
        }
        return applyThresh ? val >= threshQRD(position) : val;
    }
   
    
    // Move the specified motor at speed 
    bool driveMotor(DMot motorpos, int16_t speed){
        switch(motorpos){
            case DML:
                motor.speed(pinDML, speed);
                return true;
            case DMR:
                motor.speed(pinDMR, speed);
                return true;
            default:
                return false;
        } 
        return false;
    }
}