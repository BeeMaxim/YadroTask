#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "EventProcessor.h"
#include "Time.h"

// cmake --build . | Debug/main.exe ../test_file.txt

int main(int argc, const char** argv) {
    if (argc < 2) {
        std::cerr << "No input file found\n";
        return 0;
    }
    std::ifstream read_in(argv[1]);

    EventProcessor processor(&read_in);
    try {
        processor.Process();
    } catch (const std::exception& e) {
        std::cerr << "Something went wrong, probably incorrect data format\n";
        return 0;
    }

    return 0;
}