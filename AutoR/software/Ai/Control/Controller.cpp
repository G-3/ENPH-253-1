#include "Controller.h"
#include "ControlMode.h"
#include "TapeFollow.h"
#include "TapeFollow2.h"
#include "../HLRobot.h"
#include "../Config.h"
#include <phys253.h>

namespace Control{
	Controller *Controller::main_instance = 0;

	Controller *Controller::getInstance() {
		if (!main_instance)
			main_instance = new Controller();
		return main_instance;
	}

    Controller::Controller(){
        curController = new TapeFollow2(false, 17,25,Config::driveSpeed);
        HLRobot::curMode = HLRobot::TAPE_FOLLOW;
    }

    Controller::~Controller(){
        delete curController; 
    } 

    void Controller::step(){
        if (nextController){
            swapController();
        }
        curController->step();
    }

    void Controller::swapController(){
        // delete the old controller
        delete curController;
        curController = nextController;
        nextController = 0;
    }
    
    void Controller::setNextController(ControlMode *newController){
        // delete the old controller
        delete nextController;
        nextController = newController;
    }
}
