#include <phys253.h>
#include "Debug.h"

namespace Debug{
    void serialPrint(char msg[], MessageType type){
        if (loggedTypes[(int) type]){
            Serial.println(msg);
        }
    }
}
