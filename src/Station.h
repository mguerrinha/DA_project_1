#ifndef DA_PROJECT_1_STATION_H
#define DA_PROJECT_1_STATION_H

#include <string>

class Station {
private:
    std::string _id;

    std:: string _code;

public:
    [[nodiscard]] std::string getId() const;

    [[nodiscard]] std::string getCode() const;

    Station (std::string id, std::string code) : _id(std::move(id)), _code(std::move(code)) {};
};

#endif //DA_PROJECT_1_STATION_H
