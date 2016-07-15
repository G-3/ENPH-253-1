#include "Controller.h"
#include "ControlMode.h"
#include "TapeFollow.h"
#include <phys253.h>

namespace Control{
    Controller::Controller(){
       curMode = new TapeFollow(); 
    } 

    Controller::~Controller(){
       delete curMode; 
    } 

    void Controller::step(){
        Serial.println("Controller");
        curMode->step();
    }
}
