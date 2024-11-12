#include "Vertice.h"
#include <iostream>

// Constructor
Vertice::Vertice(float x, float y, float z) : x(x), y(y), z(z){}

// M�todo para obtener eje x
float Vertice::getX() const
{
    return x;
}

// M�todo para obtener eje y
float Vertice::getY() const
{
    return y;
}

// M�todo para obtener eje z
float Vertice::getZ() const
{
    return z;
}

// M�todo para asignar eje x
void Vertice::setX(float nuevaX)
{
    x = nuevaX;
}

// M�todo para asignar eje y
void Vertice::setY(float nuevaY)
{
    y = nuevaY;
}

// M�todo para asignar eje z
void Vertice::setZ(float nuevaZ)
{
    z = nuevaZ;
}

// M�todo para leer y mostrar todos los v�rtices
void Vertice::mostrarVertices() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}


