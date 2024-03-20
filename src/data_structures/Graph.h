// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"
#include "Vertex.h"
#include "Edge.h"

#define INF std::numeric_limits<double>::max()

class Vertex;
class Edge;

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    [[nodiscard]] Vertex *findVertex(const std::string &in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const std::string &in);
    bool removeVertex(const std::string &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const std::string &sourc, const std::string &dest, double capacity) const;
    bool removeEdge(const std::string &source, const std::string &dest) const;
    bool addBidirectionalEdge(const std::string &sourc, const std::string &dest, double capacity) const;

    [[nodiscard]] int getNumVertex() const;
    [[nodiscard]] std::vector<Vertex *> getVertexSet() const;

    [[nodiscard]] std:: vector<std::string> dfs() const;
    [[nodiscard]] std:: vector<std::string> dfs(const std::string & source) const;
    void dfsVisit(Vertex *v,  std::vector<std::string> & res) const;
    [[nodiscard]] std::vector<std::string> bfs(const std::string & source) const;

    [[nodiscard]] bool isDAG() const;
    bool dfsIsDAG(Vertex *v) const;

    bool addBidirectionalEdgeEdmond(const std::string &sourc, const std::string &dest, double capacity) const;
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    [[nodiscard]] int findVertexIdx(const std::string &in) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

#endif /* DA_TP_CLASSES_GRAPH */