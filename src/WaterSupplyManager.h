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

class WaterSupplyManager {
private:
    static Graph<std::string> _waterSupplySystem;



public:
    WaterSupplyManager();

    void load_cities(const std::string &file);
};


#endif //DA_PROJECT_1_WATERSUPPLYMANAGER_H
