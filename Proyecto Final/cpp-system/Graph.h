//Priscila Guzmán
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
//Mejora avanzada
#include <queue>
#include <unordered_map>
#include <algorithm>


struct AdjNode {
    int student_id;
    AdjNode* next;
    AdjNode(int id) : student_id(id), next(nullptr) {}
};

class Graph {
private:
    struct GraphNode {
        int student_id;
        AdjNode* head;
        GraphNode(int id) : student_id(id), head(nullptr) {}
    };

    std::vector<GraphNode> vertices;

    int findVertexIndex(int student_id) const
{
    for(size_t i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].student_id == student_id)
        {
            return i;
        }
    }

    return -1;
}


    //Auxiliar privado para DFS tradicional (imprime en consola)
    void DFSRecursivo(int current_index, std::vector<bool>& visited) {
        std::cout << vertices[current_index].student_id << " ";
        visited[current_index] = true;

        AdjNode* adj = vertices[current_index].head;
        while (adj != nullptr) {
            int adj_index = findVertexIndex(adj->student_id);
            if (adj_index != -1 && !visited[adj_index]) {
                DFSRecursivo(adj_index, visited);
            }
            adj = adj->next;
        }
    }

    // Auxiliar privado para DFS silencioso (Benchmark)
    void dfsSilenciosoRec(int current_index, std::vector<bool>& visited) {
        visited[current_index] = true;

        AdjNode* adj = vertices[current_index].head;
        while (adj != nullptr) {
            int adj_index = findVertexIndex(adj->student_id);
            if (adj_index != -1 && !visited[adj_index]) {
                dfsSilenciosoRec(adj_index, visited);
            }
            adj = adj->next;
        }
    }

public:
    Graph() {}

    ~Graph() {
        clear();
    }

    void clear() {
        for (size_t i = 0; i < vertices.size(); ++i) {
            AdjNode* current = vertices[i].head;
            while (current != nullptr) {
                AdjNode* temp = current;
                current = current->next;
                delete temp;
            }
            vertices[i].head = nullptr;
        }
        vertices.clear();
    }

    void addStudentVertex(int student_id)
    {
    if(findVertexIndex(student_id) == -1)
        {
        vertices.push_back(GraphNode(student_id));
        }
    }

    void connectStudents(int id1, int id2, bool silentMode = false) {
        if (id1 == id2) {
            if (!silentMode) std::cout << "[ERROR] No se permite conectar un estudiante consigo mismo.\n";
            return;
        }

        int index1 = findVertexIndex(id1);
        int index2 = findVertexIndex(id2);

        if (index1 == -1 || index2 == -1) {
            if (!silentMode) std::cout << "[ERROR] Uno o ambos estudiantes no existen en el sistema.\n";
            return;
        }

        if (areConnected(id1, id2)) {
            if (!silentMode) std::cout << "[ERROR] Los estudiantes " << id1 << " y " << id2 << " ya estan conectados.\n";
            return;
        }

        AdjNode* newNode1 = new AdjNode(id2);
        newNode1->next = vertices[index1].head;
        vertices[index1].head = newNode1;

        AdjNode* newNode2 = new AdjNode(id1);
        newNode2->next = vertices[index2].head;
        vertices[index2].head = newNode2;

        if (!silentMode) {
            std::cout << "[EXITO] Conexion creada exitosamente entre " << id1 << " y " << id2 << ".\n";
        }
    }

    bool areConnected(int id1, int id2) {
        int index1 = findVertexIndex(id1);
        if (index1 == -1) return false;

        AdjNode* current = vertices[index1].head;
        while (current != nullptr) {
            if (current->student_id == id2) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void displayConnections(int student_id) {
        int index = findVertexIndex(student_id);
        if (index == -1) {
            std::cout << "[ERROR] El estudiante con ID " << student_id << " no existe.\n";
            return;
        }

        std::cout << "Conexiones del estudiante [" << student_id << "]: ";
        AdjNode* current = vertices[index].head;
        if (current == nullptr) {
            std::cout << "(Ninguna conexion activa)";
        }
        while (current != nullptr) {
            std::cout << current->student_id << " ";
            current = current->next;
        }
        std::cout << "\n";
    }

    void BFS(int start_id) {
        int start_index = findVertexIndex(start_id);
        if (start_index == -1) {
            std::cout << "[ERROR] El ID inicial para BFS no existe.\n";
            return;
        }

        std::cout << "Recorrido BFS desde ID " << start_id << ": ";
        std::vector<bool> visited(vertices.size(), false);
        std::vector<int> queueSim;
        size_t front = 0;

        queueSim.push_back(start_id);
        visited[start_index] = true;

        while (front < queueSim.size()) {
            int current_id = queueSim[front++];
            std::cout << current_id << " ";

            int curr_index = findVertexIndex(current_id);
            if (curr_index == -1) continue;

            AdjNode* adj = vertices[curr_index].head;
            while (adj != nullptr) {
                int adj_index = findVertexIndex(adj->student_id);
                if (adj_index != -1 && !visited[adj_index]) {
                    visited[adj_index] = true;
                    queueSim.push_back(adj->student_id);
                }
                adj = adj->next;
            }
        }
        std::cout << "\n";
    }

    void bfsSilencioso(int start_id) {
        int start_index = findVertexIndex(start_id);
        if (start_index == -1) return;

        std::vector<bool> visited(vertices.size(), false);
        std::vector<int> queueSim;
        size_t front = 0;

        queueSim.push_back(start_id);
        visited[start_index] = true;

        while (front < queueSim.size()) {
            int current_id = queueSim[front++];
            int curr_index = findVertexIndex(current_id);
            if (curr_index == -1) continue;

            AdjNode* adj = vertices[curr_index].head;
            while (adj != nullptr) {
                int adj_index = findVertexIndex(adj->student_id);
                if (adj_index != -1 && !visited[adj_index]) {
                    visited[adj_index] = true;
                    queueSim.push_back(adj->student_id);
                }
                adj = adj->next;
            }
        }
    }

    void DFS(int start_id) {
        int start_index = findVertexIndex(start_id);
        if (start_index == -1) {
            std::cout << "[ERROR] El ID inicial para DFS no existe.\n";
            return;
        }

        std::cout << "Recorrido DFS desde ID " << start_id << ": ";
        std::vector<bool> visited(vertices.size(), false);
        DFSRecursivo(start_index, visited);
        std::cout << "\n";
    }

    void dfsSilencioso(int start_id) {
        int start_index = findVertexIndex(start_id);
        if (start_index == -1) return;

        std::vector<bool> visited(vertices.size(), false);
        dfsSilenciosoRec(start_index, visited);
    }
    //Mejora (Ruta más corta)
    void findShortestPath(int start_id, int end_id)
{
    int start_index = findVertexIndex(start_id);
    int end_index = findVertexIndex(end_id);

    if(start_index == -1 || end_index == -1)
    {
        std::cout << "[ERROR] Uno o ambos estudiantes no existen.\n";
        return;
    }

    std::queue<int> q;
    std::unordered_map<int, bool> visited;
    std::unordered_map<int, int> parent;

    q.push(start_id);
    visited[start_id] = true;
    parent[start_id] = -1;

    bool found = false;

    while(!q.empty())
    {
        int current = q.front();
        q.pop();

        if(current == end_id)
        {
            found = true;
            break;
        }

        int current_index = findVertexIndex(current);

        AdjNode* adj = vertices[current_index].head;

        while(adj)
        {
            int neighbor = adj->student_id;

            if(!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }

            adj = adj->next;
        }
    }

    if(!found)
    {
        std::cout << "\nNo existe una ruta entre los estudiantes.\n";
        return;
    }

    std::vector<int> path;

    for(int at = end_id; at != -1; at = parent[at])
    {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());

    std::cout << "\n===== RUTA MAS CORTA =====\n";

    for(size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i];

        if(i < path.size() - 1)
        {
            std::cout << " -> ";
        }
    }

    std::cout << "\nLongitud de la ruta: "
              << path.size() - 1
              << " conexiones.\n";
}

    int getTotalConnectionsCount() {
        int totalEdges = 0;
        for (const auto& vertex : vertices) {
            AdjNode* current = vertex.head;
            while (current != nullptr) {
                totalEdges++;
                current = current->next;
            }
        }
        return totalEdges / 2;
    }

    void printStatistics() {
        int totalVertices = vertices.size();
        int totalEdgesInMemory = 0;

        // 1. Contamos de forma absoluta cuántos nodos de adyacencia hay creados
        for (size_t i = 0; i < vertices.size(); ++i) {
            AdjNode* current = vertices[i].head;
            while (current != nullptr) {
                totalEdgesInMemory++;
                current = current->next;
            }
        }

        //En un grafo no dirigido (bidireccional), las conexiones reales son la mitad
        int aristasReales = totalEdgesInMemory / 2;

        //Controlamos si el grafo está completamente vacío para evitar errores de división por cero
        double promedio = 0.0;
        if (totalVertices > 0) {
            //Convertimos a double para forzar los decimales correctos
            promedio = (double)totalEdgesInMemory / totalVertices;
        }

        std::cout << "=========================================\n";
        std::cout << "         ESTADISTICAS DEL GRAFO          \n";
        std::cout << "=========================================\n";
        std::cout << "Total de Estudiantes (Vertices): " << totalVertices << "\n";
        std::cout << "Total de Conexiones Reales (Aristas): " << aristasReales << "\n";
        std::cout << "Total de Conexiones en Memoria (Punteros): " << totalEdgesInMemory << "\n";
        std::cout << "Conexiones promedio por estudiante: " << promedio << "\n";
        std::cout << "=========================================\n";
    }

    void removeStudentVertex(int student_id)
{
    int target_index = findVertexIndex(student_id);

    if(target_index == -1)
        return;

    // Eliminar referencias al estudiante en otros nodos
    for(size_t i = 0; i < vertices.size(); i++)
    {
        AdjNode* current = vertices[i].head;
        AdjNode* prev = nullptr;

        while(current != nullptr)
        {
            if(current->student_id == student_id)
            {
                if(prev == nullptr)
                    vertices[i].head = current->next;
                else
                    prev->next = current->next;

                AdjNode* temp = current;
                current = current->next;
                delete temp;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
    }

    // Eliminar lista de adyacencia propia
    AdjNode* current = vertices[target_index].head;

    while(current != nullptr)
    {
        AdjNode* temp = current;
        current = current->next;
        delete temp;
    }

    vertices.erase(vertices.begin() + target_index);
}

};

#endif
