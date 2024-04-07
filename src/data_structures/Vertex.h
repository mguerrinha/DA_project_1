#ifndef DA_PROJECT_1_VERTEX_H
#define DA_PROJECT_1_VERTEX_H

#include "Edge.h"
#include <string>
#include <vector>
#include <iostream>

class Edge;

class Vertex {
public:
    explicit Vertex(std::string in);

    bool operator<(Vertex & vertex) const;

    [[nodiscard]] std::string getInfo() const;

    [[nodiscard]] std::vector<Edge *> getAdj() const;

    [[nodiscard]] bool isVisited() const;

    [[nodiscard]] Edge *getPath() const;

    [[nodiscard]] std::vector<Edge *> getIncoming() const;

    void setVisited(bool visited);

    void setPath(Edge *path);

    Edge * addEdge(Vertex *dest, double capacity);

    bool removeEdge(std::string in);

    void removeOutgoingEdges();

protected:
    std::string info;

    std::vector<Edge *> adj;

    bool visited = false;

    bool processing = false;

    unsigned int indegree{};

    double dist = 0;

    Edge *path = nullptr;

    std::vector<Edge *> incoming;

    void deleteEdge(Edge *edge);
};


#endif //DA_PROJECT_1_VERTEX_H
