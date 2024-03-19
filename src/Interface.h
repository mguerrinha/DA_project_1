#ifndef DA_PROJECT_1_INTERFACE_H
#define DA_PROJECT_1_INTERFACE_H

#include "WaterSupplyManager.h"

class Interface {
public:
    Interface();

    static void run();

private:
    static WaterSupplyManager _waterSupplyManager;

    static int displayMainMenu();
};
#endif //DA_PROJECT_1_INTERFACE_H
