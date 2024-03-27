#ifndef DA_PROJECT_1_CITY_H
#define DA_PROJECT_1_CITY_H

#include <string>

class City {
private:
    std::string _name;

    std::string _id;

    std::string _code;

    int _demand;

    int _population;

public:
    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string getId() const;

    [[nodiscard]] std::string getCode() const;

    [[nodiscard]] int getDemand() const;

    [[nodiscard]] int getPopulation() const;

    City (std::string name, std::string id, std::string code, int demand, int population) : _name(std::move(name)), _id(std::move(id)), _code(std::move(code)),
                                                                                                            _demand(demand), _population(population) {};
};

#endif //DA_PROJECT_1_CITY_H
