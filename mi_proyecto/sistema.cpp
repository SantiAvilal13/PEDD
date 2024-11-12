#include "sistema.h"
#include "ArbolKD.h"
#include "ManejadorObj.h"
#include "Objeto3D.h"
#include "Cara.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>


Sistema::Sistema() : ejecutando(true) {}
ManejadorObj manejadorObj;

void Sistema::ejecutar() {
  std::cout << "Bienvenido al sistema de manipulación de objetos 3D."
            << std::endl;
  std::cout << "Escriba 'ayuda' para ver la lista de comandos disponibles."
            << std::endl;

  while (ejecutando) {
    std::cout << "$ ";
    std::string entrada;
    std::getline(std::cin, entrada);
    procesarComando(entrada);
  }
}

void Sistema::procesarComando(const std::string &entrada) {
  std::istringstream iss(entrada);
  std::string comando;
  iss >> comando;

  if (comando == "ayuda") {
    std::string parametro;
    if (iss >> parametro) {
      mostrarAyudaComando(parametro);
    } else {
      mostrarAyuda();
    }
  } else if (comando == "salir") {
    ejecutando = false;
    std::cout << "Saliendo del sistema..." << std::endl;
  } else if (comando == "cargar") {
    std::string nombre_archivo;
    if (iss >> nombre_archivo) {
      cargar(nombre_archivo);
    } else {
      std::cout << "Uso: cargar <nombre_archivo>" << std::endl;
    }
  } else if (comando == "listado") {
    std::cout << "EXITO" << std::endl;
    listado();
  } else if (comando == "envolvente") {
    std::string nombre_objeto;
    if (iss >> nombre_objeto) {
      envolvente(nombre_objeto);
    } else {
      std::cout << "EXITO" << std::endl;
      envolventeGlobal();
    }
  } else if (comando == "descargar") {
    std::string nombre_objeto;
    if (iss >> nombre_objeto) {
      std::cout << "EXITO" << std::endl;
      descargar(nombre_objeto);
    } else {
      std::cout << "Uso: descargar <nombre_objeto>" << std::endl;
    }
  } else if (comando == "guardar") {
    std::string nombre_objeto, nombre_archivo;
    if (iss >> nombre_objeto >> nombre_archivo) {
      std::cout << "EXITO" << std::endl;
      guardar(nombre_objeto, nombre_archivo);
    } else {
      std::cout << "Uso: guardar <nombre_objeto> <nombre_archivo>" << std::endl;
    }
  } else if (comando == "v_cercano") {
    float px, py, pz;
    std::string nombre_objeto;
    if (iss >> px >> py >> pz >> nombre_objeto) {
      std::cout << "EXITO" << std::endl;
      vCercano(px, py, pz, nombre_objeto);
    } else {
      std::cout << "Uso: v_cercano <px> <py> <pz> <nombre_objeto>" << std::endl;
    }
  } else if (comando == "v_cercanog") {
    float px, py, pz;
    if (iss >> px >> py >> pz) {
      std::cout << "EXITO" << std::endl;
      vCercanoGlobal(px, py, pz);
    } else {
      std::cout << "Uso: v_cercanog <px> <py> <pz>" << std::endl;
    }
  } else if (comando == "v_cercanos_caja") {
    std::string nombre_objeto;
    if (iss >> nombre_objeto) {
      std::cout << "EXITO" << std::endl;
      vCercanosCaja(nombre_objeto);
    } else {
      std::cout << "Uso: v_cercanos_caja <nombre_objeto>" << std::endl;
    }
  } else if (comando == "ruta_corta") {
    int i1, i2;
    std::string nombre_objeto;
    if (iss >> i1 >> i2 >> nombre_objeto) {
      std::cout << "EXITO" << std::endl;
      rutaCorta(i1, i2, nombre_objeto);
    } else {
      std::cout << "Uso: ruta_corta <i1> <i2> <nombre_objeto>" << std::endl;
    }
  } else if (comando == "ruta_corta_centro") {
    int i1;
    std::string nombre_objeto;
    if (iss >> i1 >> nombre_objeto) {
      std::cout << "EXITO" << std::endl;
      rutaCortaCentro(i1, nombre_objeto);
    } else {
      std::cout << "Uso: ruta_corta_centro <i1> <nombre_objeto>" << std::endl;
    }
  } else {
    std::cout << "Comando no reconocido. Escriba 'ayuda' para ver la lista de comandos disponibles." << std::endl;
  }
}


void Sistema::mostrarAyuda() {
  std::cout << "Comandos disponibles:" << std::endl;
  std::cout << " 1. ayuda - Muestra la lista de comandos disponibles"
            << std::endl;
  std::cout << " 2. salir - Termina la ejecución de la aplicación" << std::endl;
  std::cout
      << " 3. cargar <nombre_archivo> - Carga un objeto 3D desde un archivo"
      << std::endl;
  std::cout << " 4. listado - Muestra la lista de objetos cargados en memoria"
            << std::endl;
  std::cout << " 5. envolvente <nombre_objeto> - Calcula la caja envolvente de "
               "un objeto"
            << std::endl;
  std::cout
      << " 6. envolvente - Calcula la caja envolvente de todos los objetos"
      << std::endl;
  std::cout
      << " 7. descargar <nombre_objeto> - Descarga un objeto de la memoria"
      << std::endl;
  std::cout << " 8. guardar <nombre_objeto> <nombre_archivo> - Guarda un "
               "objeto en un archivo"
            << std::endl;
  std::cout << " 9. v_cercano <px> <py> <pz> <nombre_objeto> - Encuentra el "
               "vértice más cercano a un punto en un objeto"
            << std::endl;
  std::cout << " 10. v_cercanog <px> <py> <pz> - Encuentra el vértice más "
               "cercano a un punto en todos los objetos"
            << std::endl;
  std::cout << " 11. v_cercanos_caja <nombre_objeto> - Encuentra los vértices "
               "más cercanos a las esquinas de la caja envolvente"
            << std::endl;
  std::cout << " 12. ruta_corta <i1> <i2> <nombre_objeto> - Encuentra la ruta "
               "más corta entre dos vértices"
            << std::endl;
  std::cout << " 13. ruta_corta_centro <i1> <nombre_objeto> - Encuentra la "
               "ruta más corta desde un vértice al centro del objeto"
            << std::endl;
}

void Sistema::mostrarAyudaComando(const std::string &comando) {
  if (comando == "ayuda") {
    std::cout << "ayuda - Muestra la lista de comandos disponibles"
              << std::endl;
  } else if (comando == "salir") {
    std::cout << "salir - Termina la ejecución de la aplicación" << std::endl;
  } else if (comando == "cargar") {
    std::cout << "cargar <nombre_archivo> - Carga un objeto 3D desde un archivo"
              << std::endl;
  } else if (comando == "listado") {
    std::cout << "listado - Muestra la lista de objetos cargados en memoria"
              << std::endl;
  } else if (comando == "envolvente") {
    std::cout << "envolvente <nombre_objeto> - Calcula la caja envolvente de "
                 "un objeto"
              << std::endl;
    std::cout << "envolvente - Calcula la caja envolvente de todos los objetos"
              << std::endl;
  } else if (comando == "descargar") {
    std::cout << "descargar <nombre_objeto> - Descarga un objeto de la memoria"
              << std::endl;
  } else if (comando == "guardar") {
    std::cout << "guardar <nombre_objeto> <nombre_archivo> - Guarda un objeto "
                 "en un archivo"
              << std::endl;
  } else if (comando == "v_cercano") {
    std::cout << "v_cercano <px> <py> <pz> <nombre_objeto> - Encuentra el "
                 "vértice más cercano a un punto en un objeto"
              << std::endl;
    std::cout << "v_cercano <px> <py> <pz> - Encuentra el vértice más cercano "
                 "a un punto en todos los objetos"
              << std::endl;
  } else if (comando == "v_cercanos_caja") {
    std::cout << "v_cercanos_caja <nombre_objeto> - Encuentra los vértices más "
                 "cercanos a las esquinas de la caja envolvente"
              << std::endl;
  } else if (comando == "ruta_corta") {
    std::cout << "ruta_corta <i1> <i2> <nombre_objeto> - Encuentra la ruta más "
                 "corta entre dos vértices"
              << std::endl;
  } else if (comando == "ruta_corta_centro") {
    std::cout << "ruta_corta_centro <i1> <nombre_objeto> - Encuentra la ruta "
                 "más corta desde un vértice al centro del objeto"
              << std::endl;
  } else {
    std::cout << "No hay ayuda disponible para el comando '" << comando << "'."
              << std::endl;
  }
}

void Sistema::vCercano(float px, float py, float pz, const std::string& nombreObjeto) {
    Objeto3D* objeto = manejadorObj.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    std::vector<Vertice*> vertice = objeto->getVerticePtr();

    if(vertice.empty())
    {
        std::cout << "El objeto " << nombreObjeto << " no tiene vértices." << std::endl;
        return;
    }
    Vertice punto(px, py, pz);
    ArbolKD arbol(vertice);
    Vertice* verticeCercano = arbol.VerticeMasCercano(punto, nombreObjeto);

    if (verticeCercano != nullptr)
    {
        float distancia = arbol.distanciaEuclidiana(punto, *verticeCercano);
        auto it = std::find_if(vertice.begin(), vertice.end(),
                               [verticeCercano](const Vertice* v)
        {
            return v == verticeCercano;
        });
        if (it != vertice.end())
        {
            int indice = std::distance(vertice.begin(), it);
            std::cout << "El vertice " << indice
                      << " (" << verticeCercano->getX() << ", " << verticeCercano->getY() << ", " << verticeCercano->getZ()
                      << ") del objeto " << nombreObjeto << " es el mas cercano al punto ("
                      << px << ", " << py << ", " << pz
                      << "), a una distancia de " << distancia << "." << std::endl;
        }
    }
    else
    {
        std::cout << "No se encontro un vertice cercano." << std::endl;
    }
}

void Sistema::vCercanoGlobal(float px, float py, float pz) {
   if (manejadorObj.estaVacio())
    {
        std::cout << "Ningun objeto ha sido cargado en memoria." << std::endl;
        return;
    }

    std::vector<Vertice*> todosLosVertices;
    std::vector<Objeto3D*> objetos = manejadorObj.obtenerTodosLosObjetos();
    std::string nombreObjetoCercano;
    Vertice* verticeCercano = nullptr;

    for(const auto& objeto : objetos)
    {
        const std::vector<Vertice>& vertices = objeto->getVertices();
        for(const auto& vertice : vertices)
        {
            todosLosVertices.push_back(new Vertice(vertice));
        }
    }

    if(todosLosVertices.empty())
    {
        std::cout << "No hay vertices cargados en ningún objeto." << std::endl;
        return;
    }

    Vertice punto(px,py,pz);
    ArbolKD arbol(todosLosVertices);

    verticeCercano = arbol.VerticeMasCercano(punto, "global");
    float distancia = arbol.distanciaEuclidiana(punto, *verticeCercano);
    for (const auto& objeto : objetos) {
        const std::vector<Vertice>& vertices = objeto->getVertices();
        auto it = std::find_if(vertices.begin(), vertices.end(), [&](const Vertice& v) {
            return v.getX() == verticeCercano->getX() &&
                   v.getY() == verticeCercano->getY() &&
                   v.getZ() == verticeCercano->getZ();
        });

        if (it != vertices.end()) {
            nombreObjetoCercano = objeto->getNombreMalla();
            int indiceVertice = std::distance(vertices.begin(), it);

            // Mostrar mensaje de éxito con el vértice más cercano
            std::cout << "El vertice " << indiceVertice
                      << " (" << verticeCercano->getX() << ", " << verticeCercano->getY() << ", "
                      << verticeCercano->getZ() << ") del objeto " << nombreObjetoCercano
                      << " es el mas cercano al punto (" << px << ", " << py << ", " << pz
                      << "), a una distancia de " << distancia << "." << std::endl;
            break;
        }
    }

    for (auto vertice : todosLosVertices)
    {
        delete vertice;
    }
}

void Sistema::vCercanosCaja(const std::string& nombreObjeto) {
    // Obtener el objeto desde el gestor usando su nombre
    Objeto3D* objeto = manejadorObj.obtenerObjeto(nombreObjeto);
    if (objeto == nullptr)
    {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    // Obtener los vértices del objeto
    std::vector<Vertice> vertices = objeto->getVertices();
    if (vertices.empty())
    {
        std::cout << "El objeto " << nombreObjeto << " no tiene vértices." << std::endl;
        return;
    }

    // Inicializar los puntos mínimos y máximos con el primer vértice
    Vertice pmin = vertices[0];
    Vertice pmax = vertices[0];

    // Iterar sobre los vértices para encontrar los límites de la caja envolvente
    for (const auto& vertice : vertices)
    {
        if (vertice.getX() < pmin.getX()) pmin.setX(vertice.getX());
        if (vertice.getY() < pmin.getY()) pmin.setY(vertice.getY());
        if (vertice.getZ() < pmin.getZ()) pmin.setZ(vertice.getZ());

        if (vertice.getX() > pmax.getX()) pmax.setX(vertice.getX());
        if (vertice.getY() > pmax.getY()) pmax.setY(vertice.getY());
        if (vertice.getZ() > pmax.getZ()) pmax.setZ(vertice.getZ());
    }

    // Crear un nuevo objeto para la caja envolvente
    std::string nombreEnvolvente = "env_" + nombreObjeto;
    Objeto3D envolvente(nombreEnvolvente);

    // Agregar los puntos mínimos y máximos como vértices de la envolvente
    envolvente.agregarVertice(pmin.getX(), pmin.getY(), pmin.getZ());
    envolvente.agregarVertice(pmax.getX(), pmax.getY(), pmax.getZ());

    // Agregar la envolvente al gestor
    manejadorObj.agregarObj(envolvente);
    std::cout << "La caja envolvente del objeto " << nombreObjeto << " se ha generado con el nombre "
              << nombreEnvolvente << " y se ha agregado a los objetos en memoria.\n" << std::endl;

    // Obtener los vértices de la envolvente
    std::vector<Vertice> verticesEnvolvente = envolvente.getVertices();
    if (verticesEnvolvente.empty())
    {
        std::cout << "La envolvente no tiene vértices." << std::endl;
        return;
    }

    // Encabezado de la tabla
    std::cout << "Los vértices del objeto " << nombreObjeto
              << " más cercanos a las esquinas de su caja envolvente son:\n";
    std::cout << std::setw(10) << "Esquina"
              << std::setw(25) << "Vertice Envolvente"
              << std::setw(25) << "Vertice Original"
              << std::setw(15) << "Distancia" << "\n";
    std::cout << std::string(75, '-') << "\n";  // Línea separadora

    // Iterar sobre los vértices del objeto original para encontrar el vértice más cercano en la envolvente
    int contadorEsquina = 0;
    for (const auto& vertice : vertices)
    {
        Vertice* verticeCercano = nullptr;
        float distanciaMinima = std::numeric_limits<float>::max();
        int indiceCercano = -1;

        for (int i = 0; i < verticesEnvolvente.size(); i++)
        {
            float dx = vertice.getX() - verticesEnvolvente[i].getX();
            float dy = vertice.getY() - verticesEnvolvente[i].getY();
            float dz = vertice.getZ() - verticesEnvolvente[i].getZ();
            float distancia = sqrt((dx * dx) + (dy * dy) + (dz * dz));

            if (distancia < distanciaMinima)
            {
                distanciaMinima = distancia;
                verticeCercano = &verticesEnvolvente[i];
                indiceCercano = i;
            }
        }

        if (verticeCercano != nullptr)
        {
            // Imprimir resultados en formato tabular
            std::cout << std::setw(10) << contadorEsquina + 1
                      << std::setw(10) << "(" << verticeCercano->getX() << ", "
                      << verticeCercano->getY() << ", " << verticeCercano->getZ() << ")"
                      << std::setw(15) << "(" << vertice.getX() << ", "
                      << vertice.getY() << ", " << vertice.getZ() << ")"
                      << std::setw(15) << distanciaMinima << "\n";
        }
        contadorEsquina++;
    }
}




void Sistema::descargar(const std::string &nombre_objeto) {
  if (manejadorObj.descarObj(nombre_objeto)) {
    std::cout << "(Resultado exitoso) El objeto '" << nombre_objeto
              << "' ha sido eliminado de la memoria de trabajo." << std::endl;
  } else {
    std::cout << "(Objeto no existe) El objeto '" << nombre_objeto
              << "' no ha sido cargado en memoria." << std::endl;
  }
}

void Sistema::envolvente(const std::string &nombre_objeto) {
  int puntos=2;

  //Obtener el objeto desde el gestor usando su nombre
  Objeto3D* objeto = manejadorObj.obtenerObjeto(nombre_objeto);
  if (objeto == nullptr)
  {
      std::cout << "El objeto " << nombre_objeto << " no ha sido cargado en memoria." << std::endl;
      return;
  }


  std::vector<Vertice> vertices = objeto->getVertices();
  if (vertices.empty())
  {
      std::cout << "El objeto " << nombre_objeto << " no tiene v�rtices." << std::endl;
      return;
  }

  Vertice pmin = vertices[0];
  Vertice pmax = vertices[0];

  for (const auto& vertice : vertices)
  {
      if (vertice.getX() < pmin.getX()) pmin.setX(vertice.getX());
      if (vertice.getY() < pmin.getY()) pmin.setY(vertice.getY());
      if (vertice.getZ() < pmin.getZ()) pmin.setZ(vertice.getZ());

      if (vertice.getX() > pmax.getX()) pmax.setX(vertice.getX());
      if (vertice.getY() > pmax.getY()) pmax.setY(vertice.getY());
      if (vertice.getZ() > pmax.getZ()) pmax.setZ(vertice.getZ());
  }

  //Crear un nuevo objeto para la caja envolvente
  std::string nombreEnvolvente = "env_" + nombre_objeto;
  Objeto3D envolvente(nombreEnvolvente);


  envolvente.agregarVertice(pmin.getX(), pmin.getY(), pmin.getZ());
  envolvente.agregarVertice(pmax.getX(), pmax.getY(), pmax.getZ());
  envolvente.agregarPuntosObj(puntos);

  //Agregar la envolvente al gestor
  manejadorObj.agregarObj(envolvente);
  std::cout << "La caja envolvente del objeto " << nombre_objeto << " se ha generado con el nombre " << nombreEnvolvente << " y se ha agregado a los objetos en memoria.\n" << std::endl;

}

void Sistema::envolventeGlobal() {
  int puntos=2;
    //Verifica que haya al menos un objeto en memoria
    if (manejadorObj.estaVacio())
    {
        std::cout << "Ningun objeto ha sido cargado en memoria." << std::endl;
        return;
    }

    //Obtiene todos los vertices de todos los objetos en memoria
    std::vector<Vertice> vertices = manejadorObj.obtenerVertices();

    //Inicializar los puntos minimos y maximos con el primer vertice
    Vertice pmin = vertices[0];
    Vertice pmax = vertices[0];

    //Itera sobre los vertices para encontrar los limites de la caja envolvente global
    for (const auto& vertice : vertices)
    {
        if (vertice.getX() < pmin.getX()) pmin.setX(vertice.getX());
        if (vertice.getY() < pmin.getY()) pmin.setY(vertice.getY());
        if (vertice.getZ() < pmin.getZ()) pmin.setZ(vertice.getZ());

        if (vertice.getX() > pmax.getX()) pmax.setX(vertice.getX());
        if (vertice.getY() > pmax.getY()) pmax.setY(vertice.getY());
        if (vertice.getZ() > pmax.getZ()) pmax.setZ(vertice.getZ());
    }

    //Crear un nuevo objeto para la caja envolvente global
    std::string nombreEnvolvente = "env_global";
    Objeto3D envolvente(nombreEnvolvente);

    //Agregar los puntos minimos y maximos como vertices de la envolvente global
    envolvente.agregarVertice(pmin.getX(), pmin.getY(), pmin.getZ());
    envolvente.agregarVertice(pmax.getX(), pmax.getY(), pmax.getZ());
    envolvente.agregarPuntosObj(puntos);

    //Agregar la envolvente global al gestor
    manejadorObj.agregarObj(envolvente);
    std::cout << "\nLa caja envolvente de los objetos en memoria se ha generado con el nombre "  << nombreEnvolvente <<" y se ha agregado a los objetos en memoria." << std::endl;
}

void Sistema::rutaCorta(int i1, int i2, const std::string &nombre_objeto) {
  std::cout << "Calculando ruta más corta entre vértices " << i1 << " y " << i2
            << " en " << nombre_objeto << std::endl;

  // Implementación pendiente
}

void Sistema::rutaCortaCentro(int i1, const std::string &nombre_objeto) {
  std::cout << "Calculando ruta más corta desde vértice " << i1
            << " al centro de " << nombre_objeto << std::endl;

  // Implementación pendiente
}

void Sistema::guardar(const std::string &nombre_objeto,
                      const std::string &nombre_archivo) {
  //Obtener el objeto desde el gestor usando su nombre
  Objeto3D* objeto = manejadorObj.obtenerObjeto(nombre_objeto);
  if (objeto == nullptr)
  {
      std::cout << "El objeto " << nombre_objeto << " no ha sido cargado en memoria." << std::endl;
      return;
  }

  std::ofstream archivo(nombre_archivo);
  if (!archivo)
  {
      std::cerr << "Error al abrir el archivo " << nombre_archivo << " para escritura." << std::endl;
      return;
  }

  //Agrega la informacion al archivo
  archivo << nombre_objeto << std::endl;
  archivo << objeto->getNumeroVertices()<<std::endl;
  std::vector<Vertice> vertices = objeto->getVertices();
  for (int i = 0; i < objeto->getNumeroVertices(); i++)
  {
      archivo << vertices[i].getX() << " " << vertices[i].getY() << " " << vertices[i].getZ() << std::endl;
  }
  for (const auto& cara : objeto->getCaras())
  {
      archivo << cara.getVertices().size()<< " ";
      for (const auto& indice : cara.getVertices())
      {
          archivo << indice << " ";
      }
      archivo << std::endl;
  }
  archivo << "-1" << std::endl;
  archivo.close();
  std::cout << "La informacion del objeto " << nombre_objeto << " ha sido guardada exitosamente en el archivo " << nombre_archivo<< "." << std::endl;
}

void Sistema::cargar(const std::string& nombreArchivo)
{

    std::ifstream archivo(nombreArchivo);
    if(!archivo.is_open())
    {
        std::cout<<"El archivo "<< nombreArchivo<<" no existe o es ilegible." << std::endl;
        return;
    }
    std::string meshName;
    int numVertice, tamCaras = 0, numIndices;
    archivo >> meshName;

    if (!archivo)
    {
        std::cout << "Error al leer el archivo " << nombreArchivo << "." << std::endl;
        return;
    }

    // Verifica exisitencia del objeto
    if (manejadorObj.verificarObjeto(meshName))
    {
        std::cerr << "El objeto " << meshName << " ya ha sido cargado en memoria." << std::endl;
        return;
    }

    archivo >> numVertice;
    if (!archivo)
    {
        std::cout << "Error al leer el archivo " << nombreArchivo << " en el numero de vertices." << std::endl;
        return;
    }
    if(numVertice <= 0)
    {
        std::cout << "El archivo " << nombreArchivo << " no contiene un objeto 3D valido (cantidad de puntos no valida, tiene que ser > 0)." << std::endl;
        return;
    }

    // Crea la instancia de un nuevo Objeto
    Objeto3D nuevoObjeto(meshName);

    std::vector<Vertice*> verticesPtr;

    //Agrega los vertices del objeto
    for(int i=0; i< numVertice; i++)
    {
        float x,y,z;
        archivo >> x >> y >> z;
        if (!archivo)
        {
            std::cout << "Error al leer el archivo " << nombreArchivo << " en las coordenadas." << std::endl;
            return;
        }

        Vertice* nuevoVertice = new Vertice(x,y,z);
        nuevoObjeto.agregarVertice(x,y,z);

        verticesPtr.push_back(nuevoVertice);
    }

    //Agrega las caras del objeto y sus indices
    while(true)
    {
        archivo >> tamCaras;
        if(tamCaras == -1)
        {
            break;
        }
        if (!archivo)
        {
            std::cout << "Error al leer el archivo " << nombreArchivo << " en el numero de caras." << std::endl;
            return;
        }

        Cara nuevaCara;
        for(int i=0; i < tamCaras; i++)
        {
            int indiceVertice;
            archivo >> indiceVertice;
            if (!archivo)
            {
                std::cout << "Error al leer los indices de una cara en el archivo " << nombreArchivo << "." << std::endl;
                return;
            }
            nuevaCara.agregarVertice(indiceVertice);
        }

        nuevoObjeto.agregarCara(nuevaCara);
    }

    if(tamCaras == -1)
    {
        std::cout << "Lectura Exitosa del archivo " << nombreArchivo << std::endl;
    }

    //Calcula las aristas del objeto
    nuevoObjeto.calcularAristas();
    //Agrega el objeto a memoria
    manejadorObj.agregarObj(nuevoObjeto);
    if(manejadorObj.verificarObjeto(meshName))
    {
        std::cout << "El objeto " << meshName << " fue cargado exitosamente." << std::endl;
    }
    else
    {
        std::cerr << "Error: El objeto " << meshName << " no se pudo cargar. "<< std::endl;
    }

    ArbolKD arbolKD(verticesPtr);
}

void Sistema::listado() {
  std::cout << "Listando objetos en memoria..." << std::endl;

  manejadorObj.mostrarObj();
}

// g++ -std=c++11 -o nombre_de_mi_pro *.cpp
