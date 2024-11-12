#ifndef VERTICE_H
#define VERTICE_H

#include <vector>
#include <string>

//Definici�n de atributos y m�todos de Vertice
class Vertice
{
public:
    Vertice(float x, float y, float z);
    float getX() const;
    float getY() const;
    float getZ() const;
    void setX(float nuevoX);
    void setY(float nuevoY);
    void setZ(float nuevoZ);
    void mostrarVertices() const;

private:
    float x,y,z;
};

#endif // VERTICE_H
