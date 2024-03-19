cmake_minimum_required(VERSION 3.27)
project(DA_project_1)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(DA_project_1
        data_structures/MutablePriorityQueue.h
        data_structures/UFDS.cpp
        data_structures/UFDS.h
        src/City.h
        src/interface.h
        src/interface.cpp
        src/main.cpp
        src/Reservoir.h
        src/Station.h
        data_structures/Graph.h)