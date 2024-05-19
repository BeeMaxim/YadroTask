#include <iostream>

#include "utils.h"


std::vector<std::string> split_by_space(const std::string& line) { // unoptimal :(
    std::stringstream ss(line);
    std::vector<std::string> result;
    std::string cur;

    while (std::getline(ss, cur, ' ')) {
        result.push_back(cur);
    }

    return result;
}


int parse_number(const std::string& line) {
    return std::stoi(line);
}


std::string format_time(int minutes) {
    int hours = minutes / 60;
    int pure_minutes = minutes % 60;
    std::stringstream ss;
    ss << hours / 10 << hours % 10 << ':' << pure_minutes / 10 << pure_minutes % 10;
    return ss.str();
}