//
// Created by rui on 19-03-2024.
//

#ifndef DA_PROJECT_1_WATERSUPPLYMANAGER_H
#define DA_PROJECT_1_WATERSUPPLYMANAGER_H

#include "data_structures/Graph.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "City.h"
#include "Pipeline.h"
#include "Reservoir.h"
#include "Station.h"

class WaterSupplyManager {
private:
    static Graph<std::string> _waterSupplySystem;

    static std::unordered_map<std::string, City> _cityMap;

    static std::unordered_map<std::string, Station> _stationMap;

    static std::unordered_map<std::string, Reservoir> _reservoirMap;

public:
    WaterSupplyManager();

    static void load_cities(const std::string &file);

    static void load_stations(const std::string &file);

    static void load_reservoirs(const std::string &file);

    static void load_pipes(const std::string &file);
};


#endif //DA_PROJECT_1_WATERSUPPLYMANAGER_H
