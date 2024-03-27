#include "Pipeline.h"

std::string Pipeline::getSourc() const {
    return _sourc;
}

std::string Pipeline::getDest() const {
    return _dest;
}

int Pipeline::getCapacity() const {
    return _capacity;
}

int Pipeline::getDirection() const {
    return _direction;
}
