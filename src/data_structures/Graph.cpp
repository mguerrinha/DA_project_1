#include "Graph.h"

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

Vertex * Graph::findVertex(const std::string &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}

bool Graph::addVertex(const std::string &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(in));
    return true;
}

bool Graph::removeVertex(const std::string &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

bool Graph::addEdge(const std::string &sourc, const std::string &dest, double capacity) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, capacity);
    return true;
}

bool Graph::removeEdge(const std::string &sourc, const std::string &dest) const {
    Vertex * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

bool Graph::addBidirectionalEdgeEdmond(const std::string &sourc, const std::string &dest, double capacity) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, capacity);
    auto e2 = v2->addEdge(v1, 0);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}