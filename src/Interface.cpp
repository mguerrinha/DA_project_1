#include "Interface.h"

Interface::Interface() = default;

WaterSupplyManager Interface::_waterSupplyManager;

void Interface::run() {
    Graph graph;
    bool running = true;
    std::string aux;
    std::string src, dest;

    std::cout << "Welcome to our system of water supply management" << std::endl;
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
                graph = _waterSupplyManager.getWaterSupplySystem();
                break;
            case 2:
                _waterSupplyManager.load_stations("../Project1LargeDataSet/Stations.csv");
                _waterSupplyManager.load_reservoirs("../Project1LargeDataSet/Reservoir.csv");
                _waterSupplyManager.load_cities("../Project1LargeDataSet/Cities.csv");
                _waterSupplyManager.load_pipes("../Project1LargeDataSet/Pipes.csv");
                 graph = _waterSupplyManager.getWaterSupplySystem();
                break;
            case 3:
                double max_flow;
                _waterSupplyManager.maxFlowEachCity(&graph, &max_flow);
                std::cout << "O max flow atual é " << max_flow << "." << std::endl;
                break;
            case 4:
                std::cout << "Qual é o código da cidade desejada? ";
                std::cin >> aux;
                _waterSupplyManager.maxFlowSpecificCity(&graph, aux);
                break;
            case 5:
                _waterSupplyManager.analysisMetrics();
                break;
            case 6:
                _waterSupplyManager.balanceFlow();
                break;
            case 7:
                std::cout << "Qual é o código do reservatório desejado? " << std::endl;
                std::cin >> aux;
                _waterSupplyManager.evaluateReservoirImpact(aux);
                break;
            case 8:
                _waterSupplyManager.periodic_maintenance_pumping_stations();
                break;
            case 9:
                std::cout << "Qual é a source da pipeline desejada? ";
                std::cin >> src;
                std::cout << "Qual é o destiny da pipeline desejada? ";
                std::cin >> dest;
                _waterSupplyManager.pipeline_failures(src, dest);
                break;
            default:
                break;
        }
    }
}

int Interface::displayMainMenu() {
    std::cout << "-----------Water Supply Management -------------" << std::endl;
    std::cout << "1 --> Load small dataset" << std::endl;
    std::cout << "2 --> Load large dataset" << std::endl;
    std::cout << "3 --> General Max Flow" << std::endl;
    std::cout << "4 --> Max Flow for a specific City" << std::endl;
    std::cout << "5 --> Analyze the current metrics of the graph" << std::endl;
    std::cout << "6 --> Balance pipes" << std::endl;
    std::cout << "7 --> Cities affected by removing Reservoir" << std::endl;
    std::cout << "8 --> Not needed pumping stations." << std::endl;
    std::cout << "9 ->> Pipeline failures and cities affected by it." << std::endl;
    std::cout << "0 --> Exit" << std::endl;
    std::cout << "Choose one option: ";
    int option;
    std::cin >> option;
    return option;
}
