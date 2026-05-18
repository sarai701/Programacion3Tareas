#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Student.h"
#include <iostream>

// Nodo para la lista enlazada (Manejo de colisiones por encadenamiento)
struct HashNode {
    Student data;
    HashNode* next;
    HashNode(Student s) : data(s), next(nullptr) {}
};

class HashTable {
private:
    static const int SIZE = 20; // Cantidad de "cubetas" o buckets
    HashNode* tabla[SIZE];
    int totalElementos;
    int totalColisiones;

    // Función Hash: Determina el índice basado en el ID del estudiante
    int funcionHash(int id) {
        return id % SIZE;
    }

public:
    HashTable() : totalElementos(0), totalColisiones(0) {
        for (int i = 0; i < SIZE; i++) tabla[i] = nullptr;
    }

    // Inserta un estudiante validando que no sea duplicado
    bool insertar(Student s) {
        if (buscar(s.student_id) != nullptr) return false;

        int indice = funcionHash(s.student_id);
        HashNode* nuevo = new HashNode(s);

        // Si el bucket ya tiene datos, registramos una colisión
        if (tabla[indice] != nullptr) totalColisiones++;

        // Insertar al inicio de la lista (más rápido)
        nuevo->next = tabla[indice];
        tabla[indice] = nuevo;
        totalElementos++;
        return true;
    }

    // Busca un estudiante por ID y retorna un puntero a sus datos
    Student* buscar(int id) {
        int indice = funcionHash(id);
        HashNode* actual = tabla[indice];
        while (actual != nullptr) {
            if (actual->data.student_id == id) return &(actual->data);
            actual = actual->next;
        }
        return nullptr;
    }

    // Elimina un nodo de la lista enlazada liberando memoria
    bool eliminar(int id) {
        int indice = funcionHash(id);
        HashNode* actual = tabla[indice];
        HashNode* anterior = nullptr;

        while (actual != nullptr) {
            if (actual->data.student_id == id) {
                if (anterior == nullptr) tabla[indice] = actual->next;
                else anterior->next = actual->next;
                delete actual;
                totalElementos--;
                return true;
            }
            anterior = actual;
            actual = actual->next;
        }
        return false;
    }

    // Imprime visualmente cómo están distribuidos los datos
    void mostrarTabla() {
        std::cout << "\n--- CONTENIDO POR BUCKET ---" << std::endl;
        for (int i = 0; i < SIZE; i++) {
            std::cout << "Bucket [" << i << "]: ";
            HashNode* actual = tabla[i];
            if (!actual) std::cout << "vacio";
            while (actual) {
                std::cout << "[" << actual->data.student_id << ": " << actual->data.full_name << "] -> ";
                actual = actual->next;
            }
            std::cout << "NULL" << std::endl;
        }
    }

    // Muestra el rendimiento de la tabla
    void mostrarEstadisticas() {
        std::cout << "\n--- ESTADISTICAS HASH ---" << std::endl;
        std::cout << "Total de estudiantes: " << totalElementos << std::endl;
        std::cout << "Total de colisiones: " << totalColisiones << std::endl;
        std::cout << "Factor de carga: " << (float)totalElementos / SIZE << std::endl;
    }

    // Destructor para evitar fugas de memoria
    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            HashNode* actual = tabla[i];
            while (actual) {
                HashNode* temp = actual;
                actual = actual->next;
                delete temp;
            }
        }
    }
};
#endif
