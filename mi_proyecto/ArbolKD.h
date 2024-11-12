
#ifndef ARBOLKD_H
#define ARBOLKD_H

#include "NodoKD.h"
#include "Vertice.h"
#include <vector>

//Definici�n de atributos y m�todos de ArbolKD
class ArbolKD
{
public:
    ArbolKD();
    ArbolKD(const std::vector<Vertice*>& vertices);
    ~ArbolKD();
    Vertice* VerticeMasCercano(const Vertice& punto,const std::string& nombreObjeto);
	float distanciaEuclidiana(const Vertice& v1, const Vertice& v2);
    void preOrden() const;
 void insertar(const Vertice* vertice);  // Método para insertar un vértice
 NodoKD* insertarRecursivo(NodoKD* nodo, Vertice* vertice, int profundidad);
private:
    NodoKD* raiz;
    NodoKD* construirArbol(std::vector<Vertice*>& vertices, int profundidad);
    void preOrdenRecursivo(NodoKD* nodo) const;
    void destruirArbol(NodoKD* nodo);
    void buscarVerticeMasCercano(NodoKD* nodo, const Vertice& punto, int profundidad, Vertice*& mejorVertice, float& mejorDistancia);

};

#endif
