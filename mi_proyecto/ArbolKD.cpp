#include "ArbolKD.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits> 
// Constructor
// Constructor por defecto
ArbolKD::ArbolKD() 
    : raiz(nullptr) {}  // Inicializa el árbol como vacío

// Constructor con lista de vértices
ArbolKD::ArbolKD(const std::vector<Vertice*>& vertices)
{
    raiz = construirArbol(const_cast<std::vector<Vertice*>&>(vertices), 0);
}

ArbolKD::~ArbolKD()
{
    destruirArbol(raiz);
}

void ArbolKD::destruirArbol(NodoKD* nodo)
{
    if(nodo != nullptr)
    {
        destruirArbol(nodo->getHijoIzquierdo());
        destruirArbol(nodo->getHijoDerecho());
        delete nodo;
    }
}

NodoKD* ArbolKD::construirArbol(std::vector<Vertice*>& vertices, int profundidad)
{
    if(vertices.empty()) return nullptr;

    int eje = profundidad % 3;
    std::sort(vertices.begin(), vertices.end(), [eje](const Vertice* v1, const Vertice* v2)
    {
        if (eje == 0) return v1->getX() < v2->getX();  // Comparar X
        else if (eje == 1) return v1->getY() < v2->getY();  // Comparar Y
        else return v1->getZ() < v2->getZ();  // Comparar Z
    });

    int mediana = vertices.size() / 2;
    NodoKD* nodo = new NodoKD(vertices[mediana]);

    std::vector<Vertice*> izquierda(vertices.begin(), vertices.begin() + mediana);
    std::vector<Vertice*> derecha(vertices.begin() + mediana + 1, vertices.end());

    nodo->setHijoIzquierdo(construirArbol(izquierda, profundidad + 1));
    nodo->setHijoDerecho(construirArbol(derecha, profundidad + 1));

    return nodo;
}

void ArbolKD::preOrden() const
{
    std::cout << "Recorrido Preorden del Arbol KD:" << std::endl;
    preOrdenRecursivo(raiz);  // Llama al m�todo recursivo desde la ra�z
}

// M�todo recursivo para realizar el recorrido en preorden
void ArbolKD::preOrdenRecursivo(NodoKD* nodo) const
{
    if (nodo == nullptr)
    {
        return;  // Caso base: si el nodo es nulo, se termina la recursi�n
    }

    // Imprime la informaci�n del v�rtice del nodo actual
    Vertice* v = nodo->getVertice();
    std::cout << "Vertice: (" << v->getX() << ", " << v->getY() << ", " << v->getZ() << ")" << std::endl;

    // Recursivamente recorrer el sub�rbol izquierdo
    preOrdenRecursivo(nodo->getHijoIzquierdo());

    // Recursivamente recorrer el sub�rbol derecho
    preOrdenRecursivo(nodo->getHijoDerecho());
}

// M�todo p�blico para encontrar el v�rtice m�s cercano
Vertice* ArbolKD::VerticeMasCercano(const Vertice& punto, const std::string& nombreObjeto)
{
    if (raiz == nullptr)
    {
        std::cout << "El arbol esta vacio." << std::endl;
        return nullptr;
    }
    Vertice* mejorVertice = nullptr;
    float mejorDistancia = std::numeric_limits<float>::max();

    // Llama a la funci�n de b�squeda
    buscarVerticeMasCercano(raiz, punto, 0, mejorVertice, mejorDistancia);
    return mejorVertice;
}

// M�todo auxiliar para buscar el v�rtice m�s cercano en el �rbol
void ArbolKD::buscarVerticeMasCercano(NodoKD* nodo, const Vertice& punto, int profundidad, Vertice*& mejorVertice, float& mejorDistancia)
{
    if (nodo == nullptr)
    {
        return;
    }

    // Calcular la distancia actual
    float distanciaActual = distanciaEuclidiana(punto, *nodo->getVertice());
    if (distanciaActual < mejorDistancia)
    {
        mejorDistancia = distanciaActual;
        mejorVertice = nodo->getVertice(); // Asignar el puntero directamente
    }

    // Determinar si buscar en el sub�rbol izquierdo o derecho
    int eje = profundidad % 3;
    NodoKD* ladoCercano = (punto.getX() < nodo->getVertice()->getX()) ? nodo->getHijoIzquierdo() : nodo->getHijoDerecho();
    NodoKD* ladoLejano = (punto.getX() < nodo->getVertice()->getX()) ? nodo->getHijoDerecho() : nodo->getHijoIzquierdo();

    // Recursi�n en el sub�rbol cercano
    buscarVerticeMasCercano(ladoCercano, punto, profundidad + 1, mejorVertice, mejorDistancia);

    // Verificar si debemos explorar el lado lejano
    if (fabs(punto.getX() - nodo->getVertice()->getX()) < mejorDistancia)
    {
        buscarVerticeMasCercano(ladoLejano, punto, profundidad + 1, mejorVertice, mejorDistancia);
    }
}

float ArbolKD::distanciaEuclidiana(const Vertice& v1, const Vertice& v2)
{
    float dx = v1.getX() - v2.getX();
    float dy = v1.getY() - v2.getY();
    float dz = v1.getZ() - v2.getZ();
    return sqrt(dx * dx + dy * dy + dz * dz);
}

void ArbolKD::insertar(const Vertice* vertice) {
    raiz = insertarRecursivo(raiz, const_cast<Vertice*>(vertice), 0);  // Llamada recursiva con la raíz actual
}



// Función recursiva para insertar un vértice en el árbol KD
NodoKD* ArbolKD::insertarRecursivo(NodoKD* nodo, Vertice* vertice, int profundidad) {
    if (nodo == nullptr) {
        return new NodoKD(vertice);  // Crear un nuevo nodo si llegamos a un espacio vacío
    }

    // Determinar el eje actual basado en la profundidad
    int eje = profundidad % 3;

    // Comparar el vértice en el eje actual y decidir a qué subárbol ir
    if (eje == 0) {
        if (vertice->getX() < nodo->getVertice()->getX()) {
            nodo->setHijoIzquierdo(insertarRecursivo(nodo->getHijoIzquierdo(), vertice, profundidad + 1));
        } else {
            nodo->setHijoDerecho(insertarRecursivo(nodo->getHijoDerecho(), vertice, profundidad + 1));
        }
    } else if (eje == 1) {
        if (vertice->getY() < nodo->getVertice()->getY()) {
            nodo->setHijoIzquierdo(insertarRecursivo(nodo->getHijoIzquierdo(), vertice, profundidad + 1));
        } else {
            nodo->setHijoDerecho(insertarRecursivo(nodo->getHijoDerecho(), vertice, profundidad + 1));
        }
    } else {
        if (vertice->getZ() < nodo->getVertice()->getZ()) {
            nodo->setHijoIzquierdo(insertarRecursivo(nodo->getHijoIzquierdo(), vertice, profundidad + 1));
        } else {
            nodo->setHijoDerecho(insertarRecursivo(nodo->getHijoDerecho(), vertice, profundidad + 1));
        }
    }

    return nodo;  // Retornar el nodo actualizado
}


