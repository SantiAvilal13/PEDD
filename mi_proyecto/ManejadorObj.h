#ifndef MANEJADOROBJ_H
#define MANEJADOROBJ_H

#include "ArbolKD.h"
#include "Objeto3D.h"
#include <string>
#include <vector>

class ManejadorObj {
private:
  std::vector<Objeto3D *> objetos; // Almacena punteros a objetos 3D
  bool inicializado; // Indica si el manejador ha sido inicializado
  ArbolKD arbolKD;   // Instancia del objeto ArbolKD
public:
  ManejadorObj();

  void agregarObj(const Objeto3D &objeto);
  bool verificarObjeto(const std::string &mesh);
  Objeto3D *obtenerObjeto(const std::string &nombre);
  bool descarObj(const std::string &nombre);

  bool estaVacio() const; // Método para verificar si el manejador está vacío
  std::vector<Objeto3D *> obtenerTodosLosObjetos(); // Devuelve todos los objetos cargados
  void mostrarObj();
  std::vector<Vertice> obtenerVertices() const;
};

#endif // MANEJADOROBJ_H
