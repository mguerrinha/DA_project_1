cmake_minimum_required(VERSION 3.27)
project(DA_project_1)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(DA_project_1
        src/data_structures/MutablePriorityQueue.h
        src/data_structures/UFDS.cpp
        src/data_structures/UFDS.h
        src/City.h
        src/Interface.h
        src/Interface.cpp
        src/main.cpp
        src/Reservoir.h
        src/Station.h
        src/data_structures/Graph.h
        src/Station.cpp
        src/City.cpp
        src/Reservoir.cpp
        src/WaterSupplyManager.h
        src/WaterSupplyManager.cpp
        src/Pipeline.h
        src/Pipeline.cpp
        src/data_structures/Edge.h
        src/data_structures/Edge.cpp
        src/data_structures/Graph.cpp
        src/data_structures/Vertex.h
        src/data_structures/Vertex.cpp)