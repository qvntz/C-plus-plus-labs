#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;
    if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else {
        q.type = QueryType::NewBus;
        is >> q.bus;
        size_t stop_count = 0;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (auto& item : q.stops) {
            is >> item;
        }
    }

    return is;
}

struct BusesForStopResponse {
    vector<string> buses_to_stop_;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses_to_stop_.empty()) {
        os << "No stop";
    }
    else {
        for (const auto& bus : r.buses_to_stop_) {
            os << bus << " ";
        }  
    }
    
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<pair<string, vector<string>>> stops_for_buses_;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops_for_buses_.empty()) {
        os << "No bus";
    }
    else {
        for (const auto& [stop, buses] : r.stops_for_buses_) {
            os << "Stop " << stop << ": ";
            if (buses.size() == 1) {
                os << "no interchange";
            }
            else {
               
                for (const auto& bus : buses) {
               
                    if (bus != r.bus) {
                        os << bus << " ";
                    }
                }

            }
            cout << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops_;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops_.empty()) {
        os << "No buses";
    }
    else {
        for (const auto& [bus, stops] : r.buses_to_stops_) {
            os << "Bus " << bus << ": ";
            for (const auto& stop : stops) {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse buses;
        
        if (stops_to_buses.count(stop) == 0) {
            return BusesForStopResponse{ vector<string>() };
        }
        else {
            return BusesForStopResponse{ stops_to_buses.at(stop) };
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse result;
        result.bus = bus;

        if (buses_to_stops.count(bus) == 0) {
            return result;
        }
        else {
            for (const auto& stop : buses_to_stops.at(bus)) {
                result.stops_for_buses_.push_back(make_pair(stop, stops_to_buses.at(stop)));
            }
            return result;
        }
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse{ buses_to_stops };
    }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
