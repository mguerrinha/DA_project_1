//
// Created by rui on 19-03-2024.
//

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

void WaterSupplyManager::edmondsKarp(const std::string &source, const std::string &target) {
    Graph* aux = getGraphCopy(&_waterSupplySystem);
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

    for(Vertex* vertex: _waterSupplySystem.getVertexSet()) {
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

void WaterSupplyManager::maxFlowEachCity() {
    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
        for (Edge* edge : vertex->getAdj()) {
            edge->setFlow(0);
        }
    }
    _waterSupplySystem.addVertex("source");
    _waterSupplySystem.addVertex("target");
    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
        if (vertex->getInfo()[0] == 'R') {
            Reservoir reservoir = _reservoirMap.at(vertex->getInfo());
            _waterSupplySystem.addEdge("source", vertex->getInfo(), reservoir.getMaxDelivery());
        }
        else if (vertex->getInfo()[0] == 'C') {
            _waterSupplySystem.addEdge(vertex->getInfo(), "target", INF);
        }
    }
    edmondsKarp("source", "target");

    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
        double maxFlow = 0;
        if (vertex->getInfo() == "target") {
            for (Edge* edge : vertex->getIncoming()) {
                maxFlow += edge->getFlow();
            }
            std::cout << vertex->getInfo() << " " << maxFlow << std::endl;

        }
    }
    _waterSupplySystem.removeVertex("source");
    _waterSupplySystem.removeVertex("target");
}

void WaterSupplyManager::maxFlowSpecificCity(const std::string &city) {
    maxFlowEachCity();
    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
        if (vertex->getInfo() == city) {
            double maxFlow = 0;
            for (Edge* edge : vertex->getIncoming()) {
                maxFlow += edge->getFlow();
            }
            std::cout << vertex->getInfo() << " " << maxFlow << std::endl;
        }
    }

}

void WaterSupplyManager::checkSuficientFlow() {
    maxFlowEachCity();
    std::cout << "Cities without enough water:" << std::endl;
    for (Vertex* vertex : _waterSupplySystem.getVertexSet()) {
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
                current_difference = e->getWeight()-e->getFlow();
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

}
