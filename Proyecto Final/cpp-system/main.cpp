//Priscila Guzmán
#include <iostream>
#include <string>
#include "Student.h"
#include "HashTable.h"
#include "AVL.h"
#include "Graph.h"
#include "ActionStack.h"
#include "CSVReader.h"
#include "Benchmark.h"
#include <chrono>

using namespace std;
double datasetLoadTime = 0;

// Función auxiliar para limpiar el buffer de entrada en caso de errores de lectura o saltos de línea
void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int main() {
    //Instanciación de las estructuras principales del sistema
    HashTable studentTable;
    AVLTree rankingTree;
    Graph socialGraph;
    ActionStack activityHistory;

    int mainOption = 0;

    cout << "===============================================================" << endl;
    cout << "        Priscila Sarai Guzmán Calgua 9941-23-450               " << endl;
    do {
        cout << "===========================================================" << endl;
        cout << "                      MENU PRINCIPAL                       " << endl;
        cout << "===========================================================" << endl;
        cout << " 1. Cargar estudiantes desde CSV" << endl;
        cout << " 2. Registrar estudiante manualmente" << endl;
        cout << " 3. Buscar estudiante por ID" << endl;
        cout << " 4. Eliminar estudiante" << endl;
        cout << " 5. Agregar proyecto a estudiante" << endl;
        cout << " 6. Mostrar proyectos de estudiante" << endl;
        cout << " 7. Buscar proyecto de estudiante" << endl;
        cout << " 8. Eliminar proyecto de estudiante" << endl;
        cout << " 9. Conectar estudiantes" << endl;
        cout << "10. Verificar si dos estudiantes estan conectados" << endl;
        cout << "11. Mostrar conexiones de estudiante" << endl;
        cout << "12. Recorrer red con BFS" << endl;
        cout << "13. Recorrer red con DFS" << endl;
        cout << "14. Mostrar ranking academico" << endl;
        cout << "15. Mostrar estadisticas de estructuras" << endl;
        cout << "16. Generar benchmark C++" << endl;
        cout << "17. Ruta mas corta entre estudiantes" << endl;
        cout << "18. Ver historial de acciones" << endl;
        cout << "19. Salir" << endl;
        cout << "=========================================================" << endl;
        cout << "Seleccione una opcion (1-19): ";

        if (!(cin >> mainOption)) {
            cout << "\n Error: Por favor, ingrese un numero valido." << endl;
            clearInput();
            continue;
        }

        switch (mainOption) {
            case 1: {
                cout << "\n Cargando base de datos desde 'estudiantes.csv'..." << endl;
                auto start =
                chrono::high_resolution_clock::now();

                CSVReader::loadStudents("estudiantes.csv",studentTable,rankingTree,socialGraph);
                auto end =
                chrono::high_resolution_clock::now();
                datasetLoadTime =
                chrono::duration<double, milli>(end - start).count();
                cout << "\nTiempo de carga: "<< datasetLoadTime<< " ms" << endl;
                activityHistory.push("Carga masiva de estudiantes completada desde archivo CSV.");
                break;
                }
            case 2: {
                Student newStudent;
                cout << "\n--- Registrar Nuevo Estudiante ---" << endl;
                cout << "Ingrese ID: "; cin >> newStudent.student_id;

                if (studentTable.search(newStudent.student_id)) {
                    cout << "\n Error: El ID " << newStudent.student_id << " ya existe." << endl;
                    break;
                }

                cin.ignore();
                cout << "Ingrese Nombre Completo: "; getline(cin, newStudent.full_name);
                cout << "Ingrese Carrera: "; getline(cin, newStudent.career);
                cout << "Ingrese Semestre actual: "; cin >> newStudent.semester;
                cout << "Ingrese Promedio (GPA): "; cin >> newStudent.gpa;
                cout << "Ingrese Puntaje de Ranking (Skill Score): "; cin >> newStudent.skill_score;

                //Insertar de manera segura en las estructuras
                Student* insertedPtr = studentTable.insert(newStudent);
                if (insertedPtr) {
                    rankingTree.insert(*insertedPtr); //Sincronizar AVL
                    socialGraph.addStudentVertex(newStudent.student_id); //Registrar vértice en Grafo

                    cout << "\n Exito Estudiante registrado correctamente en todas las estructuras." << endl;
                    activityHistory.push("Insercion manual del estudiante ID " + to_string(newStudent.student_id) + ".");
                }
                break;
            }
            case 3: {
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

                    activityHistory.push("Busqueda exitosa del estudiante ID " + to_string(id) + ".");
                } else {
                    cout << "\n No se encontro ningun estudiante con el ID " << id << "." << endl;
                }
                break;
            }
            case 4: {
                int id;
                cout << "\nIngrese el ID del estudiante a eliminar del sistema: ";
                cin >> id;

                Student* found = studentTable.search(id);
                if (found) {
                    //Remover del AVL antes de perder la referencia en memoria
                    rankingTree.remove(found->skill_score, found->student_id);

                    //Eliminación en cascada del Grafo Social (Elimina vértice y enlaces relacionados)
                    //Remover de la Tabla Hash (Libera la memoria dinámica del objeto)
                    string savedName = found->full_name;
                    if (studentTable.remove(id)) {
                        cout << "\n Exito El estudiante " << savedName << " ha sido removido de todas las estructuras." << endl;
                        activityHistory.push("Eliminacion completa en cascada del estudiante ID " + to_string(id) + ".");
                    }
                } else {
                    cout << "\n El ID solicitado no se encuentra registrado en el sistema." << endl;
                }
                break;
            }
            case 5: {
                int id;
                cout << "\nIngrese el ID del estudiante para agregar un proyecto: ";
                cin >> id;

                Student* found = studentTable.search(id);
                if (!found) {
                    cout << "\n El estudiante solicitado no existe en el sistema." << endl;
                    break;
                }

                int p_id, p_year;
                string p_title, p_desc;
                cout << "Ingrese ID unico del proyecto: "; cin >> p_id;
                cin.ignore();
                cout << "Titulo del proyecto: "; getline(cin, p_title);
                cout << "Descripcion breve: "; getline(cin, p_desc);
                cout << "Año de finalizacion: "; cin >> p_year;

                if (found->addProject(p_id, p_title, p_desc, p_year)) {
                    cout << "\n Exito Proyecto incorporado a la Lista Enlazada del estudiante." << endl;
                    activityHistory.push("Proyecto ID " + to_string(p_id) + " asignado al estudiante ID " + to_string(id) + ".");
                } else {
                    cout << "\n Error: Ya existe un proyecto con el ID " << p_id << " para este estudiante." << endl;
                }
                break;
            }
            case 6: {
                int id;
                cout << "\nIngrese el ID del estudiante para ver sus proyectos: ";
                cin >> id;

                Student* found = studentTable.search(id);
                if (found) {
                    found->displayProjects();
                } else {
                    cout << "\n Error: El estudiante solicitado no existe." << endl;
                }
                break;
                }

            case 7: {
                int studentId, projectId;
                cout << "\nIngrese ID del estudiante: ";
                cin >> studentId;

                Student* found = studentTable.search(studentId);
                if (!found) {
                        cout << "\n[ERROR] Estudiante no encontrado.\n";
                break;
                }
                cout << "Ingrese ID del proyecto: ";
                cin >> projectId;

                Project* project = found->searchProject(projectId);
                if (project) {
                cout << "\n=== PROYECTO ENCONTRADO ===\n";
                cout << "ID: " << project->project_id << endl;
                cout << "Titulo: " << project->title << endl;
                cout << "Descripcion: " << project->description << endl;
                cout << "Anio: " << project->completion_year << endl;
                }else {
                    cout << "\nProyecto no encontrado.\n";
                    }
                    break;
                    }

            case 8: {
                int studentId, projectId;
                cout << "\nIngrese ID del estudiante: ";
                cin >> studentId;

                Student* found = studentTable.search(studentId);
                if (!found) {
                        cout << "\n[ERROR] Estudiante no encontrado.\n";
                break;
                }
                cout << "Ingrese ID del proyecto a eliminar: ";
                cin >> projectId;
                if (found->removeProject(projectId)) {
                        cout << "\nProyecto eliminado correctamente.\n";

                activityHistory.push("Proyecto ID " +to_string(projectId) +" eliminado del estudiante ID " +to_string(studentId));
                }
                else {
                        cout << "\nNo existe un proyecto con ese ID.\n";
                }
                break;
                }


            case 9: {
                int id1, id2;
                cout << "\n--- Establecer Conexion ---" << endl;
                cout << "Ingrese el ID del primer estudiante: "; cin >> id1;
                cout << "Ingrese el ID del segundo estudiante: "; cin >> id2;

                if (id1 == id2) {
                    cout << "\n Error No se permite conectar un estudiante consigo mismo." << endl;
                    break;
                }

                // Validar la existencia en la tabla hash central
                if (!studentTable.search(id1) || !studentTable.search(id2)) {
                    cout << "\n Error: Uno o ambos IDs no estan registrados en el sistema. Imposible conectar." << endl;
                    break;
                }

                //Asegurar existencia estructural de nodos e insertar conexión
                socialGraph.addStudentVertex(id1);
                socialGraph.addStudentVertex(id2);

                socialGraph.connectStudents(id1, id2);
                activityHistory.push("Conexion social registrada entre ID " + to_string(id1) + " e ID " + to_string(id2) + ".");
                break;
            }
            case 10: {
                int id1, id2;
                cout << "\n--- Verificar Conectividad Directa ---" << endl;
                cout << "Ingrese ID del primer estudiante: "; cin >> id1;
                cout << "Ingrese ID del segundo estudiante: "; cin >> id2;

                if (socialGraph.areConnected(id1, id2)) {
                    cout << "\n Resultado:SI existe una conexion directa entre el estudiante " << id1 << " y el estudiante " << id2 << "." << endl;
                } else {
                    cout << "\n Resultado:NO existe una conexion directa entre los estudiantes consultados." << endl;
                }
                break;
            }
            case 11: {
                int id;
                cout << "\nIngrese el ID del estudiante: "; cin >> id;
                socialGraph.displayConnections(id);
                break;
            }
            case 12: {
                int id;
                cout << "\nIngrese el ID del estudiante para iniciar el recorrido BFS: "; cin >> id;
                cout << "\n--- Recorrido BFS (Amplitud) ---" << endl;
                socialGraph.BFS(id); //Ejecuta el BFS interactivo e imprime en consola
                cout << endl;
                break;
            }
            case 13: {
                int id;
                cout << "\nIngrese el ID del estudiante para iniciar el recorrido DFS: "; cin >> id;
                cout << "\n--- Recorrido DFS (Profundidad) ---" << endl;
                socialGraph.DFS(id); //Ejecuta el DFS interactivo e imprime en consola
                cout << endl;
                break;
            }
            case 14: {
                cout << "\nGenerando desde el Arbol AVL de balance automatico..." << endl;
                rankingTree.displayRanking();
                activityHistory.push("Visualizacion completa del Ranking Academico Global");
                break;
            }
            case 15: {
                cout << "\n=========================================================" << endl;
                cout << "                 ESTADISTICAS ESTRUCTURALES                " << endl;
                cout << "===========================================================" << endl;

                studentTable.displayStats(); //Total estudiantes, colisiones, factor carga
                rankingTree.displayStats();  //Altura del AVL

                cout << "Total de proyectos registrados: "<< studentTable.countAllProjects()<< endl;

                cout << "\n[Estadisticas Grafo Social]" << endl;
                // Corrige: llama al método directamente sin meterlo en otro cout
                socialGraph.printStatistics();
                cout << "\nTotal de conexiones creadas: "<< socialGraph.getTotalConnectionsCount()<< endl;
                cout << "\nTiempo total de carga del dataset: "<< datasetLoadTime<< " ms" << endl;
                cout << "=========================================================" << endl;
                break;
                }
            case 16: {
                cout << "\n Ejecutando Benchmark aislado con 10,000 registros..." << endl;
                Benchmark::runBenchmark();
                cout << "Modulo completado. Archivo 'cpp_results.csv' generado de forma limpia." << endl;
                activityHistory.push("Se ejecuto el modulo de Benchmark de C++. Archivo cpp_results.csv generado.");
                break;
            }
            case 17:{
                int origen, destino;
                cout << "\n===== RUTA MAS CORTA =====" << endl;
                cout << "Ingrese ID de origen: ";
                cin >> origen;
                cout << "Ingrese ID destino: ";
                cin >> destino;

                socialGraph.findShortestPath(origen, destino);
                activityHistory.push("Consulta de ruta mas corta entre ID "+ to_string(origen)+ " y ID "+ to_string(destino));
                break;
                }
                case 18: {
                    cout << "\n========================================" << endl;
                    cout << "      HISTORIAL DE ACCIONES DEL SISTEMA" << endl;
                    cout << "=========================================" << endl;

                    activityHistory.displayHistory();
                    cout << "=========================================" << endl;
                    break;
                    }
            case 19:
                cout << "\nCerrando el sistema de Red. Liberando recursos de memoria asignados de forma dinamica..." << endl;
                break;
                default:
                    cout << "\n[Opcion Invalida] Por favor seleccione una accion del 1 al 16." << endl;

        }

    } while (mainOption != 19);

    return 0;
}
