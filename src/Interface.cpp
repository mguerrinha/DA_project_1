//
// Created by miguel on 18-03-2024.
//
#include "Interface.h"

Interface::Interface() = default;

WaterSupplyManager Interface::_waterSupplyManager;

void Interface::run() {
    bool running = true;

    _waterSupplyManager.load_stations("../Project1LargeDataSet/Stations.csv");
    _waterSupplyManager.load_reservoirs("../Project1LargeDataSet/Reservoir.csv");
    _waterSupplyManager.load_cities("../Project1LargeDataSet/Cities.csv");
    _waterSupplyManager.load_pipes("../Project1LargeDataSet/Pipes.csv");
    /*
    _waterSupplyManager.load_stations("../Project1DataSetSmall/Stations_Madeira.csv");
    _waterSupplyManager.load_reservoirs("../Project1DataSetSmall/Reservoirs_Madeira.csv");
    _waterSupplyManager.load_cities("../Project1DataSetSmall/Cities_Madeira.csv");
    _waterSupplyManager.load_pipes("../Project1DataSetSmall/Pipes_Madeira.csv");
*/
    std::cout << "Welcome to our system of water supply management";

    for (Vertex* vertex : _waterSupplyManager.getWaterSupplySystem().getVertexSet()) {
        std::cout << vertex->getInfo() << std::endl;
    }

    _waterSupplyManager.checkSuficientFlow();
}

int Interface::displayMainMenu() {
    std::cout << "---------------- Water Supply Management ----------------" << std::endl;
    std::cout << "1 --> Load small dataset" << std::endl;
    std::cout << "2 --> Load large dataset" << std::endl;
    std::cout << "0 --> Exit" << std::endl;
    std::cout << "Choose one option: ";
    int option;
    std::cin >> option;
    return option;
}



