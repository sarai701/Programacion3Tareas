#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Student.h"
#include <iostream>

struct HashNode {
    Student data;
    HashNode* next;
    HashNode(Student s) : data(s), next(nullptr) {}
};

class HashTable {
private:
    // Ajustado de 15,000 a 2000
    static const int TABLE_SIZE = 2000;
    HashNode* table[TABLE_SIZE];
    int totalElements;
    int collisions;

    int hashFunction(int id) { return id % TABLE_SIZE; }

public:
    HashTable() : totalElements(0), collisions(0) {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
    }

    // Retorna Student* para enlazar las demas estructuras
    Student* insert(Student s) {
        if (search(s.student_id)) return nullptr; // Evitar ID duplicados

        int index = hashFunction(s.student_id);
        HashNode* newNode = new HashNode(s);

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            collisions++; //colisiones
            newNode->next = table[index];
            table[index] = newNode;
        }
        totalElements++;
        return &(newNode->data);
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

    bool remove(int id) {
        int index = hashFunction(id);
        HashNode* temp = table[index];
        HashNode* prev = nullptr;

        while (temp) {
            if (temp->data.student_id == id) {
                if (prev == nullptr) table[index] = temp->next;
                else prev->next = temp->next;

                // Limpieza absoluta de la sublista de proyectos del estudiante eliminado
                Project* currProj = temp->data.projectsHead;
                while (currProj) {
                    Project* nextProj = currProj->next;
                    delete currProj;
                    currProj = nextProj;
                }
                delete temp;
                totalElements--;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    int getCollisions() { return collisions; }
    int getTotalElements() { return totalElements; }
    float getLoadFactor() { return (float)totalElements / TABLE_SIZE; }

    void displayStats() {
        std::cout << "\n[Estadisticas Tabla Hash]" << std::endl;
        std::cout << " - Total estudiantes: " << totalElements << std::endl;
        std::cout << " - Colisiones totales: " << collisions << std::endl;
        std::cout << " - Factor de carga: " << getLoadFactor() << std::endl;
    }
};

#endif
