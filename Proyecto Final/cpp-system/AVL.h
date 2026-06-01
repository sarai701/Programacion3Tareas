//Priscila Guzmán
#ifndef AVL_H
#define AVL_H

#include "Student.h"

class AVLNode {
public:
    Student data;       //Objeto estudiante almacenado
    AVLNode *left;      //Puntero a hijo izquierdo
    AVLNode *right;     //Puntero a hijo derecho
    int height;         //Altura del nodo para calcular el balance

    AVLNode(Student s) : data(s), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;      //Raíz del árbol
    int nodeCount;      //Contador de nodos para estadísticas

    //Métodos de utilidad interna (Privados)
    int getHeight(AVLNode* n);
    int getBalanceFactor(AVLNode* n);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insert(AVLNode* node, Student student);
    AVLNode* remove(AVLNode* root, int score, int id);
    AVLNode* getMinNode(AVLNode* node);
    AVLNode* search(AVLNode* node, int score);
    void inOrder(AVLNode* node, int& rank);
    void inOrderSilent(AVLNode* node); //para benchmark

public:
    AVLTree() : root(nullptr), nodeCount(0) {}

    void insert(Student s) { root = insert(root, s); }
    void remove(int score, int id) { root = remove(root, score, id); }

    void displayRanking();
    void findAndPrint(int score);
    void displayStats();

    //Getters necesarios para el módulo de Benchmark
    int getNodeCount() { return nodeCount; }
    int getRootHeight() { return getHeight(root); }

    //Ejecuta el recorrido por los 10,000 nodos de manera 100% silenciosa en memoria
    void runSilentTraversal() { inOrderSilent(root); }
};

#endif
