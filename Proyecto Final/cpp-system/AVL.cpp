//Priscila Guzmán
#include "AVL.h"
#include <iostream>
#include <algorithm>

int AVLTree::getHeight(AVLNode* n) { return n ? n->height : 0; }

int AVLTree::getBalanceFactor(AVLNode* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, Student student) {
    if (!node) {
        nodeCount++;
        return new AVLNode(student);
    }

    // Lógica de Ranking: Mayores a la izquierda
    if (student.isGreaterThan(node->data))
        node->left = insert(node->left, student);
    else
        node->right = insert(node->right, student);

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    if (bf > 1 && student.isGreaterThan(node->left->data)) return rotateRight(node);
    if (bf < -1 && !student.isGreaterThan(node->right->data)) return rotateLeft(node);
    if (bf > 1 && !student.isGreaterThan(node->left->data)) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bf < -1 && student.isGreaterThan(node->right->data)) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLNode* AVLTree::remove(AVLNode* root, int score, int id) {
    if (!root) return root;

    if (score > root->data.skill_score || (score == root->data.skill_score && id > root->data.student_id))
        root->left = remove(root->left, score, id);
    else if (score < root->data.skill_score || (score == root->data.skill_score && id < root->data.student_id))
        root->right = remove(root->right, score, id);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else *root = *temp;
            delete temp;
            nodeCount--;
        } else {
            AVLNode* temp = getMinNode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data.skill_score, temp->data.student_id);
        }
    }

    if (!root) return root;

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    if (bf > 1 && getBalanceFactor(root->left) >= 0) return rotateRight(root);
    if (bf > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (bf < -1 && getBalanceFactor(root->right) <= 0) return rotateLeft(root);
    if (bf < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

AVLNode* AVLTree::getMinNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr) current = current->left;
    return current;
}

void AVLTree::displayRanking() {
    int rank = 1;
    std::cout << "\nPuesto\t| ID\t| Nombre\t\t\t| Score\n";
    std::cout << "---------------------------------------------------------\n";
    inOrder(root, rank);
}

void AVLTree::inOrder(AVLNode* node, int& rank) {
    if (node) {
        inOrder(node->left, rank);
        std::cout << rank++ << "\t| " << node->data.student_id
                  << "\t| " << node->data.full_name
                  << "\t\t| Score: " << node->data.skill_score << std::endl;
        inOrder(node->right, rank);
    }
}

// Implementación del método silencioso exclusivo para el Benchmark masivo
void AVLTree::inOrderSilent(AVLNode* node) {
    if (node) {
        inOrderSilent(node->left);
        // Solo visitamos el nodo en memoria, sin imprimir en consola
        int dummy = node->data.skill_score;
        inOrderSilent(node->right);
    }
}

void AVLTree::displayStats() {
    std::cout << "\n[Estadisticas AVL]" << std::endl;
    std::cout << " - Altura actual del arbol: " << getHeight(root) << std::endl;
    std::cout << " - Total estudiantes registrados: " << nodeCount << std::endl;
}

AVLNode* AVLTree::search(AVLNode* node, int score) {
    if (!node || node->data.skill_score == score) return node;
    return (score > node->data.skill_score) ? search(node->left, score) : search(node->right, score);
}

// Solución al método faltante para evitar errores de compilación
void AVLTree::findAndPrint(int score) {
    AVLNode* result = search(root, score);
    if (result) {
        std::cout << "\n[Estudiante Encontrado con Score " << score << "]:\n";
        std::cout << "ID: " << result->data.student_id << " | Nombre: " << result->data.full_name << std::endl;
    } else {
        std::cout << "\n[Aviso] No existen estudiantes con el score: " << score << std::endl;
    }
}
