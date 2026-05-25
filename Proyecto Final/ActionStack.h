#ifndef ACTIONSTACK_H
#define ACTIONSTACK_H

#include <string>
#include <iostream>

struct StackNode {
    std::string actionDescription;
    StackNode* next;
    StackNode(std::string desc) : actionDescription(desc), next(nullptr) {}
};

class ActionStack {
private:
    StackNode* topNode;
    int size;

public:
    ActionStack() : topNode(nullptr), size(0) {}

    // Insertar acción en la pila (Push)
    void push(std::string action) {
        StackNode* newNode = new StackNode(action);
        newNode->next = topNode;
        topNode = newNode;
        size++;
    }

    // Mostrar el historial de acciones recientes sin destruirlo
    void displayHistory(int limit = 5) {
        if (!topNode) {
            std::cout << "Historial vacio. No se han realizado acciones.\n";
            return;
        }
        std::cout << "\n--- HISTORIAL DE ULTIMAS ACCIONES (" << size << " en total) ---\n";
        StackNode* temp = topNode;
        int count = 0;
        while (temp && count < limit) {
            std::cout << " [" << count + 1 << "] " << temp->actionDescription << "\n";
            temp = temp->next;
            count++;
        }
        std::cout << "-------------------------------------------\n";
    }

    // Destructor para evitar fugas de memoria
    ~ActionStack() {
        while (topNode) {
            StackNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};

#endif
