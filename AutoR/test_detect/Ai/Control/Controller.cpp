#include "Controller.h"
#include "ControlMode.h"
#include "TapeFollow.h"
#include "../HLRobot.h"
#include <phys253.h>

namespace Control{
	Controller Controller::*main_instance = 0;

	Controller *Controller::getInstance() {
		if (!main_instance)
			main_instance = new Controller();
		return main_instance;
	}

    Controller::Controller(){
        curController= new TapeFollow();
        HLRobot::curMode = HLRobot::TAPE_FOLLOW;
    } 

    Controller::~Controller(){
        delete curController; 
    } 

    void Controller::step(){
        curController->step();
    }

    void Controller::swapController(ControlMode *newController){
        // delete the old controller
        delete curController;
        curController = newController;
    }
}
