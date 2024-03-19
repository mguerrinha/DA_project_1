//
// Created by miguel on 18-03-2024.
//

#ifndef DA_PROJECT_1_CITY_H
#define DA_PROJECT_1_CITY_H

#include <string>

class City {
private:
    std::string _name;

    std::string _id;

    std::string _code;

    std::string _demand;

    std::string _population;

public:
    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string getId() const;

    [[nodiscard]] std::string getCode() const;

    [[nodiscard]] std::string getDemand() const;

    [[nodiscard]] std::string getPopulation() const;

    City (std::string name, std::string id, std::string code, std::string demand, std::string population) : _name(std::move(name)), _id(std::move(id)), _code(std::move(code)),
                                                                                                            _demand(std::move(demand)), _population(std::move(population)) {};
};

#endif //DA_PROJECT_1_CITY_H
