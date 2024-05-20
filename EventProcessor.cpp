#include <iostream>
#include <string>

#include "EventProcessor.h"
#include "utils.h"


EventProcessor::EventProcessor(std::ifstream* read_in) : read_in_(read_in) {}


void EventProcessor::Process() {
    std::string line;
    std::getline(*read_in_, line);
    int station_count = parse_number(line);

    std::getline(*read_in_, line);
    std::vector<std::string> timetable = split_by_space(line);
    Time open_time(timetable[0]);
    Time close_time(timetable[1]);

    std::getline(*read_in_, line);
    int price = parse_number(line);

    this->info_ = StateInfo(open_time, close_time, station_count);

    std::cout << open_time << std::endl;

    while (std::getline(*read_in_, line)) {
        ProcessEvent(line);
    }

    info_.ClientsOut();
    std::cout << close_time << std::endl;
    info_.PrintStationInfo(price);
}

void EventProcessor::ProcessEvent(const std::string& line) {
    std::vector<std::string> args = split_by_space(line);

    Time time(args[0]);
    int id = parse_number(args[1]);
    std::string name = args[2];

    std::cout << line << std::endl;

    if (id == 1) { // client arrived
        info_.AddClient(time, name);
    } else if (id == 2) { // client sat down at the computer
        int station_number = parse_number(args[3]);
        info_.OccupyStation(time, name, station_number);
    } else if (id == 3) { // client is waiting for free station
        info_.WaitForStation(time, name);
    } else if (id == 4) { // client left 
        info_.ClientLeft(time, name);
    } else {
        throw std::invalid_argument("");
    }
}
