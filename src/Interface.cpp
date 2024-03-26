//
// Created by miguel on 18-03-2024.
//
#include "Interface.h"

Interface::Interface() = default;

WaterSupplyManager Interface::_waterSupplyManager;

void Interface::run() {
    bool running = true;
    std::string aux;

    std::cout << "Welcome to our system of water supply management";

    while (running) {
        int choice  = displayMainMenu();
        switch (choice) {
            case 0:
                std::cout << "Thank you for using our water supply management system!" << std::endl;
                running = false;
                break;
            case 1:
                _waterSupplyManager.load_stations("../Project1DataSetSmall/Stations_Madeira.csv");
                _waterSupplyManager.load_reservoirs("../Project1DataSetSmall/Reservoirs_Madeira.csv");
                _waterSupplyManager.load_cities("../Project1DataSetSmall/Cities_Madeira.csv");
                _waterSupplyManager.load_pipes("../Project1DataSetSmall/Pipes_Madeira.csv");
                break;
            case 2:
                _waterSupplyManager.load_stations("../Project1LargeDataSet/Stations.csv");
                _waterSupplyManager.load_reservoirs("../Project1LargeDataSet/Reservoir.csv");
                _waterSupplyManager.load_cities("../Project1LargeDataSet/Cities.csv");
                _waterSupplyManager.load_pipes("../Project1LargeDataSet/Pipes.csv");
                break;
            case 3:
                _waterSupplyManager.maxFlowEachCity();
                break;
            case 4:
                std::cout << "Qual é o código da cidade desejada? " << std::endl;
                std::cin >> aux;
                _waterSupplyManager.maxFlowSpecificCity(aux);
                break;
            case 5:
                _waterSupplyManager.analysisMetrics();
                break;
        }
    }
}

int Interface::displayMainMenu() {
    std::cout << "---------------- Water Supply Management ----------------" << std::endl;
    std::cout << "1 --> Load small dataset" << std::endl;
    std::cout << "2 --> Load large dataset" << std::endl;
    std::cout << "3 --> General Max Flow" << std::endl;
    std::cout << "4 --> Max Flow for a specific City" << std::endl;
    std::cout << "5 --> Analyze the current metrics of the graph" << std::endl;
    std::cout << "0 --> Exit" << std::endl;
    std::cout << "Choose one option: ";
    int option;
    std::cin >> option;
    return option;
}
