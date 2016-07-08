#include "LLRobot.h"

int LLRobot::readQRD(TF position){
    switch(position){
        case TFLF:
            digitalWrite(pinMPQRD, 1);
            analogRead(pinTFL);

        case TFRF:
            digitalWrite(pinMPQRD, 1);
            analogRead(pinTFR);

        case TFLB:
            digitalWrite(pinMPQRD, 0);
            analogRead(pinTFL);

        case TFRB:
            digitalWrite(pinMPQRD, 0);
            analogRead(pinTFR);
    }
}


