#include "AVL.h"

int AVLTree::getHeight(AVLNode* n) { return n ? n->height : 0; }

int AVLTree::getBalanceFactor(AVLNode* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

//Realiza una rotación simple a la derecha para reequilibrar el subárbol
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    // Actualización de alturas tras el movimiento
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

    // Ordenar por skill_score (mayor a la izquierda para ranking descendente)
    if (student.isGreaterThan(node->data))
        node->left = insert(node->left, student);
    else
        node->right = insert(node->right, student);

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    // Casos de rotación
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

// Implementación del método de búsqueda para el main
void AVLTree::findAndPrint(int score) {
    AVLNode* result = search(root, score);
    if (result != nullptr) {
        std::cout << "\n--- Estudiante Encontrado ---" << std::endl;
        std::cout << "ID: " << result->data.student_id << std::endl;
        std::cout << "Nombre: " << result->data.full_name << std::endl;
        std::cout << "Score: " << result->data.skill_score << std::endl;
        std::cout << "Carrera: " << result->data.career << std::endl;
    } else {
        std::cout << "\nNo se encontro ningun estudiante con el score: " << score << std::endl;
    }
}

// Función auxiliar recursiva para buscar en el árbol
AVLNode* AVLTree::search(AVLNode* node, int score) {
    if (node == nullptr || node->data.skill_score == score)
        return node;

    // Dado que nuestro AVL está ordenado de mayor a menor para el ranking
    if (score > node->data.skill_score)
        return search(node->left, score);

    return search(node->right, score);
}

void AVLTree::displayRanking() {
    int rank = 1;
    inOrder(root, rank);
}

//Recorrido InOrden optimizado para mostrar el ranking académico
void AVLTree::inOrder(AVLNode* node, int& rank) {
    if (node) {
        inOrder(node->left, rank);
        std::cout << rank++ << ". " << node->data.full_name
                  << " - Score: " << node->data.skill_score << std::endl;
        inOrder(node->right, rank);
    }
}

void AVLTree::displayStats() {
    std::cout << "--- Estadísticas AVL ---" << std::endl;
    std::cout << "Altura raíz: " << getHeight(root) << std::endl;
    std::cout << "Factor balance raíz: " << getBalanceFactor(root) << std::endl;
    std::cout << "Nodos totales: " << nodeCount << std::endl;
}
