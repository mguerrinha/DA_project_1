#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "Vertex.h"
#include "Edge.h"

#define INF std::numeric_limits<double>::max()

class Vertex;
class Edge;

class Graph {
public:
    [[nodiscard]] Vertex *findVertex(const std::string &in) const;

    bool addVertex(const std::string &in);

    bool removeVertex(const std::string &in);

    bool addEdge(const std::string &sourc, const std::string &dest, double capacity) const;

    bool removeEdge(const std::string &source, const std::string &dest) const;

    [[nodiscard]] std::vector<Vertex *> getVertexSet() const;

    bool addBidirectionalEdgeEdmond(const std::string &sourc, const std::string &dest, double capacity) const;

protected:
    std::vector<Vertex *> vertexSet;
};

#endif /* DA_TP_CLASSES_GRAPH */