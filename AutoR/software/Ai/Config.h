#pragma once
#include "Arduino.h"
namespace Config{
    // links describes edges between nodes: dest, start, dir from start to dest
    // dir-> 0:R 1:T 2:L 3:B
    // static const int links[2][3] = {{1, 0, 1},{1, 2, 0}};
    // static const int linksSize = 2;
    static const uint8_t linksSize = 40;
    static const uint8_t links[40][3]{ { 0, 1, 0 },
        { 1, 0, 2 },
        { 1, 2, 0 },
        { 1, 4, 1 },
        { 2, 1, 2 },
        { 2, 3, 1 },
        { 3, 2, 3 },
        { 3, 4, 2 },
        { 3, 9, 1 },
        { 4, 1, 3 },
        { 4, 3, 0 },
        { 4, 5, 2 },
        { 4, 8, 1 },
        { 5, 4, 0 },
        { 5, 6, 3 },
        { 5, 7, 2 },
        { 6, 5, 1 },
        { 7, 5, 0 },
        { 8, 4, 3 },
        { 9, 3, 3 },
        { 9, 13, 1 },
        { 10, 11, 0 },
        { 11, 10, 2 },
        { 11, 12, 0 },
        { 11, 14, 3 },
        { 12, 11, 2 },
        { 12, 13, 3 },
        { 13, 12, 1 },
        { 13, 14, 2 },
        { 13, 9, 3 },
        { 14, 11, 1 },
        { 14, 13, 0 },
        { 14, 15, 2 },
        { 14, 18, 3 },
        { 15, 14, 0 },
        { 15, 16, 1 },
        { 15, 17, 2 },
        { 16, 15, 3 },
        { 17, 15, 0 },
        { 18, 14, 1 }
    };
}