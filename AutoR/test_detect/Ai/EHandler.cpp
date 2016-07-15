#include "EHandler.h"

namespace EHandler{
    void intersect(bool left, bool right){                
        // Check to make sure this agrees with our internal model for the base node
        
        // If so start IntersectNavigation
       ::mainController->swapController(new IntersectionNav());    
    }
    
    void falseIntersect(){
         
    }

    void fail(char message[]){
        LCD.clear(); LCD.home();
        LCD.print(message);
    }

} 
