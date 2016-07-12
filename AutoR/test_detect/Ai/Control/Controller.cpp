#include "Ai/Control/Controller.h"
#include "Ai/Control/ControlMode.h"
#include "Ai/Control/TapeFollow.h"

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
}
