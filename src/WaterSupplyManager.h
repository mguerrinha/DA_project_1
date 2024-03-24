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
    Graph _waterSupplySystem;

    std::unordered_map<std::string, City> _cityMap;

    std::unordered_map<std::string, Station> _stationMap;

    std::unordered_map<std::string, Reservoir> _reservoirMap;

public:
    WaterSupplyManager();

    void load_cities(const std::string &file);

    void load_stations(const std::string &file);

    void load_reservoirs(const std::string &file);

    void load_pipes(const std::string &file);

    Graph getWaterSupplySystem();

    std::unordered_map<std::string, City> &getCityMap();

    std::unordered_map<std::string, Station> &getStationMap();

    std::unordered_map<std::string, Reservoir> &getReservoirMap();

    Graph* getGraphCopy(Graph* graph);

    bool bfsEdmondsKarp(Graph* graph, Vertex *source, Vertex *target);

    void edmondsKarp(const std::string &source, const std::string &target);

    void maxFlowEachCity();

    void maxFlowSpecificCity(const std::string &city);

    void checkSuficientFlow();
};


#endif //DA_PROJECT_1_WATERSUPPLYMANAGER_H
