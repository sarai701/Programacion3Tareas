#include <iostream>
#include <string>
#include "Student.h"
#include "HashTable.h"
#include "AVL.h"
#include "Graph.h"
#include "ActionStack.h"
#include "CSVReader.h"
#include "Benchmark.h"

using namespace std;

// Función auxiliar para limpiar el buffer de entrada en caso de errores de lectura
void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int main() {
    // Instanciación de las estructuras principales del sistema
    HashTable studentTable;
    AVLTree rankingTree;
    Graph socialGraph;
    ActionStack activityHistory;

    int mainOption = 0;

    cout << "=========================================================" << endl;
    cout << "        SISTEMA DE RED SOCIAL ACADEMICA UNIVERSITARIA     " << endl;
    cout << "=========================================================" << endl;

    // Ejecutar automáticamente la carga masiva para inicializar el ecosistema
    cout << "\n[Iniciando] Cargando base de datos desde 'estudiantes.csv'..." << endl;
    CSVReader::loadStudents("estudiantes.csv", studentTable, rankingTree);

    // Registrar el evento de carga masiva en nuestra Pila de actividades
    activityHistory.push("Carga masiva inicial de estudiantes completada desde archivo CSV.");

    do {
        cout << "\n=========================================================" << endl;
        cout << "                    MENU PRINCIPAL                        " << endl;
        cout << "=========================================================" << endl;
        cout << " 1. Buscar estudiante (Por ID)" << endl;
        cout << " 2. Insertar nuevo estudiante manualmente" << endl;
        cout << " 3. Eliminar estudiante del sistema" << endl;
        cout << " 4. Gestionar proyectos de un estudiante (Lista)" << endl;
        cout << " 5. Conectar dos estudiantes (Red Social / Grafo)" << endl;
        cout << " 6. Consultar amigos/conexiones de un estudiante" << endl;
        cout << " 7. Ver Ranking Academico Global (Top AVL)" << endl;
        cout << " 8. Ver Bitacora Reciente (Pila de Acciones)" << endl;
        cout << " 9. Ver Panel de Estadisticas Estructurales" << endl;
        cout << "10. Ejecutar Benchmark de Rendimiento (10,000 registros)" << endl;
        cout << "11. Salir de la aplicacion" << endl;
        cout << "=========================================================" << endl;
        cout << "Seleccione una opcion (1-11): ";

        if (!(cin >> mainOption)) {
            cout << "\n[Error] Por favor, ingrese un numero valido." << endl;
            clearInput();
            continue;
        }

        switch (mainOption) {
            case 1: {
                int id;
                cout << "\nIngrese el ID del estudiante a buscar: ";
                cin >> id;

                Student* found = studentTable.search(id);
                if (found) {
                    cout << "\n>>> ESTUDIANTE ENCONTRADO <<<" << endl;
                    cout << "ID: " << found->student_id << endl;
                    cout << "Nombre: " << found->full_name << endl;
                    cout << "Carrera: " << found->career << endl;
                    cout << "Semestre: " << found->semester << endl;
                    cout << "GPA: " << found->gpa << endl;
                    cout << "Skill Score: " << found->skill_score << endl;
                    found->displayProjects();

                    activityHistory.push("Busqueda exitosa del estudiante ID " + to_string(id) + " (" + found->full_name + ").");
                } else {
                    cout << "\n[Aviso] No se encontro ningun estudiante con el ID " << id << "." << endl;
                    activityHistory.push("Busqueda fallida del ID " + to_string(id) + " (No registrado).");
                }
                break;
            }
            case 2: {
                Student newStudent;
                cout << "\n--- Registrar Nuevo Estudiante ---" << endl;
                cout << "Ingrese ID (Unico): "; cin >> newStudent.student_id;

                if (studentTable.search(newStudent.student_id)) {
                    cout << "\n[Error] Violacion de restricciones: El ID " << newStudent.student_id << " ya existe." << endl;
                    break;
                }

                cin.ignore(); // Limpiar el salto de línea anterior
                cout << "Ingrese Nombre Completo: "; getline(cin, newStudent.full_name);
                cout << "Ingrese Carrera: "; getline(cin, newStudent.career);
                cout << "Ingrese Semestre actual: "; cin >> newStudent.semester;
                cout << "Ingrese Promedio (GPA): "; cin >> newStudent.gpa;
                cout << "Ingrese Puntaje de Ranking (Skill Score): "; cin >> newStudent.skill_score;

                // Insertar de manera segura en la tabla hash y capturar su posicion de memoria real
                Student* insertedPtr = studentTable.insert(newStudent);
                if (insertedPtr) {
                    rankingTree.insert(*insertedPtr); // Sincronizar el objeto real usando el asterisco
                    socialGraph.addStudentNode(insertedPtr->student_id); // Registrar nodo en el Grafo base
                    cout << "\n[Exito] Estudiante registrado e indexado correctamente en todas las estructuras." << endl;
                    activityHistory.push("Insercion manual del estudiante ID " + to_string(insertedPtr->student_id) + ".");
                }
                break;
            }
            case 3: {
                int id;
                cout << "\nIngrese el ID del estudiante a eliminar: ";
                cin >> id;

                Student* found = studentTable.search(id);
                if (found) {
                    //Remover del AVL usando sus llaves de ordenamiento antes de perder la referencia en memoria
                    rankingTree.remove(found->skill_score, found->student_id);

                    //Remover de la Tabla Hash (este metodo limpia fisicamente la memoria y la lista de proyectos)
                    string savedName = found->full_name;
                    if (studentTable.remove(id)) {
                        cout << "\n[Exito] El estudiante " << savedName << " ha sido removido del sistema de forma segura." << endl;
                        activityHistory.push("Eliminacion del estudiante ID " + to_string(id) + " (" + savedName + ").");
                    }
                } else {
                    cout << "\n[Aviso] El ID solicitado no se encuentra en el sistema." << endl;
                }
                break;
            }
            case 4: {
                int id;
                cout << "\nIngrese el ID del estudiante para gestionar sus proyectos: ";
                cin >> id;

                Student* found = studentTable.search(id);
                if (!found) {
                    cout << "\n[Error] El estudiante no existe." << endl;
                    break;
                }

                int subOption = 0;
                do {
                    cout << "\n--- Gestion de Proyectos [Estudiante: " << found->full_name << "] ---" << endl;
                    cout << "1. Mostrar proyectos vigentes" << endl;
                    cout << "2. Agregar nuevo proyecto académico" << endl;
                    cout << "3. Eliminar un proyecto (Por ID)" << endl;
                    cout << "4. Volver al menú principal" << endl;
                    cout << "Seleccione una sub-opcion: ";
                    cin >> subOption;

                    if (subOption == 1) {
                        found->displayProjects();
                    }
                    else if (subOption == 2) {
                        int p_id, p_year;
                        string p_title, p_desc;
                        cout << "Ingrese ID unico del proyecto: "; cin >> p_id;
                        cin.ignore();
                        cout << "Titulo del proyecto: "; getline(cin, p_title);
                        cout << "Descripcion breve: "; getline(cin, p_desc);
                        cout << "Ano de finalizacion: "; cin >> p_year;

                        if (found->addProject(p_id, p_title, p_desc, p_year)) {
                            cout << "\n[Exito] Proyecto agregado a la lista enlazada del estudiante." << endl;
                            activityHistory.push("Proyecto ID " + to_string(p_id) + " incorporado al estudiante ID " + to_string(id) + ".");
                        } else {
                            cout << "\n[Error] Ya existe un proyecto con ese ID en este estudiante." << endl;
                        }
                    }
                    else if (subOption == 3) {
                        int p_id;
                        cout << "Ingrese el ID del proyecto a eliminar: "; cin >> p_id;
                        if (found->removeProject(p_id)) {
                            cout << "\n[Exito] Proyecto removido e hilos de la lista reestructurados." << endl;
                            activityHistory.push("Proyecto ID " + to_string(p_id) + " eliminado del estudiante ID " + to_string(id) + ".");
                        } else {
                            cout << "\n[Aviso] No se encontro ese ID de proyecto." << endl;
                        }
                    }
                } while (subOption != 4);
                break;
            }
            case 5: {
                int id1, id2;
                cout << "\n--- Establecer Conexion Social ---" << endl;
                cout << "Ingrese el ID del primer estudiante: "; cin >> id1;
                cout << "Ingrese el ID del segundo estudiante: "; cin >> id2;

                // Asegurar la existencia de ambos en la base de datos central antes de enlazar en el grafo
                if (!studentTable.search(id1) || !studentTable.search(id2)) {
                    cout << "\n[Error] Uno o ambos IDs no estan registrados en la Tabla Hash. Imposible conectar." << endl;
                    break;
                }

                // Asegurar que los nodos existan estructuralmente en el grafo base
                socialGraph.addStudentNode(id1);
                socialGraph.addStudentNode(id2);

                if (socialGraph.connectStudents(id1, id2)) {
                    cout << "\n[Exito] Conexion establecida simetricamente (Arista no dirigida creada)." << endl;
                    activityHistory.push("Conexion social creada entre ID " + to_string(id1) + " e ID " + to_string(id2) + ".");
                } else {
                    cout << "\n[Aviso] No se pudo crear la conexion (¿Los estudiantes ya eran amigos o ingreso el mismo ID?)." << endl;
                }
                break;
            }
            case 6: {
                int id;
                cout << "\nIngrese el ID del estudiante para auditar su red: "; cin >> id;
                socialGraph.displayConnections(id);
                break;
            }
            case 7: {
                cout << "\nGenerando escalafon desde el Arbol AVL de balance automatico..." << endl;
                rankingTree.displayRanking();
                activityHistory.push("Visualizacion completa del Ranking Academico Global.");
                break;
            }
            case 8: {
                activityHistory.displayHistory(8); // Muestra los últimos 8 eventos guardados
                break;
            }
            case 9: {
                cout << "\n=========================================================" << endl;
                cout << "         PANEL DE AUDITORIA Y CONTROL DE CALIDAD          " << endl;
                cout << "=========================================================" << endl;

                studentTable.displayStats();

                rankingTree.displayStats();

                cout << "\n[Estadisticas Grafo Social]" << endl;
                cout << " - Total conexiones activas en la red: " << socialGraph.getTotalConnections() << endl;
                cout << "=========================================================" << endl;
                break;
            }
            case 10: {
                Benchmark::runBenchmark();
                activityHistory.push("Se ejecuto el módulo de Benchmark de C++ (10,000 registros). Archivo cpp_results.csv generado.");
                break;
            }
            case 11:
                cout << "\nCerrando el sistema. Liberando recursos de memoria asignados de forma dinamica..." << endl;
                break;
            default:
                cout << "\n[Opcion Invalida] Por favor seleccione una accion del 1 al 11." << endl;
        }

    } while (mainOption != 11);

    return 0;
}
