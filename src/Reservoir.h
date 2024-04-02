#ifndef DA_PROJECT_1_RESERVOIR_H
#define DA_PROJECT_1_RESERVOIR_H

#include <string>

/**
 * @brief Classe que representa um reservatório de água
 */

class Reservoir {
private:
    /// Nome do reservatório
    std::string _name;

    /// Distrito do reservatório
    std::string _municipality;

    /// Identificador único do reservatório
    std::string _id;

    /// Código do reservatório
    std::string _code;

    /// Entrega máxima de água do reservatório
    int _maxDelivery;

public:
    /**
     * @brief Retorna o nome do reservatório
     * @return Nome do reservatório
     */
    [[nodiscard]] std::string getName() const;

    /**
     * @brief Retorna o distrito do reservatório
     * @return Distrito do reservatório
     */
    [[nodiscard]] std::string getMunicipality() const;

    /**
     * @brief Retorna o identificador único do reservatório
     * @return Identificador único do reservatório
     */
    [[nodiscard]] std::string getId() const;

    /**
     * @brief Retorna o código do reservatório
     * @return Código do reservatório
     */
    [[nodiscard]] std::string getCode() const;

    /**
     * @brief Retorna a entrega máxima de água do reservatório
     * @return Entrega máxima de água do reservatório
     */
    [[nodiscard]] int getMaxDelivery() const;

    /**
     * @brief Constructor da classe Reservoir
     * @param name Nome do reservatório
     * @param municipality Distrito do reservatório
     * @param id Identificador único do reservatório
     * @param code Código do reservatório
     * @param maxDelivery Entrega máxima de água do reservatório
     */
    Reservoir (std::string name, std::string municipality, std::string id, std::string code, int maxDelivery) : _name(std::move(name)), _municipality(std::move(municipality)), _id(std::move(id)),
                                                                                                                        _code(std::move(code)), _maxDelivery(maxDelivery) {};
};

#endif //DA_PROJECT_1_RESERVOIR_H
