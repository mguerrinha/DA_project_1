#ifndef DA_PROJECT_1_WATERSUPPLYMANAGER_H
#define DA_PROJECT_1_WATERSUPPLYMANAGER_H

#include "data_structures/Graph.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "City.h"
#include "Reservoir.h"
#include "Station.h"
#include <cmath>

/**
 * @brief Classe que representa uma sistema de gestão de abastecimento de água
 */

class WaterSupplyManager {
private:
    /// Representa o sistema de abastecimento de água como um grafo
    Graph _waterSupplySystem;

    /// Hash table tendo o código de uma cidade associado a um objeto CIty
    std::unordered_map<std::string, City> _cityMap;

    /// Hash table tendo o código de uma estação de bombeamento associado a um objeto Station
    std::unordered_map<std::string, Station> _stationMap;

    /// Hash table tendo o código de um reservatório de água associado a um objeto Reservoir
    std::unordered_map<std::string, Reservoir> _reservoirMap;

    double ratio;

public:
    /**
     * @brief Obtém o ratio
     * @return Ratio
     */
    double getRatio() const;

    /**
     * @brief Redefine o valor do ratio
     * @param ratio Ratio a definir
     */
    void setRatio(double ratio);

    /**
     * @brief Constructor default da classe WaterSupplyManager
     */
    WaterSupplyManager();

    /**
     * @brief Carrega as informações sobre as cidades a partir de um arquivo CSV
     * Complexidade : O(N)
     * @param file
     */
    void load_cities(const std::string &file);

    /**
     * @brief Carrega as informações sobre as estações de bombeamento a partir de um arquivo CSV
     * Complexidade : O(N)
     * @param file
     */
    void load_stations(const std::string &file);

    /**
     * @brief Carrega as informações sobre os reservatórios de água a partir de um arquivo CSV
     * Complexidade : O(N)
     * @param file
     */
    void load_reservoirs(const std::string &file);

    /**
     * @brief Carrega as informações sobre os tubos de água a partir de um arquivo CSV
     * Complexidade : O(N)
     * @param file
     */
    void load_pipes(const std::string &file);

    /**
     * @brief Obtém o grafo que representa o sistema de gestão de abastecimento de água
     * @return Grafo que representa o sistema de gestão de abastecimento de água
     */
    Graph getWaterSupplySystem();

    /**
     * @brief Avalia o impacto que teria a remoção de um water reservoir
     * Complexidade: O(E + (VE + (V * (E^2)) + 3V) + N)
     * @param reservoirToRemove Reservatório a remover
     */
    void evaluateReservoirImpact(const std::string& reservoirToRemove);

    /**
     * @brief Obtém a hash table associada às cidades
     * @return Hash table associada às cidades
     */
    std::unordered_map<std::string, City> &getCityMap();

    /**
     * @brief Obtém a hash table associada às estações de bombeamento
     * @return Hash table associada às estações de bombeamento
     */
    std::unordered_map<std::string, Station> &getStationMap();

    /**
     * @brief Obtém a hash table associada aos reservatórios de água
     * @return Hash table associada aos reservatórios de água
     */
    std::unordered_map<std::string, Reservoir> &getReservoirMap();

    /**
     * @brief Método auxiliar ao Edmonds Karp que cria o residual graph com as respectivas residual edges
     * Complexidade : O(V + VE)
     * @param graph Grafo cujas informações irão ser copiadas
     * @return Residual graph do grafo pretendido
     */
    Graph* copyGraphEdmonds(Graph* graph);

    /**
     * @brief Copia as informações de um grafo para outro
     * Complexidade: O(V + 2VE)
     * @param graph Grafo cujas informações irão ser copiadas
     * @return Cópia do grafo pretendido
     */
    Graph* copyGraphAux(Graph* graph);

    /**
     * @brief Realiza o algoritmo BFS para encontrar possíveis augmenting paths de uma source até um target
     * Complexidade: O(V + E)
     * @param graph Grafo a ser percorrido
     * @param source Vertex de origem
     * @param target Vertex alvo
     * @return True se for encontrado um path, falso caso contrário
     */
    bool bfsEdmondsKarp(Graph* graph, Vertex *source, Vertex *target);

    /**
     * @brief Realiza o algoritmo de Edmonds-Karp para encontrar o max flow entre dois pontos
     * Complexidade: O(V * (E^2))
     * @param source Vertex de origem
     * @param target Vertex alvo
     */
    void edmondsKarp(Graph* graph, const std::string &source, const std::string &target);

    /**
     * @brief Verifica o max flow total do sistema
     * Complexidade: O(VE + (V * (E^2)) + 2V)
     */
    void maxFlowEachCity(Graph* graph, double *maxFlow);

    /**
     * @brief Verifica o max flow que atinge uma certa cidade
     * Complexidade: O(VE + (V * (E^2)) + 3V)
     * @param city
     */
    void maxFlowSpecificCity(Graph* graph, const std::string &city);

    /**
     * @brief Verifica as cidades cujo que não receberam as quantidades de água desejadas, tendo em conta a sua demanda
     * Complexidade: O(VE + (V * (E^2)) + 3V)
     */
    void checkSuficientFlow(Graph* graph);

    /**
     * @brief Analisa a média, variância e diferença máxima entre a capacidade e o flow que percorrem as pipelines
     * Complexidade: O(2VE + 2N)
     */
    void analysisMetrics();

    /**
     * @brief Função que balanceia o flow da network de forma a baixar a média, variância ou diferença máxima entre a capacidade e o flow das pipelines
     * Complexidade: O(VE + V(E + E))
     */
    void balanceFlow();

    /**
     * @brief Analisa as cidades mais afetadas em caso de uma pumping station ser removida
     * Complexidade: O((2+V)(VE + (V * (E^2)) + 2V) + 2VE + N^2 + N)
     */
    void periodic_maintenance_pumping_stations();

    /**
     * @brief Analisa as cidades mais afetadas em caso de uma pipeline ser removida
     * Complexidade:  O(2(VE + (V * (E^2)) + 2V) + 2VE + N^2)
     * @param src Source da pipeline a ser removida
     * @param dest Destiny da pipeline a ser removida
     */
    void pipeline_failures(const std::string& src, const std::string& dest);

    /**
     * @brief Salva os flows associados a cada cidade (tendo cada uma nome e código) num ficheiro csv
     * Complexidade: O(VE)
     */
    void saveResultsToFile();

    /**
     * @brief Verifica a diferença de outcoming de flow com o incoming flow de um Vertex
     * Complexidade: O(2E)
     * @param ps Vertex a utilizar
     * @param dif Diferença entre o incoming e o outcoming flow
     * @return Verdadeiro se o outcoming flow for igual ao incoming flow, falso caso contrário
     */
    bool fullDeliveryPS(Vertex* ps, double *dif);
};

#endif //DA_PROJECT_1_WATERSUPPLYMANAGER_H
