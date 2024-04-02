#ifndef DA_PROJECT_1_INTERFACE_H
#define DA_PROJECT_1_INTERFACE_H

#include "WaterSupplyManager.h"

class Interface {
public:
    /**
     * @brief Constructor default da classe Interface
     */
    Interface();

    /**
     * @brief Executa o programa
     */
    static void run();

private:
    /**
     * @brief Objeto da classe WaterSupplyManager, que contêm toda a informação do sistema de abastecimento de água
     */
    static WaterSupplyManager _waterSupplyManager;

    /**
     * @brief Menu principal do programa
     * @return Número correspondente à ação que o utilizador pretende realizar
     */
    static int displayMainMenu();
};
#endif //DA_PROJECT_1_INTERFACE_H
