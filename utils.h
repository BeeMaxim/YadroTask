#pragma once

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_by_space(const std::string& line);

int parse_number(const std::string& line);

std::string format_time(int minutes);