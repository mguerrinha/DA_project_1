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
            City city = City(name, id, code, demand, population);
            _waterSupplySystem.addVertex(code);
        }
    }
}

void WaterSupplyManager::load_stations(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;
    getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string id, code;
        if (std::getline(linhaStream, id, ',')
            && std::getline(linhaStream, code, ',')) {
            Station station = Station (id, code);
            _waterSupplySystem.addVertex(code);
        }
    }
}

void WaterSupplyManager::load_reservoirs(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;
    getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string name, municipality, id, code, maxDelivery;
        if (std::getline(linhaStream, name, ',')
            && std::getline(linhaStream, municipality, ',')
            && std::getline(linhaStream, id, ',')
            && std::getline(linhaStream, code, ',')
            && std::getline(linhaStream, maxDelivery, ',')) {
            Reservoir reservoir = Reservoir (name, municipality, id, code, maxDelivery);
            _waterSupplySystem.addVertex(code);
        }
    }
}

