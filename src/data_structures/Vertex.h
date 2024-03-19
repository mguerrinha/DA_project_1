//
// Created by miguel on 19-03-2024.
//

#ifndef DA_PROJECT_1_VERTEX_H
#define DA_PROJECT_1_VERTEX_H

#include "Edge.h"
#include <string>
#include <vector>
#include "MutablePriorityQueue.h"

class Edge;

class Vertex {
public:
    explicit Vertex(std::string in);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    [[nodiscard]] std::string getInfo() const;
    [[nodiscard]] std::vector<Edge *> getAdj() const;
    [[nodiscard]] bool isVisited() const;
    [[nodiscard]] bool isProcessing() const;
    [[nodiscard]] unsigned int getIndegree() const;
    [[nodiscard]] double getDist() const;
    [[nodiscard]] Edge *getPath() const;
    [[nodiscard]] std::vector<Edge *> getIncoming() const;

    void setInfo(std::string info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double capacity);
    bool removeEdge(std::string in);
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;
protected:
    std::string info;                // info node
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree{}; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);
};


#endif //DA_PROJECT_1_VERTEX_H
