#include <iostream>

#include "StateInfo.h"
#include "utils.h"


StateInfo::StateInfo() {}


StateInfo::StateInfo(const Time& open_time, const Time& close_time, int station_count) : open_time_(open_time), close_time_(close_time), station_count_(station_count) {
    stations_.assign(station_count_, {});
}


void StateInfo::AddClient(const Time& time, const std::string& name) {
    if (clients_.find(name) != clients_.end()) {
        PrintError(time, "YouShallNotPass");
        return;
    }
    if (time < open_time_) {
        PrintError(time, "NotOpenYet");
        return;
    }
    clients_[name] = Client();
    return;
}


void StateInfo::OccupyStation(const Time& time, const std::string& name, int station_number) {
    if (!stations_[station_number - 1].IsFree()) {
        PrintError(time, "PlaceIsBusy");
        return;
    }
    auto client = clients_.find(name);
    if (client == clients_.end()) {
        PrintError(time, "ClientUnknown");
        return;
    }

    int old_station = client->second.station_occupied;
    client->second.station_occupied = station_number;
    if (old_station != -1) { // client changed station
        stations_[old_station - 1].Free(time);
    } else { // client occupied new station
        ++occupied_station_count_;
    }   
    stations_[station_number - 1].Occupy(time);
    return;
}


void StateInfo::WaitForStation(const Time& time, const std::string& name) {
    if (occupied_station_count_ < station_count_) {
        PrintError(time, "ICanWaitNoLonger!");
        return;
    }
    if (client_queue_.size() > station_count_) { // ? > vs >=
        ClientLeftOutcoming(time, name);
        return;
    }
    client_queue_.push(name);
    return;
}


void StateInfo::ClientLeft(const Time& time, const std::string& name) {
    auto client = clients_.find(name);
    if (client == clients_.end()) {
        PrintError(time, "ClientUnknown");
        return;
    }
    int old_station = client->second.station_occupied;
    clients_.erase(client);
    if (old_station != -1) {
        stations_[old_station - 1].Free(time);
        --occupied_station_count_;
        OccupyStationOutcoming(time, old_station);
    }
    return;
}


void StateInfo::OccupyStationOutcoming(const Time& time, int station_number) {
    if (client_queue_.empty()) {
        return;
    }
    std::string name = client_queue_.front();
    client_queue_.pop();
    auto client = clients_.find(name);
    client->second.station_occupied = station_number;

    stations_[station_number - 1].Occupy(time);
    ++occupied_station_count_;
    PrintEvent(time, 12, name, station_number);
}


void StateInfo::ClientLeftOutcoming(const Time& time, const std::string& name) {
    PrintEvent(time, 11, name);
}


void StateInfo::ClientsOut() {
    for (auto& client : clients_) {
        ClientLeftOutcoming(close_time_, client.first);
        int station_number = client.second.station_occupied;
        if (station_number != -1) {
            stations_[station_number - 1].Free(close_time_);
        }
    }
    clients_.clear();
}


void StateInfo::PrintEvent(const Time& time, int id, const std::string& name, int optional) {
    std::cout << time << ' '<< id << ' ' << name;
    if (id == 2 || id == 12) {
        std::cout << ' ' << optional;
    }
    std::cout << std::endl;
}


void StateInfo::PrintError(const Time& time, const std::string& status) {
    std::cout << time << ' ' << 13 << ' ' << status << std::endl;
}


void StateInfo::PrintStationInfo(int price) const {
    for (int i = 0; i < station_count_; ++i) {
        std::cout << i + 1 << ' '<< price * stations_[i].paid_hours_occupied << ' ' << format_time(stations_[i].minutes_occupied) << std::endl;
    }
}