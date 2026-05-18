#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Student.h"
#include <vector>
#include <iostream>

struct HashNode {
    Student data;
    HashNode* next;
    HashNode(Student s) : data(s), next(nullptr) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 15000; // Tamaño base para la tabla
    HashNode* table[TABLE_SIZE];
    int totalElements;
    int collisions;

    int hashFunction(int id) {
        return id % TABLE_SIZE;
    }

public:
    HashTable() : totalElements(0), collisions(0) {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
    }

    void insert(Student s) {
        int index = hashFunction(s.student_id);
        HashNode* newNode = new HashNode(s);

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            // Ocurre una colisión
            collisions++;
            newNode->next = table[index];
            table[index] = newNode;
        }
        totalElements++;
    }

    Student* search(int id) {
        int index = hashFunction(id);
        HashNode* temp = table[index];
        while (temp) {
            if (temp->data.student_id == id) return &(temp->data);
            temp = temp->next;
        }
        return nullptr;
    }

    void displayStats() {
        std::cout << "\n[Estadisticas Tabla Hash]" << std::endl;
        std::cout << " - Colisiones totales: " << collisions << std::endl;
        std::cout << " - Factor de carga: " << (float)totalElements / TABLE_SIZE << std::endl;
    }
};

#endif
