#ifndef AVL_H
#define AVL_H

#include "Student.h"
#include <iostream>
#include <algorithm>

//Nodo del árbol AVL que almacena un objeto Student
class AVLNode {
public:
    Student data;
    AVLNode *left, *right;
    int height;

    AVLNode(Student s) : data(s), left(nullptr), right(nullptr), height(1) {}
};

//Mantiene los datos balanceados automáticamente tras cada inserción
class AVLTree {
private:
    AVLNode* root;
    int nodeCount;

    int getHeight(AVLNode* n);
    int getBalanceFactor(AVLNode* n);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insert(AVLNode* node, Student student);
    void inOrder(AVLNode* node, int& rank);
    AVLNode* search(AVLNode* node, int score);

public:
    AVLTree() : root(nullptr), nodeCount(0) {}
    void insert(Student s) { root = insert(root, s); } //Inserta un estudiante manteniendo el balance
    void displayRanking(); // Imprime el ranking (InOrden)
    void findAndPrint(int score); // Busca por puntaje
    void displayStats(); // Muestra altura y balance de la raíz
};

#endif
