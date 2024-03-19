//
// Created by miguel on 18-03-2024.
//

#ifndef DA_PROJECT_1_RESERVOIR_H
#define DA_PROJECT_1_RESERVOIR_H

#include <string>

class Reservoir {
private:
    std::string _name;

    std::string _municipality;

    std::string _id;

    std::string _code;

    std::string _maxDelivery;

public:
    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string getMunicipality() const;

    [[nodiscard]] std::string getId() const;

    [[nodiscard]] std::string getCode() const;

    [[nodiscard]] std::string getMaxDelivery() const;

};

#endif //DA_PROJECT_1_RESERVOIR_H
