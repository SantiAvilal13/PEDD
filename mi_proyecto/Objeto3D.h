#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "Arista.h"
#include "Cara.h"
#include "Vertice.h"
#include <string>
#include <vector>
#include "ArbolKD.h"

// Definición de atributos y métodos de Objeto3D
class Objeto3D {
public:
  Objeto3D(const std::string &nombre);

  // Métodos para agregar vértices y caras
  void agregarVertice(float x, float y, float z);
  void agregarVertice(
      const Vertice &vertice); // Sobrecarga para agregar un objeto Vertice
  void agregarPuntosObj(int puntos);
  void agregarCara(const Cara &cara);
  void
  setVertices(const std::vector<float> &vert); // Reservar memoria para vértices
  void agregarPuntos(
      int cantidadVertices); // Método para reservar memoria para puntos
  void agregarCarasObjeto(
      int cantidadCaras); // Método para reservar memoria para caras

  // Métodos para obtener y establecer propiedades
  std::string getNombreMalla() const;
  int getNumeroPuntos() const;
  int getNumeroVertices() const;
  int getNumeroCaras() const;
  int getNumeroAristas() const;
  void setNombreMalla(const std::string& nombre);
  const std::vector<Vertice> &getVertices() const;
  const std::vector<Cara> &getCaras() const;
  std::vector<int>
  getCaras(int indice) const; // Nuevo método para obtener las caras
  void leerVertices() const;

  // Métodos para manejar el KDTree (aunque no se implementan en este código)
void setArbolKD(ArbolKD* arbolKD);
ArbolKD* getArbolKD() const;
std::vector<Vertice*> getVerticePtr();


  // Métodos adicionales
  void calcularAristas();
  std::vector<std::vector<float>> calcularEsquinasEnvolvente() const;

private:
  std::string nombreMalla;
  std::vector<Vertice> vertices;
  std::vector<Cara> caras;
  std::vector<Arista> aristas;
  int cantidadPuntos = 0;
};

#endif // OBJETO3D_H
