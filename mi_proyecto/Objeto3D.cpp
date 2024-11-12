#include "Objeto3D.h"
#include <iostream>
#include <algorithm>

// Constructor
Objeto3D::Objeto3D(const std::string& nombre) : nombreMalla(nombre) {}

// Método para reservar memoria a los vértices (equivalente a `agregarPuntos` en code 1)
void Objeto3D::agregarPuntos(int cantidadVertices)
{
    vertices.reserve(cantidadVertices);
}

void Objeto3D::setNombreMalla(const std::string& nombre) {
    nombreMalla = nombre;
}

// Método para reservar memoria a las caras (equivalente a `agregarCarasObjeto` en code 1)
void Objeto3D::agregarCarasObjeto(int cantidadCaras)
{
    caras.reserve(cantidadCaras);
}

// Método para agregar un vértice
void Objeto3D::agregarVertice(float x, float y, float z)
{
    vertices.emplace_back(x, y, z);
}

// Método sobrecargado para agregar un vértice como objeto Vertice
void Objeto3D::agregarVertice(const Vertice& vertice)
{
    vertices.push_back(vertice);
}

// Método para agregar la cantidad de puntos del objeto (equivalente a `agregarPuntosObj` en code 1)
void Objeto3D::agregarPuntosObj(int puntos)
{
    cantidadPuntos = puntos;
}

// Método para agregar una cara
void Objeto3D::agregarCara(const Cara& cara)
{
    caras.push_back(cara);
}

// Método para obtener el nombre del objeto (equivalente a `getNombreMalla` en code 1)
std::string Objeto3D::getNombreMalla() const
{
    return nombreMalla;
}

// Método para obtener la cantidad de puntos (equivalente a `getNumeroPuntos` en code 1)
int Objeto3D::getNumeroPuntos() const
{
    return cantidadPuntos;
}

// Método para obtener la cantidad de vértices (equivalente a `getNumeroVertices` en code 1)
int Objeto3D::getNumeroVertices() const
{
    return vertices.size();
}

// Método para obtener la cantidad de caras (equivalente a `getNumeroCaras` en code 1)
int Objeto3D::getNumeroCaras() const
{
    return caras.size();
}

// Método para obtener la cantidad de aristas (equivalente a `getNumeroAristas` en code 1)
int Objeto3D::getNumeroAristas() const
{
    return aristas.size();
}

// Método para obtener los vértices del objeto (equivalente a `getVertices` en code 1)
const std::vector<Vertice>& Objeto3D::getVertices() const
{
    return vertices;
}

// Método para obtener las caras del objeto (equivalente a `getCaras` en code 1)
const std::vector<Cara>& Objeto3D::getCaras() const
{
    return caras;
}

// Método para leer y mostrar todos los vértices
void Objeto3D::leerVertices() const
{
    std::cout << "Vértices del objeto \"" << nombreMalla << "\":" << std::endl;
    for (int i = 0; i < vertices.size(); ++i)
    {
        const auto& v = vertices[i];
        std::cout << "Vértice " << i + 1 << ": "
                  << v.getX() << ", " << v.getY() << ", " << v.getZ() << std::endl;
        std::cout << std::endl;
    }
}

// Método para obtener punteros a los vértices (equivalente a `getVerticePtr` en code 1)
std::vector<Vertice*> Objeto3D::getVerticePtr()
{
    std::vector<Vertice*> verticesPtr;
    for (Vertice& vertice : vertices)
    {
        verticesPtr.push_back(&vertice);
    }
    return verticesPtr;
}

// Método para calcular las aristas del objeto (equivalente a `calcularAristas` en code 1)
void Objeto3D::calcularAristas()
{
    // Recorrer las caras del objeto
    for (const auto& cara : caras)
    {
        const auto& verticesCara = cara.getVertices();
        int numVerticesCara = verticesCara.size();

        for (int i = 0; i < numVerticesCara; ++i)
        {
            // Obtener los índices de los vértices
            int v1Index = verticesCara[i];
            int v2Index = verticesCara[(i + 1) % numVerticesCara];

            // Obtener las referencias de los vértices
            Vertice* v1 = &vertices[v1Index];
            Vertice* v2 = &vertices[v2Index];

            // Crear una nueva arista
            Arista nuevaArista(v1, v2);

            // Verificar si la arista ya existe
            if (std::find_if(aristas.begin(), aristas.end(),
                [&nuevaArista](const Arista& a) {
                    return (a.getV1() == nuevaArista.getV1() && a.getV2() == nuevaArista.getV2());
                }) == aristas.end()) {
                aristas.push_back(nuevaArista);
            }
        }
    }
}

// Método para establecer el árbol KD
void Objeto3D::setArbolKD(ArbolKD* arbolKD) {
    // Lógica para asignar el árbol KD
    // (Si no se implementa por ahora, se puede dejar vacío)
}

// Método para obtener el árbol KD
ArbolKD* Objeto3D::getArbolKD() const {
    return nullptr; // Se puede cambiar cuando el árbol KD esté implementado
}

// Método para obtener las caras por índice
std::vector<int> Objeto3D::getCaras(int indice) const {
    if (indice >= 0 && indice < caras.size()) {
        return caras[indice].getVertices(); // Asumiendo que `getVertices()` de `Cara` devuelve los índices de los vértices
    }
    return std::vector<int>(); // Devuelve un vector vacío si el índice es inválido
}

// Método para calcular las esquinas del bounding box
std::vector<std::vector<float>> Objeto3D::calcularEsquinasEnvolvente() const {
    if (vertices.empty()) {
        return {};
    }

    // Inicializar valores máximos y mínimos con el primer vértice
    float minX = vertices[0].getX();
    float minY = vertices[0].getY();
    float minZ = vertices[0].getZ();
    float maxX = vertices[0].getX();
    float maxY = vertices[0].getY();
    float maxZ = vertices[0].getZ();

    // Recorrer los vértices y actualizar los valores de mínimo y máximo
    for (const auto& vertice : vertices) {
        if (vertice.getX() < minX) minX = vertice.getX();
        if (vertice.getY() < minY) minY = vertice.getY();
        if (vertice.getZ() < minZ) minZ = vertice.getZ();

        if (vertice.getX() > maxX) maxX = vertice.getX();
        if (vertice.getY() > maxY) maxY = vertice.getY();
        if (vertice.getZ() > maxZ) maxZ = vertice.getZ();
    }

    // Esquinas del cubo envolvente
    std::vector<std::vector<float>> esquinas = {
        {minX, minY, minZ},
        {maxX, minY, minZ},
        {minX, maxY, minZ},
        {maxX, maxY, minZ},
        {minX, minY, maxZ},
        {maxX, minY, maxZ},
        {minX, maxY, maxZ},
        {maxX, maxY, maxZ}
    };

    return esquinas;
}
