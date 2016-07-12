#include "Controller.h"
#include "LLRobot.h"

namespace Control{
    Controller::Controller(){
       curMode = new TapeFollow(); 
    } 

    Controller::~Controller(){
       delete curMode; 
    } 

    void Controller::step(){
        curMode->step();
    }


    TapeFollow::TapeFollow(){
        controlProcess = new PidControl();
        err = dir = 0;
    }

    TapeFollow::~TapeFollow(){
       delete controlProcess; 
    }

    
    // Note error is defined in the x direction with a robot to the right
    // of the tape having positive error.
    void TapeFollow::step(){
        
	int sensorL = LLRobot::readQRD(LLRobot::TFLF);
        int sensorR = LLRobot::readQRD(LLRobot::TFRF);
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
    
    // Vc is defined as the reaction needed to counteract the error and is also
    // defined in the x direction with a robot to the right of the tape having
    // negative Vc.
    int PidControl::step(int error){
        while (startbutton()){
	    LCD.clear(); LCD.home();
	    while(!stopbutton()){
		LCD.clear();
		LCD.print("Set P = ");
		LCD.print(knob(6)/10);
		delay(10);
	    }
	    P = knob(6)/10;
	    delay(500);

	    LCD.clear(); LCD.home();
	    while(!stopbutton()){
		LCD.clear();
		LCD.print("Set I = ");
		LCD.print(knob(6)/10);
		delay(10);
	    }
	    I = knob(6)/10;
	    delay(500);

	    LCD.clear(); LCD.home();
	    while(!stopbutton()){
		LCD.clear();
		LCD.print("Set D = ");
		LCD.print(knob(6)/10);
		delay(10);
	    }
	    D = knob(6)/10;
	    delay(500);
	}

	errsum += error*dt;

        if (errsum > errsummax) errsum = errsummax;
        if (errsum < -errsummax) errsum = -errsummax;

        G = knob(6)/100.;

        int Vc = -G*(P*error + I*errsum + D*(error - errp)/dt)*dt/1000;

        errp = error;

        return Vc;
    }
}
