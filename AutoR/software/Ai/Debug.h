#pragma once

namespace Debug{
    enum MessageType {GENERAL=0, INTERSECT_DB, EDETECT, EHANDLER, PATHPLAN, MSGTYPE_LAST};
    const bool loggedTypes[MSGTYPE_LAST] = {
        1,  // GENERAL
        1,  // INTERSECT_DB:    Debug logs for intersection navigation control mode
        1,  // EDETECT:         Debug logs for event detection process
        1,  // EHANDLER:        Debug logs for event handler calls
        1   // PATHPLAN:        Debug logs for path planning
    };
    void serialPrint(char msg[], MessageType type = GENERAL);
}
