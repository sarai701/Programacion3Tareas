//Priscila Guzmán 9941-23-450
#include <iostream>
#include <string>
#include "AVL.h"
#include "Student.h"

using namespace std;

void showMenu() {
    cout << "\n--- MODULO DE RANKING ACADEMICO (AVL) ---" << endl;
    cout << "1. Insertar estudiante" << endl;
    cout << "2. Mostrar ranking academico (InOrden)" << endl;
    cout << "3. Buscar por skill_score" << endl;
    cout << "4. Mostrar estadisticas AVL" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    cout << "\n---Priscila Guzmán 9941-23-450---" << endl;
    AVLTree rankingTree; //Instancia global del árbol balanceado
    int option;

    do {
        showMenu();
        cin >> option;

        switch (option) {
            case 1: {
                Student newStudent;
                cout << "\n--- Registro de Estudiante ---" << endl;
                cout << "ID: "; cin >> newStudent.student_id;
                cin.ignore(); // Limpiar el buffer para leer strings con espacios
                cout << "Nombre completo: "; getline(cin, newStudent.full_name);
                cout << "Carrera: "; getline(cin, newStudent.career);
                cout << "Semestre: "; cin >> newStudent.semester;
                cout << "Promedio: "; cin >> newStudent.promedio;
                cout << "Skill Score: "; cin >> newStudent.skill_score;

                //Inserción en el árbol con balanceo automático
                rankingTree.insert(newStudent);
                cout << "Estudiante insertado y arbol balanceado correctamente." << endl;
                break;
            }
            case 2: {
                //El recorrido InOrden garantiza que el ranking aparezca ordenado
                cout << "\n--- RANKING ACADEMICO ACTUAL ---" << endl;
                rankingTree.displayRanking();
                break;
            }
            case 3: {
                //Búsqueda eficiente (O log n) por puntaje
                int scoreToSearch;
                cout << "Ingrese el Skill Score a buscar: ";
                cin >> scoreToSearch;
                rankingTree.findAndPrint(scoreToSearch);
                break;
            }
            case 4: {
                // Información sobre el estado de balance del árbol
                rankingTree.displayStats();
                break;
            }
            case 5:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (option != 5); //El ciclo se repite hasta que el usuario elige salir

    return 0;
}
