#include "ManejadorObj.h"
#include <iostream>

ManejadorObj::ManejadorObj() : inicializado(false) {}

void ManejadorObj::agregarObj(const Objeto3D& objeto) {
    // Agregar el objeto a la lista de objetos
    objetos.push_back(new Objeto3D(objeto));

}


bool ManejadorObj::verificarObjeto(const std::string& mesh) {
    for (const auto& obj : objetos) {
        if (obj->getNombreMalla() == mesh) {
            return true;
        }
    }
    return false;
}

Objeto3D* ManejadorObj::obtenerObjeto(const std::string& nombre) {
    for (auto& obj : objetos) {
        if (obj->getNombreMalla() == nombre) {
            return obj;
        }
    }
    return nullptr;
}

bool ManejadorObj::descarObj(const std::string& nombre) {
    for (auto it = objetos.begin(); it != objetos.end(); ++it) {
        if ((*it)->getNombreMalla() == nombre) {
            delete *it; // Liberar la memoria del objeto
            objetos.erase(it); // Eliminar el puntero de la lista
            return true;
        }
    }
    return false;
}

bool ManejadorObj::estaVacio() const {
    return objetos.empty();  // Verifica si no hay objetos
}

std::vector<Objeto3D*> ManejadorObj::obtenerTodosLosObjetos() const {
    return objetos;  // Devuelve una copia del vector con todos los objetos cargados
}

void ManejadorObj::mostrarObj() {
    for (const auto& obj : objetos) {
        std::cout << "Nombre de malla: " << obj->getNombreMalla() << std::endl;
        std::cout << "Número de vértices: " << obj->getNumeroVertices() << std::endl;
        std::cout << "Número de caras: " << obj->getNumeroCaras() << std::endl;
        std::cout << "Número de aristas: " << obj->getNumeroAristas() << std::endl;
    }
}

std::vector<Vertice> ManejadorObj::obtenerVertices() const{
    std::vector<Vertice> todosLosVertices; 

    for (const auto& objeto : objetos) {

        const std::vector<Vertice>& verticesDelObjeto = objeto->getVertices();

        todosLosVertices.insert(todosLosVertices.end(), verticesDelObjeto.begin(), verticesDelObjeto.end());
    }

    return todosLosVertices; 
}
