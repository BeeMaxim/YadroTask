#include <ostream>

#include "Time.h"


Time::Time(const std::string& line) : format_(line) {
    minutes_ = ((line[0] - '0') * 10 + (line[1] - '0')) * 60 + (line[3] - '0') * 10 + (line[4] - '0');
}


int Time::operator-(const Time& other) const {
    return (minutes_ - other.minutes_);
}


bool Time::operator<(const Time& other) const {
    return (minutes_ < other.minutes_);
}


std::ostream& operator<< (std::ostream& out, const Time& time) {
    out  << time.format_;
    return out;
}


Time::Time(int32_t minutes) : minutes_(minutes) {}