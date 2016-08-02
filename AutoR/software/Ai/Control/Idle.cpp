#include "Idle.h"
#include "../LLRobot.h"

using namespace LLRobot::Rel;

namespace Control{
    Idle::Idle(){
    }
    Idle::~Idle(){
    }
    void Idle::step(){
        driveMotors(0, 0);
    }
}
