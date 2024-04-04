#ifndef DA_PROJECT_1_WATERSUPPLYMANAGER_H
#define DA_PROJECT_1_WATERSUPPLYMANAGER_H

#include "data_structures/Graph.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "City.h"
#include "Pipeline.h"
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

public:
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
    void maxFlowEachCity(Graph* graph, double *auxFlow);

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
     * Complexidade: O(...)
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
};

#endif //DA_PROJECT_1_WATERSUPPLYMANAGER_H
