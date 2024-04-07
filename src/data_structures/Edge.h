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
    Vertex * dest;

    double weight;

    bool selected = false;

    Vertex *orig;

    Edge *reverse = nullptr;

    double flow{};
};


#endif //DA_PROJECT_1_EDGE_H
