#include <iostream>
#include "AVL.h"
#include "HashTable.h"
#include "CSVReader.h"

using namespace std;

int main() {
    AVLTree rankingTree;
    HashTable studentTable;

    cout << "--- SISTEMA DE RED SOCIAL ACADEMICA ---" << endl;

    // Probar la carga masiva
    CSVReader::loadStudents("estudiantes.csv", studentTable, rankingTree);

    // Probar búsqueda en Hash (ID 1001 suele ser el primero)
    cout << "\nBuscando estudiante ID 1001 en Tabla Hash..." << endl;
    Student* found = studentTable.search(1001);
    if(found) {
        cout << "Encontrado: " << found->full_name << " | Carrera: " << found->career << endl;
    }

    // Mostrar ranking inicial del AVL
    cout << "\nRanking Academico (Primeros lugares):" << endl;
    rankingTree.displayRanking();

    // Mostrar estadísticas
    studentTable.displayStats();
    rankingTree.displayStats();

    return 0;
}
