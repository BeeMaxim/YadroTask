#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "EventProcessor.h"
#include "Time.h"

// cmake --build . | Debug/main.exe ../test_file.txt

int main(int argc, const char** argv) {
    std::ifstream read_in(argv[1]);

    EventProcessor processor(&read_in);
    processor.Process();

    return 0;
}