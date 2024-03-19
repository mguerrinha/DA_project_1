//
// Created by miguel on 18-03-2024.
//

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
};

#endif //DA_PROJECT_1_STATION_H
