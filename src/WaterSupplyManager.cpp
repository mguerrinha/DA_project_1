#include <iomanip>
#include "WaterSupplyManager.h"

WaterSupplyManager::WaterSupplyManager() = default;

void WaterSupplyManager::load_cities(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;
    getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string name, id, code;
        int demand, population;
        if (std::getline(linhaStream, name, ',')
            && std::getline(linhaStream, id, ',')
            && std::getline(linhaStream, code, ',')
            && linhaStream >> demand
            && linhaStream.ignore()
            && linhaStream >> population) {
            City city = City(name, id, code, demand, population);
            _waterSupplySystem.addVertex(code);
            _cityMap.emplace(code, city);
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
            && std::getline(linhaStream, code, '\r')) {
            Station station = Station (id, code);
            _waterSupplySystem.addVertex(code);
            _stationMap.emplace(code, station);
        }
    }
}

void WaterSupplyManager::load_reservoirs(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;
    getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string name, municipality, id, code;
        int maxDelivery;
        if (std::getline(linhaStream, name, ',')
            && std::getline(linhaStream, municipality, ',')
            && std::getline(linhaStream, id, ',')
            && std::getline(linhaStream, code, ',')
            && linhaStream >> maxDelivery) {
            Reservoir reservoir = Reservoir (name, municipality, id, code, maxDelivery);
            _waterSupplySystem.addVertex(code);
            _reservoirMap.emplace(code, reservoir);
        }
    }
}

void WaterSupplyManager::load_pipes(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;
    getline(arquivo, linha);
    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string spA, spB;
        int capacity, direction;
        if (std::getline(linhaStream, spA, ',')
            && std::getline(linhaStream, spB, ',')
            && linhaStream >> capacity
            && linhaStream.ignore()
            && linhaStream >> direction) {
            if (direction == 0) {
                _waterSupplySystem.addEdge(spB, spA, capacity);
            }
            _waterSupplySystem.addEdge(spA, spB, capacity);
        }
    }
}

std::unordered_map<std::string, City> &WaterSupplyManager::getCityMap() {
    return _cityMap;
}

std::unordered_map<std::string, Station> &WaterSupplyManager::getStationMap() {
    return _stationMap;
}

std::unordered_map<std::string, Reservoir> &WaterSupplyManager::getReservoirMap() {
    return _reservoirMap;
}

Graph WaterSupplyManager::getWaterSupplySystem() {
    return _waterSupplySystem;
}

void WaterSupplyManager::saveResultsToFile() {
    std::fstream file;
    file.open("../docs/flow_results.csv", std::ios::out);
    if (file) {
        file << "NAME,CODE,FLOW" << std::endl;
        for (Vertex *v: _waterSupplySystem.getVertexSet()) {
            if (v->getInfo()[0] == 'C') {
                City city = _cityMap.at(v->getInfo());
                int maxFlow = 0;
                for (Edge* edge : v->getIncoming()) {
                    maxFlow += edge->getFlow();
                }
                file << city.getName() << "," << city.getCode() << "," << std::to_string(maxFlow) << std::endl;
            }
        }
        file.close();
    }
}

Graph* WaterSupplyManager::copyGraphEdmonds(Graph *graph) {
    auto* newGraph = new Graph();

    for (auto v : graph->getVertexSet()) {

        newGraph->addVertex(v->getInfo());
    }

    for (Vertex* vertex : graph->getVertexSet()) {
        for (Edge* edge : vertex->getAdj()) {
            edge->setFlow(0);
            newGraph->addBidirectionalEdgeEdmond(vertex->getInfo(), edge->getDest()->getInfo(), edge->getWeight());
        }
    }

    return newGraph;
}

Graph* WaterSupplyManager::copyGraphAux(Graph *graph) {
    auto* newGraph = new Graph();
    for (auto v : graph->getVertexSet()) {
        newGraph->addVertex(v->getInfo());
    }
    for (Vertex* vertex : graph->getVertexSet()) {
        for (Edge* edge : vertex->getAdj()) {
            newGraph->addEdge(edge->getOrig()->getInfo(), edge->getDest()->getInfo(), edge->getWeight());
        }
    }
    for (auto v: newGraph->getVertexSet()) {
        for (Edge* e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    return newGraph;
}

bool WaterSupplyManager::bfsEdmondsKarp(Graph* g, Vertex* source, Vertex* sink) {
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
    }

    std::queue<Vertex*> queue;
    queue.push(source);
    source->setVisited(true);

    while (!queue.empty()) {
        Vertex* u = queue.front();
        queue.pop();

        for (Edge* edge : u->getAdj()) {
            Vertex* v = edge->getDest();
            if (!v->isVisited() && edge->getWeight() - edge->getFlow() > 0) {
                v->setVisited(true);
                v->setPath(edge);
                queue.push(v);
                if(v == sink) {
                    return true;
                }
            }
        }
    }
    return false;
}

void WaterSupplyManager::edmondsKarp(Graph* graph, const std::string &source, const std::string &target) {
    Graph* aux = copyGraphEdmonds(graph);
    Vertex* src = aux->findVertex(source);
    Vertex* sink = aux->findVertex(target);
    double max_flow = 0;

    while (bfsEdmondsKarp(aux, src, sink)) {
        double path_flow = INF;

        for (Vertex* v = sink; v != src; v = v->getPath()->getOrig()) {
            Edge* edge = v->getPath();
            path_flow = std::min(path_flow, edge->getWeight() - edge->getFlow());
        }

        for (Vertex* v = sink; v != src; v = v->getPath()->getOrig()) {
            Edge* edge = v->getPath();
            edge->setFlow(edge->getFlow() + path_flow);

            Edge* reverseEdge = edge->getReverse();
            if (reverseEdge != nullptr) {
                reverseEdge->setFlow(reverseEdge->getFlow() - path_flow);
            }
        }

        max_flow += path_flow;
    }

    for(Vertex* vertex: graph->getVertexSet()) {
        Vertex* auxVertex = aux->findVertex(vertex->getInfo());
        for(Edge* edge : vertex->getAdj()) {
            for(Edge* auxEdge : auxVertex->getAdj()) {
                if(edge->getDest()->getInfo() == auxEdge->getDest()->getInfo()) {
                    edge->setFlow(auxEdge->getFlow());
                }
            }
        }
    }
}

void WaterSupplyManager::maxFlowEachCity(Graph* graph, double *maxFlow) {
    for (Vertex* vertex : graph->getVertexSet()) {
        for (Edge* edge : vertex->getAdj()) {
            edge->setFlow(0);
        }
    }
    graph->addVertex("source");
    graph->addVertex("target");
    for (Vertex* vertex : graph->getVertexSet()) {
        if (vertex->getInfo()[0] == 'R') {
            Reservoir reservoir = _reservoirMap.at(vertex->getInfo());
            graph->addEdge("source", vertex->getInfo(), reservoir.getMaxDelivery());
        }
        else if (vertex->getInfo()[0] == 'C') {
            City city = _cityMap.at(vertex->getInfo());
            graph->addEdge(vertex->getInfo(), "target", city.getDemand());
        }
    }
    edmondsKarp(graph, "source", "target");

    Vertex* target = graph->findVertex("target");
    for (Edge* edge : target->getIncoming()) {
        *maxFlow += edge->getFlow();
    }

    graph->removeVertex("source");
    graph->removeVertex("target");

    double _ratio = 0;
    std::vector<double> ratios;
    for (Vertex* vertex : graph->getVertexSet()) {
        for (Edge* edge : vertex->getAdj()) {
            _ratio += edge->getFlow()/edge->getWeight();
            ratios.push_back(edge->getFlow()/edge->getWeight());
        }
    }
    ratio = _ratio / ratios.size();
    saveResultsToFile();
}

void WaterSupplyManager::maxFlowSpecificCity(Graph* graph, const std::string &city) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (_cityMap.find(city) == nullptr) {
        std::cout << "City not found." << std::endl;
        return;
    }
    double max_flow = 0;
    maxFlowEachCity(graph, &max_flow);
    for (Vertex* vertex : graph->getVertexSet()) {
        if (vertex->getInfo() == city) {
            double maxFlow = 0;
            for (Edge* edge : vertex->getIncoming()) {
                maxFlow += edge->getFlow();
            }
            City city = _cityMap.at(vertex->getInfo());
            std::cout << vertex->getInfo() << ": " << city.getName() << " <--> " << maxFlow << "/" << city.getDemand() << std::endl;
        }
    }
}

void WaterSupplyManager::checkSuficientFlow(Graph* graph) {
    double max_flow = 0;
    bool cityFound = false;
    maxFlowEachCity(graph, &max_flow);
    std::cout << "Cities without enough water:" << std::endl;
    for (Vertex* vertex : graph->getVertexSet()) {
        if (vertex->getInfo()[0] == 'C') {
            double maxFlow = 0;
            for (Edge* edge : vertex->getIncoming()) {
                maxFlow += edge->getFlow();
            }
            City city = _cityMap.at(vertex->getInfo());
            if (maxFlow < city.getDemand()) {
                double dif = city.getDemand() - maxFlow;
                City city = _cityMap.at(vertex->getInfo());
                std::cout << vertex->getInfo() << ": " << city.getName() << " as a deficit of: " << dif << " <--> " << maxFlow << "/" << city.getDemand() << std::endl;
                cityFound = true;
            }
        }
    }
    if (!cityFound) std::cout << "No cities were found with water deficit level." << std::endl;
}

void WaterSupplyManager::analysisMetrics() {
    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
        for (Edge* edge : vertex->getAdj()) {
            edge->setSelected(false);
        }
    }
    double average_difference = 0;
    double variance_difference = 0;
    double current_difference;
    double max_dif = 0;
    double _ratio = 0;
    std::vector<double> ratios;
    std::vector<double> differences;
    for (Vertex* v : _waterSupplySystem.getVertexSet()) {
        for (Edge* e : v->getAdj()) {
            if (!e->isSelected()) {
                _ratio += e->getFlow()/e->getWeight();
                ratios.push_back(e->getFlow()/e->getWeight());
                current_difference = e->getWeight()-std::abs(e->getFlow());
                differences.push_back(current_difference);
                average_difference += current_difference;
                e->setSelected(true);
                if (current_difference > max_dif) max_dif = current_difference;
            }
        }
    }
    ratio = _ratio / ratios.size();
    std::cout << ratio << std::endl;
    std::cout << "The current maximum difference between the capacity and flow of a pipe is " << max_dif << "." << std::endl;

    average_difference /= differences.size();
    std::cout << "The current average difference between the capacity and flow of each pipe is " << average_difference << "." << std::endl;

    for (double aux2 : differences) {
        variance_difference += std::pow(aux2 - average_difference, 2);
    }
    variance_difference /= differences.size();
    std::cout << "The current variance of the difference between the capacity and flow of each pipe is " << variance_difference << "." << std::endl;

    for (Vertex* v : _waterSupplySystem.getVertexSet()) {
        for (Edge* e : v->getAdj()) {
            e->setSelected(false);
        }
    }
}

void WaterSupplyManager::balanceFlow() {
    double maxFlow = 0;
    maxFlowEachCity(&_waterSupplySystem, &maxFlow);
    analysisMetrics();
/*
    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
        if (vertex->getInfo()[0] == 'P') {
            double dif = 0;
            if (!fullDeliveryPS(vertex, &dif)) {
                for (Edge* edge : vertex->getIncoming()) {
                    double auxRatio = edge->getFlow() / edge->getWeight();
                    if (auxRatio > ratio) {
                        double dif_ratio = auxRatio - ratio;
                        if (dif_ratio * edge->getWeight() <= dif) {
                            edge->setFlow(edge->getFlow() - dif_ratio * edge->getWeight());
                            dif -= dif_ratio * edge->getWeight();
                        }
                        else {
                            edge->setFlow(edge->getFlow() - dif);
                            break;
                        }
                    }
                }
            }
        }
    }
*/
    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
        if (vertex->getInfo()[0] == 'R') {
            double out = 0;
            for (Edge* edge : vertex->getAdj()) {
                out += edge->getFlow();
            }
            if (out < _reservoirMap.at(vertex->getInfo()).getMaxDelivery()) {
                double dif = _reservoirMap.at(vertex->getInfo()).getMaxDelivery() - out;
                for (Edge* edge : vertex->getAdj()) {
                    double aux_ratio = edge->getFlow() / edge->getWeight();
                    if (aux_ratio < ratio) {
                        double dif2 = ratio - aux_ratio;
                        if (dif2 * edge->getWeight() <= dif) {
                            edge->setFlow(edge->getFlow() + dif2 * edge->getWeight());
                            dif -= dif2 * edge->getWeight();
                        }
                        else {
                            edge->setFlow(edge->getFlow() + dif);
                            break;
                        }
                    }
                }
            }
        }
    }
    analysisMetrics();
}

void WaterSupplyManager::evaluateReservoirImpact(const std::string& reservoirToRemove){
    std::vector<std::pair<std::string,double>> removedEdges;
    Vertex* reservoir = _waterSupplySystem.findVertex(reservoirToRemove);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (reservoir == nullptr || reservoir->getInfo()[0] != 'R'){
        std::cout << "The code provided: " << reservoirToRemove << " is not valid." << std::endl;
        return;
    }
    for (Edge* edge : reservoir->getAdj()) {
        removedEdges.emplace_back(edge->getDest()->getInfo(), edge->getWeight());
    }

    _waterSupplySystem.removeVertex(reservoirToRemove);
    checkSuficientFlow(&_waterSupplySystem);
    _waterSupplySystem.addVertex(reservoirToRemove);

    Vertex* i = _waterSupplySystem.findVertex(reservoirToRemove);
    for (std::pair<std::string,double> j : removedEdges) _waterSupplySystem.addEdge(i->getInfo(), j.first, j.second);
}

void WaterSupplyManager::periodic_maintenance_pumping_stations() {
    std::vector<std::pair<std::string, double>> flowBefore;
    std::vector<std::pair<std::string, double>> flowAfter;
    std::vector<std::pair<std::string, double>> flowRatio;
    double total_max_flow = 0;
    maxFlowEachCity(&_waterSupplySystem, &total_max_flow);
    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
        if (vertex->getInfo()[0] == 'C') {
            double cityFlow = 0;
            for (Edge* edge : vertex->getIncoming()) {
                cityFlow += edge->getFlow();
            }
            flowBefore.emplace_back(vertex->getInfo(), cityFlow);
        }
    }
    int count_removable_stations = 0;
    for (Vertex* v : _waterSupplySystem.getVertexSet()) {
        if (v->getInfo()[0] == 'P') {
            Graph* aux = copyGraphAux(&_waterSupplySystem);
            aux->removeVertex(v->getInfo());
            double max_flow_specific1 = 0;
            maxFlowEachCity(aux, &max_flow_specific1);
            if (max_flow_specific1 == total_max_flow) {
                std::cout << v->getInfo() << std::endl;
                count_removable_stations++;
            }
        }
    }
    if (count_removable_stations > 0) {
        std::cout << "There are " << count_removable_stations << " pumping stations pumping stations that can be temporarily deactivated without affecting the network's max flow." << std::endl;
    }
    else {
        std::cout << "There are no pumping stations that don't affect the network's maw flow." << std::endl;
    }
    std::string in_aux;
    std::cout << "Do you want to see the cities most affected if we disable a particular pumping station? (y/n) ";
    std::getline(std::cin, in_aux);
    if (in_aux == "n" || in_aux == "N") {
        return;
    }
    else if (in_aux == "y" || in_aux == "Y") {
        std::string in_aux2;
        std::cout << "What is the code for the desired pumping station? ";
        std::cin >> in_aux2;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (_stationMap.find(in_aux2) == nullptr) {
            std::cout << "Pumping station not found." << std::endl;
            return;
        }
        Graph* aux2 = copyGraphAux(&_waterSupplySystem);
        aux2->removeVertex(in_aux2);
        double max_flow_specific2 = 0;
        maxFlowEachCity(aux2, &max_flow_specific2);

        if (max_flow_specific2 == total_max_flow) {
            std::cout << "This pumping station does not affect the flow of any city." << std::endl;
            return;
        }
        else {
            for (Vertex* vertex : aux2->getVertexSet()) {
                if (vertex->getInfo()[0] == 'C') {
                    double cityFlow = 0;
                    for (Edge* edge : vertex->getIncoming()) {
                        cityFlow += edge->getFlow();
                    }
                    flowAfter.emplace_back(vertex->getInfo(), cityFlow);
                }
            }
            for (const auto& pair1: flowBefore) {
                for (const auto& pair2: flowAfter) {
                    if (pair1.first == pair2.first) {
                        double ratio = pair2.second / pair1.second;
                        flowRatio.emplace_back(pair1.first, ratio);
                    }
                }
            }
            std::sort(flowRatio.begin(), flowRatio.end(), [](const auto& a, const auto& b) {
                return a.second < b.second;
            });
            int num_affected = 0, num_affected_aux = 0;
            for(auto & j : flowRatio) {
                if (j.second != 1) num_affected++;
            }

            int n;
            std::string line;
            std::cout << "Were affected " << num_affected << " cities, how many do you want to see? ";
            while (true) {
                std::getline(std::cin, line);
                std::stringstream in(line);

                if (in >> n) {
                    char check;
                    if (in >> check) {
                        std::cout << "Error: Invalid input. Please enter a valid number without any extra characters: ";
                    } else if (n > 0 && n <= num_affected) {
                        break;
                    } else {
                        std::cout << "Error: Invalid input. Please enter a valid number between 1 and " << num_affected << ": ";
                    }
                } else {
                    std::cout << "Error: Invalid input. Please enter a number: ";
                }
                in.clear();
            }

            for(auto & i : flowRatio) {
                if (num_affected_aux < num_affected) {
                    City city = _cityMap.at(i.first);
                    if (i.second > 1) {
                        std::cout << "The city of " << city.getName() << " saw a increase of " << std::round((i.second - 1) * 10000) / 100
                                  << "% in its total incoming flow." << std::endl;
                        num_affected_aux++;
                    }
                    if (i.second < 1) {
                        std::cout << "The city of " << city.getName() << " saw a decrease of " << std::round((1 - i.second) * 10000) / 100
                                  << "% in its total incoming flow." << std::endl;
                        num_affected_aux++;
                    }
                    if (i.second == 1) {
                        continue;
                    }
                }
            }
            return;
        }
    }
    else {
        std::cout << "Invalid characters have been entered." << std::endl;
        return;
    }
}

void WaterSupplyManager::pipeline_failures(const std::string& src, const std::string& dest) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (_waterSupplySystem.findVertex(src) == nullptr) {
        std::cout << "Source vertex not found." << std::endl;
        if (_waterSupplySystem.findVertex(dest) == nullptr) {
            std::cout << "Destiny vertex not found." << std::endl;
            return;
        }
        return;
    }
    if (_waterSupplySystem.findVertex(dest) == nullptr) {
        std::cout << "Destiny vertex not found." << std::endl;
        return;
    }
    std::vector<std::pair<std::string, double>> flowCitiesBefore;
    std::vector<std::pair<std::string, double>> flowCitiesAfter;
    double aux_max_flow = 0, original_max_flow = 0;

    maxFlowEachCity(&_waterSupplySystem, &original_max_flow);
    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
        if (vertex->getInfo()[0] == 'C') {
            double cityFlow = 0;
            for (Edge* edge : vertex->getIncoming()) {
                cityFlow += edge->getFlow();
            }
            flowCitiesBefore.emplace_back(vertex->getInfo(), cityFlow);
        }
    }

    Graph* aux = copyGraphAux(&_waterSupplySystem);
    aux->removeEdge(src, dest);
    maxFlowEachCity(aux, &aux_max_flow);
    for (Vertex* vertex : aux->getVertexSet()) {
        if (vertex->getInfo()[0] == 'C') {
            double cityFlow = 0;
            for (Edge* edge : vertex->getIncoming()) {
                cityFlow += edge->getFlow();
            }
            flowCitiesAfter.emplace_back(vertex->getInfo(), cityFlow);
        }
    }

    int num_checks = 0;
    for (const auto& pair1: flowCitiesBefore) {
        for (const auto& pair2: flowCitiesAfter) {
            if (pair1.first == pair2.first) {
                double deficit = pair1.second - pair2.second;
                if (deficit == 0) {
                    continue;
                }
                else if (deficit > 0){
                    City city = _cityMap.at(_waterSupplySystem.findVertex(pair1.first)->getInfo());
                    std::cout << city.getName() << " | " << pair1.first << " --> Water Supply in Deficit (in losses): " << deficit << std::endl;
                    num_checks++;
                }
                else {
                    City city = _cityMap.at(_waterSupplySystem.findVertex(pair1.first)->getInfo());
                    std::cout << city.getName() << " | " << pair1.first << " --> Water Supply in Deficit (in gains): " << -deficit << std::endl;
                    num_checks++;
                }
            }
        }
    }
    if (num_checks == 0) {
        std::cout << "No changes found." << std::endl;
    }
}

double WaterSupplyManager::getRatio() const {
    return ratio;
}

void WaterSupplyManager::setRatio(double ratio) {
    this->ratio = ratio;
}

bool WaterSupplyManager::fullDeliveryPS(Vertex *ps, double *dif) {
    double in = 0, out = 0;
    for (Edge* edge : ps->getIncoming()) {
        in += edge->getFlow();
    }
    for (Edge* edge : ps->getAdj()) {
        out += edge->getFlow();
    }
    *dif = in - out;
    return in == out;
}
