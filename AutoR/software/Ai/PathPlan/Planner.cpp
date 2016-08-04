#include "Planner.h"
#include "PathMode.h"
#include "../HLRobot.h"
#include "../Config.h"
#include <phys253.h>

namespace PathPlan{
	Planner *Planner::main_instance = 0;

	Planner *Planner::getInstance() {
		if (!main_instance)
			main_instance = new Planner();
		return main_instance;
	}

    Planner::Planner(){
        // TODO: Add a default planner 
        curPlanner = 0;
    }

    Planner::~Planner(){
        delete curPlanner; 
    } 

    void Planner::swapPlanner(){
        // delete the old planner 
        delete curPlanner;
        // swap in the new planner
        curPlanner = nextPlanner;
        nextPlanner = 0;
    }
    
    void Planner::setNextPlanner(PathMode *newPlanner){
        // delete the old controller
        delete nextPlanner;
        nextPlanner = newPlanner;
        swapPlanner();
    }
    
    void Planner::update(){
        curPlanner->update();
    }

    void Planner::finishedTurnAround(){
        curPlanner->finishedTurnAround(); 
    }

    void Planner::finishedIntersect(){
        curPlanner->finishedIntersect();
    }
    
    void Planner::finishedPickUp(){
        curPlanner->finishedPickUp();
    } 

    void Planner::finishedDropOff(){
        curPlanner->finishedDropOff();
    }   

    void Planner::reverseIntersect(){
        curPlanner->reverseIntersect();
    }   
}
