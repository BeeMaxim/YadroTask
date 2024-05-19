#include "Station.h"


void Station::Free(const Time& time) {
    is_occupied = false;
    minutes_occupied += (time - last_occupied);
    paid_hours_occupied += (time - last_occupied + 59) / 60;
}


void Station::Occupy(const Time& time) {
    is_occupied = true;
    last_occupied = time;
}


bool Station::IsFree() {
    return !is_occupied;
}