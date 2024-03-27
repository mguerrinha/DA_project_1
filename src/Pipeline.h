#ifndef DA_PROJECT_1_PIPELINE_H
#define DA_PROJECT_1_PIPELINE_H

#include <string>

class Pipeline {
private:
    std::string _sourc;

    std::string _dest;

    int _capacity;

    int _direction;

public:
    [[nodiscard]] std::string getSourc() const;

    [[nodiscard]] std::string getDest() const;

    [[nodiscard]] int getCapacity() const;

    [[nodiscard]] int getDirection() const;
};


#endif //DA_PROJECT_1_PIPELINE_H
