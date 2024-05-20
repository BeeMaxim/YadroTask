#pragma once

#include <string>
#include <map>
#include <vector>
#include <queue>

#include "Client.h"
#include "Station.h"
#include "Time.h"

class StateInfo {
public:
    StateInfo();
    StateInfo(const Time& open_time, const Time& close_time, int station_count);
    void AddClient(const Time& time, const std::string& name);
    void OccupyStation(const Time& time, const std::string& name, int station_number);
    void WaitForStation(const Time& time, const std::string& name);
    void ClientLeft(const Time& time, const std::string& name);

    void OccupyStationOutcoming(const Time& time, int station_number);
    void ClientLeftOutcoming(const Time& time, const std::string& name);

    void ClientsOut();

    void PrintEvent(const Time& time, int id, const std::string& name, int optional = -1);
    void PrintError(const Time& time, const std::string& status);
    void PrintStationInfo(int price) const;

private:
    std::map<std::string, Client> clients_;
    std::queue<std::string> client_queue_;
    std::vector<Station> stations_;
    Time open_time_;
    Time close_time_;
    int station_count_;
    int occupied_station_count_ = 0;
};