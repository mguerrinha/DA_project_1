#include "Vertex.h"

#include <utility>

Vertex::Vertex(std::string in): info(std::move(in)) {}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

bool Vertex::removeEdge(std::string in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true;
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

std::string Vertex::getInfo() const {
    return this->info;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

Edge * Vertex::addEdge(Vertex *d, double capacity) {
    Edge* newEdge = new Edge(this, d, capacity);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}


void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}
