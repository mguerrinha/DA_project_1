#include "Interface.h"

Interface::Interface() = default;

WaterSupplyManager Interface::_waterSupplyManager;

void Interface::run() {
    Graph graph;
    bool running = true;
    std::string aux, src, dest, file;

    std::cout << "Welcome to our system of water supply management" << std::endl;
    while (running) {
        int choice  = displayLoadOptions();
        switch (choice) {
            case 0:
                std::cout << "Thank you for using our water supply management system!" << std::endl;
                running = false;
                break;
            case 1:
                _waterSupplyManager.load_reservoirs("../Project1DataSetSmall/Reservoirs_Madeira.csv");
                _waterSupplyManager.load_stations("../Project1DataSetSmall/Stations_Madeira.csv");
                _waterSupplyManager.load_cities("../Project1DataSetSmall/Cities_Madeira.csv");
                _waterSupplyManager.load_pipes("../Project1DataSetSmall/Pipes_Madeira.csv");
                graph = _waterSupplyManager.getWaterSupplySystem();
                mainMenuOptions(&graph);
                break;

            case 2:
                _waterSupplyManager.load_reservoirs("../Project1LargeDataSet/Reservoir.csv");
                _waterSupplyManager.load_stations("../Project1LargeDataSet/Stations.csv");
                _waterSupplyManager.load_cities("../Project1LargeDataSet/Cities.csv");
                _waterSupplyManager.load_pipes("../Project1LargeDataSet/Pipes.csv");
                 graph = _waterSupplyManager.getWaterSupplySystem();
                mainMenuOptions(&graph);
                break;

            case 3:
                std::cout << "Path of the file that contains reservoirs you want to use: ";
                std::cin >> file;
                _waterSupplyManager.load_reservoirs(file);
                std::cout << "Path of the file that contains stations you want to use: ";
                std::cin >> file;
                _waterSupplyManager.load_stations(file);
                std::cout << "Path of the file that contains cities you want to use: ";
                std::cin >> file;
                _waterSupplyManager.load_cities(file);
                std::cout << "Path of the file that contains pipes you want to use: ";
                std::cin >> file;
                _waterSupplyManager.load_pipes(file);
                graph = _waterSupplyManager.getWaterSupplySystem();
                mainMenuOptions(&graph);
                break;

            default:
                std::cout << "Invalid option!" << std::endl;
                break;
        }
    }
}

int Interface::displayMainMenu() {
    std::cout << "-----------Water Supply Management -------------" << std::endl;
    std::cout << "1 --> General Max Flow" << std::endl;
    std::cout << "2 --> Max Flow for a specific City" << std::endl;
    std::cout << "3 --> Check desired water rate levels" << std::endl;
    std::cout << "4 --> Analyze the current metrics of the graph" << std::endl;
    std::cout << "5 --> Balance pipes" << std::endl;
    std::cout << "6 --> Cities affected by removing Reservoir" << std::endl;
    std::cout << "7 --> Not needed pumping stations." << std::endl;
    std::cout << "8 ->> Pipeline failures and cities affected by it." << std::endl;
    std::cout << "0 --> Exit" << std::endl;
    std::cout << "Choose one option: ";
    int option;
    std::cin >> option;
    return option;
}

int Interface::displayLoadOptions() {
    std::cout << "-----------Load Options -------------" << std::endl;
    std::cout << "1 --> Load Madeira dataset" << std::endl;
    std::cout << "2 --> Load Portugal dataset" << std::endl;
    std::cout << "3 --> Load other dataset" << std::endl;
    std::cout << "0 --> Exit" << std::endl;
    std::cout << "Choose one option: ";
    int option;
    std::cin >> option;
    return option;
}

void Interface::mainMenuOptions(Graph *graph) {
    bool running = true;
    std::string city;
    std::string src, dest;
    std::string reservoir;
    while (running) {
        int choice = displayMainMenu();
        switch (choice) {
            case 0:
                std::cout << "Thank you for using our water supply management system!" << std::endl;
                running = false;
                break;
            case 1:
                double max_flow;
                _waterSupplyManager.maxFlowEachCity(graph, &max_flow);
                std::cout << "The maximum flow is: " << max_flow << std::endl;
                break;
            case 2:
                std::cout << "Qual é o código da cidade desejada? ";
                std::cin >> city;
                _waterSupplyManager.maxFlowSpecificCity(graph, city);
                break;
            case 3:
                _waterSupplyManager.checkSuficientFlow(graph);
                break;
            case 4:
                _waterSupplyManager.analysisMetrics();
                break;
            case 5:
                _waterSupplyManager.balanceFlow();
                break;
            case 6:
                std::cout << "Qual é o código do reservatório desejado? " << std::endl;
                std::cin >> reservoir;
                _waterSupplyManager.evaluateReservoirImpact(reservoir);
                break;
            case 7:
                _waterSupplyManager.periodic_maintenance_pumping_stations();
                break;
            case 8:
                std::cout << "Qual é a source da pipeline desejada? ";
                std::cin >> src;
                std::cout << "Qual é o destiny da pipeline desejada? ";
                std::cin >> dest;
                _waterSupplyManager.pipeline_failures(src, dest);
                break;
            default:
                std::cout << "Invalid option!" << std::endl;
                break;
        }
    }

}
