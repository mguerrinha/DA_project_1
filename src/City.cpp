#include "City.h"

std::string City::getName() const {
    return _name;
}

std::string City::getId() const {
    return _id;
}

std::string City::getCode() const {
    return _code;
}

int City::getDemand() const {
    return _demand;
}

int City::getPopulation() const {
    return _population;
}
