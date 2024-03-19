//
// Created by rui on 19-03-2024.
//

#include "WaterSupplyManager.h"

WaterSupplyManager::WaterSupplyManager() = default;

Graph<std::string> WaterSupplyManager::_waterSupplySystem;

void WaterSupplyManager::load_cities(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;
    getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string name, id, code, demand, population;
        if (std::getline(linhaStream, name, ',')
            && std::getline(linhaStream, id, ',')
            && std::getline(linhaStream, code, ',')
            && std::getline(linhaStream, demand, ',')
            && std::getline(linhaStream, population, ',')) {

        }
    }
}
