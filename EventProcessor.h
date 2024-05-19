#pragma once

#include <fstream>

#include "StateInfo.h"

class EventProcessor {
public:
    EventProcessor(std::ifstream* read_in);
    void Process();
private:
    void ProcessEvent(const std::string& line);

    StateInfo info_;
    std::ifstream* read_in_;
};