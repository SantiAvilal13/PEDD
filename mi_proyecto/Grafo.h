#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

template <class T, class U>
class Grafo {
private:
    std::vector<T> vertices;
    U **aristas;
    std::vector<std::pair<std::string, std::string>> pares;
public:
    Grafo();
    ~Grafo();

    void setVertices(const std::vector<T>& v);
    void setAristas(U** a);
    std::vector<T> getVertices() const;
    U** getAristas() const;
    int cantVertices() const;
    int cantAristas() const;
    int buscarVertice(T vert) const;
    bool insertarVertice(T vert);
    bool insertarArista(T ori, T des, U cos);
    U buscarArista(T ori, T des) const;
    bool eliminarArista(T ori, T des);
    void DFS(T start) const;
    void BFS(T start) const;
    std::unordered_map<T, U> dijkstra(T start) const;
    void cargarRelaciones(const std::string& archivoRelaciones);
    void cargarPares(const std::string& nombreArchivo);
    std::vector<std::pair<std::string, std::string>> obtenerPares() const;
    void imprimirGrafo() const;
};

// Implementación de constructor y destructor

template <class T, class U>
Grafo<T, U>::Grafo() : aristas(nullptr) {}

template <class T, class U>
Grafo<T, U>::~Grafo() {
    if (aristas) {
        for (int i = 0; i < cantVertices(); i++) {
            delete[] aristas[i];
        }
        delete[] aristas;
    }
}

// Métodos de asignación y obtención de datos

template <class T, class U>
void Grafo<T, U>::setVertices(const std::vector<T>& v) {
    vertices = v;
}

template <class T, class U>
void Grafo<T, U>::setAristas(U** a) {
    aristas = a;
}

template <class T, class U>
std::vector<T> Grafo<T, U>::getVertices() const {
    return vertices;
}

template <class T, class U>
U** Grafo<T, U>::getAristas() const {
    return aristas;
}

// Métodos de conteo

template <class T, class U>
int Grafo<T, U>::cantVertices() const {
    return vertices.size();
}

template <class T, class U>
int Grafo<T, U>::cantAristas() const {
    int suma = 0;
    for (int i = 0; i < cantVertices(); i++) {
        for (int j = 0; j < cantVertices(); j++) {
            if (aristas[i][j] != 0) suma++;
        }
    }
    return suma;
}

// Operaciones de búsqueda y modificación de vértices y aristas

template <class T, class U>
int Grafo<T, U>::buscarVertice(T vert) const {
    for (int i = 0; i < cantVertices(); i++) {
        if (vertices[i] == vert) return i;
    }
    return -1;
}

template <class T, class U>
bool Grafo<T, U>::insertarVertice(T vert) {
    if (buscarVertice(vert) == -1) {
        vertices.push_back(vert);
        U** nmatriz = new U*[cantVertices()];
        for (int i = 0; i < cantVertices(); i++) {
            nmatriz[i] = new U[cantVertices()];
        }
        for (int i = 0; i < cantVertices() - 1; i++) {
            for (int j = 0; j < cantVertices() - 1; j++) {
                nmatriz[i][j] = aristas[i][j];
            }
        }
        for (int i = 0; i < cantVertices(); i++) {
            nmatriz[i][cantVertices() - 1] = 0;
            nmatriz[cantVertices() - 1][i] = 0;
        }
        for (int i = 0; i < cantVertices() - 1; i++) {
            delete[] aristas[i];
        }
        delete[] aristas;
        aristas = nmatriz;
        return true;
    }
    return false;
}

template <class T, class U>
bool Grafo<T, U>::insertarArista(T ori, T des, U cos) {
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1 && aristas[i_ori][i_des] == 0) {
        aristas[i_ori][i_des] = cos;
        return true;
    }
    return false;
}

template <class T, class U>
U Grafo<T, U>::buscarArista(T ori, T des) const {
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    return (i_ori != -1 && i_des != -1) ? aristas[i_ori][i_des] : -1;
}

template <class T, class U>
bool Grafo<T, U>::eliminarArista(T ori, T des) {
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
        aristas[i_ori][i_des] = 0;
        return true;
    }
    return false;
}

// Implementación de DFS

template <class T, class U>
void Grafo<T, U>::DFS(T start) const {
    std::set<T> visited;
    std::stack<T> stack;
    stack.push(start);

    while (!stack.empty()) {
        T vertex = stack.top();
        stack.pop();

        if (visited.find(vertex) == visited.end()) {
            visited.insert(vertex);
            std::cout << vertex << " ";

            int index = buscarVertice(vertex);
            for (int i = 0; i < cantVertices(); i++) {
                if (aristas[index][i] != 0 && visited.find(vertices[i]) == visited.end()) {
                    stack.push(vertices[i]);
                }
            }
        }
    }
}

// Implementación de BFS

template <class T, class U>
void Grafo<T, U>::BFS(T start) const {
    std::set<T> visited;
    std::queue<T> queue;
    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        T vertex = queue.front();
        queue.pop();
        std::cout << vertex << " ";

        int index = buscarVertice(vertex);
        for (int i = 0; i < cantVertices(); i++) {
            if (aristas[index][i] != 0 && visited.find(vertices[i]) == visited.end()) {
                queue.push(vertices[i]);
                visited.insert(vertices[i]);
            }
        }
    }
}

// Implementación de Dijkstra

template <class T, class U>
std::unordered_map<T, U> Grafo<T, U>::dijkstra(T start) const {
    if (vertices.empty()) {
        std::cerr << "Error: vertices está vacío.\n";
        return {};
    }

    std::unordered_map<T, U> distances;
    std::priority_queue<std::pair<U, T>, std::vector<std::pair<U, T>>, std::greater<std::pair<U, T>>> pq;
    std::set<T> reportedErrors;  

    // Inicialización de distancias
    for (const auto& vertex : vertices) {
        distances[vertex] = std::numeric_limits<U>::max();
    }
    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        T current = pq.top().second;
        U currentDistance = pq.top().first;
        pq.pop();

        if (currentDistance > distances[current]) {
            continue;
        }

        int index = buscarVertice(current);
        if (index == -1) {
            if (reportedErrors.find(current) == reportedErrors.end()) {
                std::cerr << "Error: No se encontró la persona " << current << " en el archivo de relaciones.\n";
                reportedErrors.insert(current);
            }
            continue;
        }

        // Procesar vecinos
        for (int i = 0; i < cantVertices(); i++) {
            if (aristas[index][i] != 0) {
                T neighbor = vertices[i];
                U weight = aristas[index][i];

                if (distances[current] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[current] + weight;
                    pq.push({distances[neighbor], neighbor});
                }
            }
        }
    }

    return distances;
}

template <class T, class U>
void Grafo<T, U>::cargarRelaciones(const std::string& archivoRelaciones) {
    std::ifstream archivo(archivoRelaciones);

    if(!archivo.is_open()) {
        std::cout << "Archivo no existe\n";
        return; // Termina la función si no se puede abrir el archivo
    }

    std::string linea, persona1, persona2;

    // Ignorar la primera línea
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);

        if (!(iss >> persona1 >> persona2)) {
            std::cerr << "Línea inválida o incompleta: " << linea << '\n';
            continue;
        }

        if (persona1.empty() || persona2.empty()) {
            std::cerr << "Persona vacía en la línea: " << linea << '\n';
            continue;
        }

        if (buscarVertice(persona1) == -1) insertarVertice(persona1);
        if (buscarVertice(persona2) == -1) insertarVertice(persona2);
        insertarArista(persona1, persona2, 1);
        insertarArista(persona2, persona1, 1);
    }
}

template <class T, class U>
void Grafo<T, U>::cargarPares(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + nombreArchivo);
    }

    int m;
    archivo >> m;
    std::string p1, p2;
    for (int i = 0; i < m; i++) {
        archivo >> p1 >> p2;
        pares.push_back({p1, p2});
    }
    archivo.close();
}

template <class T, class U>
std::vector<std::pair<std::string, std::string>> Grafo<T, U>::obtenerPares() const {
    return pares;
}

template <class T, class U>
void Grafo<T, U>::imprimirGrafo() const {
    for (int i = 0; i < cantVertices(); ++i) {
        std::cout << "Vértice: " << vertices[i] << std::endl;
        for (int j = 0; j < cantVertices(); ++j) {
            if (aristas[i][j] != 0) {
                std::cout << "  -> " << vertices[j] << " (peso: " << aristas[i][j] << ")" << std::endl;
            }
        }
    }
}



#endif // GRAFO_H
