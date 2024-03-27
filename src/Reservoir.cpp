#include "Reservoir.h"


std::string Reservoir::getName() const {
    return _name;
}

std::string Reservoir::getMunicipality() const {
    return _municipality;
}

std::string Reservoir::getId() const {
    return _id;
}

std::string Reservoir::getCode() const {
    return _code;
}

int Reservoir::getMaxDelivery() const {
    return _maxDelivery;
}
