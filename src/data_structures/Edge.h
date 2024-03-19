//
// Created by miguel on 19-03-2024.
//

#ifndef DA_PROJECT_1_EDGE_H
#define DA_PROJECT_1_EDGE_H

#include "Vertex.h"

class Vertex;

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double capacity);

    [[nodiscard]] Vertex * getDest() const;
    [[nodiscard]] double getWeight() const;
    [[nodiscard]] bool isSelected() const;
    [[nodiscard]] Vertex * getOrig() const;
    [[nodiscard]] Edge * getReverse() const;
    [[nodiscard]] double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow{}; // for flow-related problems
};


#endif //DA_PROJECT_1_EDGE_H
