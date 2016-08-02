#include "PidControl.h"
#include <phys253.h>

namespace Control{
    // Vc is defined as the reaction needed to counteract the error and is also
    // defined in the x direction with a robot to the right of the tape having
    // negative Vc.
    double PidControl::step(int error, float derivative){
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

    double Vc = -(P*error + I*errsum + D*derivative*10.)/10.;

    errp = error;

    return Vc;
    }
}
