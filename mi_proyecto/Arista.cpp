#include "Arista.h"
#include <iostream>
#include <algorithm>

// Constructor
Arista::Arista(Vertice* v1, Vertice* v2)
{
    this->v1 = std::min(v1,v2);
    this->v2 = std::max(v1,v2);


}

Vertice* Arista::getV1() const
{
    return v1;
}


Vertice* Arista::getV2() const
{
    return v2;
}


void Arista::mostrarArista() const
{
    std::cout << "Arista: ";
    v1->mostrarVertices();
    std::cout << " a ";
    v2->mostrarVertices();
    std::cout << std::endl;
}
