#include "Cara.h"
#include <iostream>

// Metodo para agregar vertices
void Cara::agregarVertice(int indice) {
    vertices.push_back(indice);
}

// Metodo para obtener los vertices de una cara
const std::vector<int>& Cara::getVertices() const {
    return vertices;
}
