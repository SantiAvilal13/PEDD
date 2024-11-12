#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "ManejadorObj.h"
#include "ArbolKD.h"

class Sistema {
private:
    bool ejecutando;
    ManejadorObj manejadorObj; 
    void mostrarAyuda();
    void mostrarAyudaComando(const std::string& comando);
    void cargar(const std::string& nombre_archivo);
    void listado();
    void envolvente(const std::string& nombre_objeto);
    void envolventeGlobal();
    void descargar(const std::string& nombre_objeto);
    void guardar(const std::string& nombre_objeto, const std::string& nombre_archivo);
    void vCercano(float px, float py, float pz, const std::string& nombre_objeto);
    void vCercanoGlobal(float px, float py, float pz);
    void vCercanosCaja(const std::string& nombre_objeto);
    void rutaCorta(int i1, int i2, const std::string& nombre_objeto);
    void rutaCortaCentro(int i1, const std::string& nombre_objeto);
    bool existeObjeto(const std::string& nombre_objeto);  
    ArbolKD arbolKD;  


public:
    Sistema();
    void ejecutar();
    void procesarComando(const std::string& entrada);
    
};

#endif