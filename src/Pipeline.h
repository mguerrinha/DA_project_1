#ifndef DA_PROJECT_1_PIPELINE_H
#define DA_PROJECT_1_PIPELINE_H

#include <string>

/**
 * @brief Classe que representa um tubo de água
 */

class Pipeline {
private:
    /// Serviço de origem de um tubo de água
    std::string _sourc;

    /// Serviço alvo de um tubo de água
    std::string _dest;

    /// Capacidade de um tubo de água
    int _capacity;

    /// Direção de um tubo de água ( 1 - Unidiretional | 0 - Bidiretional)
    int _direction;

public:
    /**
     * @brief Retorna o serviço de origem de um tubo de água
     * @return Serviço de origem de um tubo de água
     */
    [[nodiscard]] std::string getSourc() const;

    /**
     * @brief Retorna o serviço alvo de um tubo de água
     * @return Serviço alvo de um tubo de água
     */
    [[nodiscard]] std::string getDest() const;

    /**
     * @brief Retorna a capacidade de um tubo de água
     * @return Capacidade de um tubo de água
     */
    [[nodiscard]] int getCapacity() const;

    /**
     * @brief Retorna a direção de um tubo de água
     * @return Direção de um tubo de água
     */
    [[nodiscard]] int getDirection() const;
};


#endif //DA_PROJECT_1_PIPELINE_H
