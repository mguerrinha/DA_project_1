#ifndef DA_PROJECT_1_STATION_H
#define DA_PROJECT_1_STATION_H

#include <string>

/**
 * @brief Classe que representa uma estação de bombeamento
 */

class Station {
private:
    /// Identificador único da estação de bombeamento
    std::string _id;

    /// Código da estação de bombeamento
    std:: string _code;

public:
    /**
     * @brief Retorna o identificador único da estação de bombeamento
     * @return Identificador único da estação de bombeamento
     */
    [[nodiscard]] std::string getId() const;

    /**
     * @brief Retorna o código da estação de bombeamento
     * @return Código da estação de bombeamento
     */
    [[nodiscard]] std::string getCode() const;

    /**
     * @brief Constructor da classe Station
     * @param id Identificador único da estação de bombeamento
     * @param code Código da estação de bombeamento
     */
    Station (std::string id, std::string code) : _id(std::move(id)), _code(std::move(code)) {};
};

#endif //DA_PROJECT_1_STATION_H
