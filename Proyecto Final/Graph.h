#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

// Estructura base para representar una arista (conexion) en la lista de adyacencia
struct Edge {
    int target_id;
    Edge* next;
    Edge(int id) : target_id(id), next(nullptr) {}
};

// Entrada de la lista de adyacencia para cada nodo del grafo
struct GraphNode {
    int student_id;
    Edge* head;
    GraphNode(int id) : student_id(id), head(nullptr) {}
};

class Graph {
private:
    std::vector<GraphNode> vertices; // El uso de vector auxiliar esta permitido por la rúbrica
    int totalConnections;

    int findVertexIndex(int id) {
        for (size_t i = 0; i < vertices.size(); i++) {
            if (vertices[i].student_id == id) return i;
        }
        return -1;
    }

public:
    Graph() : totalConnections(0) {}

    void addStudentNode(int id) {
        if (findVertexIndex(id) == -1) {
            vertices.push_back(GraphNode(id));
        }
    }

    bool connectStudents(int id1, int id2) {
        if (id1 == id2) return false; // Restriccion: No conectarse consigo mismo

        int idx1 = findVertexIndex(id1);
        int idx2 = findVertexIndex(id2);

        if (idx1 == -1 || idx2 == -1) return false; // Uno de los estudiantes no existe

        // Validacion: Verificar si la conexion ya existe (No duplicados)
        Edge* temp = vertices[idx1].head;
        while (temp) {
            if (temp->target_id == id2) return false;
            temp = temp->next;
        }

        // Grafo no dirigido: Insertar id2 en la lista de id1
        Edge* e1 = new Edge(id2);
        e1->next = vertices[idx1].head;
        vertices[idx1].head = e1;

        // Insertar id1 en la lista de id2
        Edge* e2 = new Edge(id1);
        e2->next = vertices[idx2].head;
        vertices[idx2].head = e2;

        totalConnections++;
        return true;
    }

    void displayConnections(int id) {
        int idx = findVertexIndex(id);
        if (idx == -1) {
            std::cout << "Estudiante no registrado en la red social.\n";
            return;
        }
        Edge* temp = vertices[idx].head;
        std::cout << "Conexiones del estudiante ID " << id << ": ";
        if (!temp) std::cout << "Ninguna conexion activa.";
        while (temp) {
            std::cout << "[" << temp->target_id << "] -> ";
            temp = temp->next;
        }
        std::cout << "FIN\n";
    }

    int getTotalConnections() { return totalConnections; }

    void runBFS(int start_id) {
        std::cout << "--- Recorrido BFS (Sera codificado tras la clase de Grafos) ---\n";
    }

    void runDFS(int start_id) {
        std::cout << "--- Recorrido DFS (Sera codificado tras la clase de Grafos) ---\n";
    }
};

#endif
