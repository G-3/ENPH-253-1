#include "TapeFollow.h"
#include "PidControl.h"
#include "../LLRobot.h"
#include <phys253.h>

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
        
        if (l == 0 && r == 0){
            if (dir == 0){
                err = -1000;
            } else {
                err = 1000;
            }
        }

        else{
            if (l == 1 && r == 0){
                dir = 1;
            }else if(l==0 && r==1){
                dir = 0;
            } 

            err = -sensorR+sensorL;
        }
        /*if (l == 0 && r == 1){
            err = -10;
            dir = 0;
        } else if (l == 1 && r == 0){
            err = 10;
            dir = 10;
        } else if (l == 0 && r == 0){
        if (dir == 0){
            err = -50;
        } else {
            err = 50;
        }
        } else if (l == 1 && r == 1){
            err = 0;
        }*/

        double Vc = controlProcess->step(err); 
        
        double G = knob(6)/1024.;
        int base = knob(7)/6;
        // With a positive reaction needed, we need to increase the left motor.
        int powerL = base - G*Vc*base;
        if (powerL > 255) powerL = 255;
        if (powerL < 0) powerL = 0;

        // With a positive reaction needed, we need to decrease the right motor.
        int powerR = base + G*Vc*base;
        if (powerR > 255) powerR = 255;
        if (powerR < 0) powerR = 0;

        LLRobot::driveMotor(LLRobot::DML, powerL);
        LLRobot::driveMotor(LLRobot::DMR, powerR);
	counter+=1;
	
	if(counter%10==0){
	    Serial.println("~~~~~~~~~");
	    Serial.println(powerR);
	    Serial.println(powerL);
	    Serial.println("-       -");
	    Serial.println(sensorL);
	    Serial.println(sensorR);
	    Serial.println("~~~~~~~~~");
	    Serial.println();  
	    counter = 0;
	    LCD.clear();
            LCD.home();
	    LCD.print(sensorL);
	    LCD.print(" | ");
	    LCD.print(powerL);
	    LCD.setCursor(0,1);
	    LCD.print(sensorR);
	    LCD.print("|");
            LCD.print(powerR);
	    LCD.print("|");
	    LCD.print(Vc);
	}
	delay(10);
    }
}
