cmake_minimum_required(VERSION 3.29)
project(mi_proyecto)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mi_proyecto
    ArbolKD.cpp
    ArbolKD.h
    Arista.cpp
    Arista.h
    Cara.cpp
    Cara.h
    main.cpp
    ManejadorObj.cpp
    ManejadorObj.h
    NodoKD.cpp
    NodoKD.h
    Objeto3D.cpp
    Objeto3D.h
    sistema.cpp
    sistema.h
    Vertice.cpp
    Vertice.h)
