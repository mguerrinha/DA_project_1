#ifndef DA_PROJECT_1_CITY_H
#define DA_PROJECT_1_CITY_H

#include <string>

/**
 * @brief Classe que representa uma cidade ou local de entrega
 */

class City {
private:
    /// Nome de uma cidade
    std::string _name;

    /// Identificador único de uma cidade
    std::string _id;

    /// Código de uma cidade
    std::string _code;

    /// Demanda de uma cidade
    int _demand;

    /// População de uma cidade
    int _population;

public:
    /**
     * @brief Retorna o nome de uma cidade
     * @return Nome de uma cidade
     */
    [[nodiscard]] std::string getName() const;

    /**
     * @brief Retorna o identificador único de uma cidade
     * @return Identificador único de uma cidade
     */
    [[nodiscard]] std::string getId() const;

    /**
     * @brief Retorna o código de uma cidade
     * @return Código de uma cidade
     */
    [[nodiscard]] std::string getCode() const;

    /**
     * @brief Retorna a demanda de uma cidade
     * @return Demanda de uma cidade
     */
    [[nodiscard]] int getDemand() const;

    /**
     * @brief Retorna a população de uma cidade
     * @return População de uma cidade
     */
    [[nodiscard]] int getPopulation() const;

    /**
     * @brief Constructor da classe City
     * @param name Nome de uma cidade
     * @param id Identificador único de uma cidade
     * @param code Código de uma cidade
     * @param demand Demanda de uma cidade
     * @param population População de uma cidade
     */
    City (std::string name, std::string id, std::string code, int demand, int population) : _name(std::move(name)), _id(std::move(id)), _code(std::move(code)),
                                                                                                            _demand(demand), _population(population) {};
};

#endif //DA_PROJECT_1_CITY_H
