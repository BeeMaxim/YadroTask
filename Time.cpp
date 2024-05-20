#include <cctype>
#include <ostream>
#include <stdexcept>

#include "Time.h"


Time::Time(const std::string& line) : format_(line) {
    CheckCorrectness(line);
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


void Time::CheckCorrectness(const std::string line) {
    if (line.size() == 5) {
        for (int i = 0; i < 5; ++i) {
            if (i == 2) {
                if (line[i] != ':') {
                    throw std::invalid_argument("");
                }
            } else {
                if (!std::isdigit(static_cast<unsigned char>(line[0]))) {
                    throw std::invalid_argument("");
                }
            }
        }
    } else {
        throw std::invalid_argument("");
    }
    if (line[3] - '0' > 5) { // correct minutes count
        throw std::invalid_argument("");
    }
    if ((line[0] - '0' > 2) || ((line[0] - '0' == 2) && (line[1] - '0' > 3))) { // correct hours count
        throw std::invalid_argument("");
    }
}
