#pragma once

#include "Time.h"

class Station {
public:
    void Occupy(const Time& time);
    void Free(const Time& time);
    bool IsFree();
public:
    Time last_occupied;
    int paid_hours_occupied = 0;
    int minutes_occupied = 0;
    bool is_occupied = false;
};
