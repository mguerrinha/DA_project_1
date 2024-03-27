#ifndef DA_PROJECT_1_RESERVOIR_H
#define DA_PROJECT_1_RESERVOIR_H

#include <string>

class Reservoir {
private:
    std::string _name;

    std::string _municipality;

    std::string _id;

    std::string _code;

    int _maxDelivery;

public:
    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string getMunicipality() const;

    [[nodiscard]] std::string getId() const;

    [[nodiscard]] std::string getCode() const;

    [[nodiscard]] int getMaxDelivery() const;

    Reservoir (std::string name, std::string municipality, std::string id, std::string code, int maxDelivery) : _name(std::move(name)), _municipality(std::move(municipality)), _id(std::move(id)),
                                                                                                                        _code(std::move(code)), _maxDelivery(maxDelivery) {};
};

#endif //DA_PROJECT_1_RESERVOIR_H
