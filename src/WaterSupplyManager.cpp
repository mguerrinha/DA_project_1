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



Graph* WaterSupplyManager::getGraphCopy(Graph *graph) {
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
    Graph* aux = getGraphCopy(graph);
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

void WaterSupplyManager::maxFlowEachCity(Graph* graph, double *auxFlow) {
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

    for (Vertex* vertex : graph->getVertexSet()) {
        double maxFlow = 0;
        if (vertex->getInfo() == "target") {
            for (Edge* edge : vertex->getIncoming()) {
                maxFlow += edge->getFlow();
            }
            *auxFlow = maxFlow;
        }
    }
    graph->removeVertex("source");
    graph->removeVertex("target");
}

void WaterSupplyManager::maxFlowSpecificCity(Graph* graph, const std::string &city) {
    double max_flow = 0;
    maxFlowEachCity(graph, &max_flow);
    for (Vertex* vertex : graph->getVertexSet()) {
        if (vertex->getInfo() == city) {
            double maxFlow = 0;
            for (Edge* edge : vertex->getIncoming()) {
                maxFlow += edge->getFlow();
            }
            City city = _cityMap.at(vertex->getInfo());
            std::cout << vertex->getInfo() << " | " << city.getName() << " <--> " << maxFlow << "/" << city.getDemand() << std::endl;
        }
    }
}

void WaterSupplyManager::checkSuficientFlow(Graph* graph) {
    double max_flow = 0;
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
                std::cout << vertex->getInfo() << " as a deficit of: " << dif << std::endl;
            }
        }
    }
}

void WaterSupplyManager::analysisMetrics() {
    double average_difference = 0;
    double variance_difference = 0;
    double current_difference;
    double max_dif = 0;
    std::vector<double> _differences;
    for (Vertex* v : _waterSupplySystem.getVertexSet()) {
        for (Edge* e : v->getAdj()) {
            if (!e->isSelected()) {
                current_difference = e->getWeight()-std::abs(e->getFlow());
                _differences.push_back(current_difference);
                e->setSelected(true);
                if (current_difference > max_dif) max_dif = current_difference;
            }
        }
    }
    std::cout << "A diferença máxima atual entre a capacidade e o flow de um pipe é " << max_dif << "." << std::endl;

    for (double aux : _differences) {
        average_difference += aux;
    }
    average_difference = average_difference / _differences.size();
    std::cout << "A média atual da diferença entre a capacidade e o flow de cada pipe é " << average_difference << "." << std::endl;

    for (double aux2 : _differences) {
        variance_difference += std::pow(aux2 - average_difference, 2);
    }
    variance_difference = variance_difference / _differences.size();
    std::cout << "A variância atual da diferença entre a capacidade e o flow de cada pipe é " << variance_difference << "." << std::endl;

    for (Vertex* v : _waterSupplySystem.getVertexSet()) {
        for (Edge* e : v->getAdj()) {
            e->setSelected(false);
        }
    }
}

void WaterSupplyManager::balanceFlow() {
    std::vector<std::pair<double, Edge*>> auxEdges;
    for (Vertex* v : _waterSupplySystem.getVertexSet()) {
        for (Edge* e : v->getAdj()) {
            if (!e->isSelected()) {
                auxEdges.emplace_back(e->getFlow()/ e->getWeight(), e);
                e->setSelected(true);
            }
        }
    }

    std::sort(auxEdges.begin(), auxEdges.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });

    for (const auto& pair : auxEdges) { // Antes
        std::cout << pair.first << std::endl;
    }

    for (auto& overloaded : auxEdges) {
        for (auto& underloaded : auxEdges) {
            if(overloaded.second->getOrig() == underloaded.second->getOrig() && overloaded.second->getDest() == underloaded.second->getDest()) continue;

            if(overloaded.first < 0 || underloaded.first < 0) continue;

            if(overloaded.first >= 0.5 && overloaded.first < 0.6) continue;

            if(underloaded.first >= 0.5 && underloaded.first < 0.6) continue;

            if(underloaded.first == 0 && overloaded.second->getFlow() < underloaded.second->getWeight()) {
                double excessFlow = overloaded.second->getFlow() / 2;
                overloaded.second->setFlow(overloaded.second->getFlow() - excessFlow);
                overloaded.first = overloaded.second->getFlow() / overloaded.second->getWeight();
                underloaded.second->setFlow(underloaded.second->getFlow() + excessFlow);
                underloaded.first = underloaded.second->getFlow() / underloaded.second->getWeight();
            }
            if (overloaded.first - underloaded.first > 0.45 && overloaded.second->getFlow() < underloaded.second->getWeight()) {
                double excessFlow = overloaded.second->getFlow() * 0.45;
                overloaded.second->setFlow(overloaded.second->getFlow() - excessFlow);
                overloaded.first = overloaded.second->getFlow() / overloaded.second->getWeight();
                underloaded.second->setFlow(underloaded.second->getFlow() + excessFlow);
                underloaded.first = underloaded.second->getFlow() / underloaded.second->getWeight();
            }
        }
    }

    std::cout << "----------------------" << std::endl;

    for (const auto& pair : auxEdges) { // Depois
        std::cout << pair.first << std::endl;
    }

    for (Vertex* v : _waterSupplySystem.getVertexSet()) {
        for (Edge* e : v->getAdj()) {
            e->setSelected(false);
        }
    }
}

void WaterSupplyManager::evaluateReservoirImpact(const std::string& reservoirToRemove){
    std::vector<std::pair<std::string,double>> removedEdges;
    Vertex* reservoir = _waterSupplySystem.findVertex(reservoirToRemove);
    if (reservoir == nullptr || reservoir->getInfo()[0] != 'R'){
        std::cout << "O código fornecido: " << reservoirToRemove << ", não é válido." << std::endl;
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
    double total_max_flow;
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
            Graph* aux = getGraphCopy(&_waterSupplySystem);
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
        std::cout << "Existem " << count_removable_stations << " pumping stations que podem ser desativadas temporariamente sem afetar o max flow da network." << std::endl;
    }
    else {
        std::cout << "Não existem pumping stations que não afetem o maw flow da network." << std::endl;
    }
    char in_aux;
    std::cout << "Deseja ver as cidades mais afetadas se desativarmos uma determinada pumping station? (y/n) ";
    std::cin >> in_aux;
    if (in_aux == 'n') {
        return;
    }
    else if (in_aux == 'y') {
        std::string in_aux2;
        std::cout << "Qual é o código da pumping station desejada? ";
        std::cin >> in_aux2;
        Graph* aux2 = getGraphCopy(&_waterSupplySystem);
        aux2->removeVertex(in_aux2);
        double max_flow_specific2 = 0;
        maxFlowEachCity(aux2, &max_flow_specific2);
        if (max_flow_specific2 == total_max_flow) {
            std::cout << "Esta pumping station não afeta o flow de nenhuma city." << std::endl;
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
                return a.first < b.first;
            });
            /*
            int n;
            std::cout << "Qual a n-ésima cidade mais afetada que deseja obter? ";
            std::cin >> n;

            for (int i = 0; i < flowRatio.size(); i++) {
                if ( (i+1) == n) {
                    City city = _cityMap.at(flowRatio[i].first);
                    std::cout << "A cidade de " << city.getName() << " teve um decréscimo de " << std::round((1 - flowRatio[i].second) * 10000) / 100
                    << "% no seu total incoming flow." << std::endl;
                }
            }
             */
            for (const auto& pair: flowAfter) {
                std::cout <<pair.second << " "<< pair.first << std::endl;
            }
            return;
        }
    }
    else {
        std::cout << "Foram inseridos caracteres inválidos." << std::endl;
        return;
    }

    /*
    std::vector<Vertex*> indiferentStations;
    bool flag = false;
    for (Vertex* v : _waterSupplySystem.getVertexSet()) {
        if (v->getInfo()[0] == 'P') {
            for (Edge *e: v->getAdj()) {
                if (e->getFlow() != 0) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                indiferentStations.push_back(v);
            }
            flag = false;
        }
    }

    if (indiferentStations.empty()) {
        std::cout << "Não existem pumping stations que possam ser desativadas temporariamente sem afetar o flow atual da network." << std::endl;
    }
    else {
        for (Vertex* v : indiferentStations) {
            std::cout << v->getInfo() << std::endl;
        }
        std::cout << "Existem pumping stations que possam ser desativadas temporariamente sem afetar o flow atual da network." << std::endl;
    }
    */
}
