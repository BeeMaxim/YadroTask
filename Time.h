#pragma once

#include <cstdint>
#include <string>

class Time {
public:
    Time() = default;
    Time(const std::string& line);
    int operator-(const Time& other) const;
    bool operator<(const Time& other) const;
    friend std::ostream& operator<< (std::ostream& out, const Time& time);
private:
    Time(int32_t minutes);
    void CheckCorrectness(const std::string line);

    std::string format_;
    int32_t minutes_;
};
