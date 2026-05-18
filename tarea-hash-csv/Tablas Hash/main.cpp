#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Student.h"
#include "HashTable.h"

using namespace std;

// Función para leer el archivo CSV e insertar datos automáticamente
void cargarCSV(string nombreArchivo, HashTable& tabla) {
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    getline(archivo, linea); // Saltar encabezado
    int contador = 0;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Student s;
        string temp;

        getline(ss, temp, ','); s.student_id = stoi(temp);
        getline(ss, s.full_name, ',');
        getline(ss, s.career, ',');
        getline(ss, temp, ','); s.semester = stoi(temp);
        getline(ss, temp, ','); s.gpa = stof(temp);
        getline(ss, temp, ','); s.skill_score = stoi(temp);

        if(tabla.insertar(s)) contador++;
    }
    cout << ">>> Exito: " << contador << " estudiantes cargados." << endl;
    archivo.close();
}

int main() {
    cout << "==========================================" << endl;
    cout << "NOMBRE: Priscila Guzman" << endl;
    cout << "CARNE: 9941-23-450" << endl;
    cout << "==========================================\n" << endl;

    HashTable miHash;

    // Intentar cargar datos automáticamente al iniciar
    cargarCSV("estudiantes.csv", miHash);

    int opcion;
    do {
        cout << "\n========== MENU HASH TABLE ==========\n";
        cout << "1. Insertar estudiante \n";
        cout << "2. Buscar estudiante por ID\n";
        cout << "3. Eliminar estudiante\n";
        cout << "4. Mostrar tabla \n";
        cout << "5. Mostrar estadisticas\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Student s;
            cout << "Ingrese ID: "; cin >> s.student_id;
            cin.ignore();
            cout << "Ingrese Nombre: "; getline(cin, s.full_name);
            cout << "Ingrese Carrera: "; getline(cin, s.career);
            cout << "Ingrese Semestre: "; cin >> s.semester;
            cout << "Ingrese Promedio (GPA): "; cin >> s.gpa;
            cout << "Ingrese Skill Score: "; cin >> s.skill_score;

            if(miHash.insertar(s)) cout << "Estudiante agregado.\n";
            else cout << "Error: ID duplicado.\n";

        } else if (opcion == 2) {
            int id;
            cout << "Ingrese ID a buscar: "; cin >> id;
            Student* encontrado = miHash.buscar(id);
            if (encontrado) {
                cout << "\n--- DATOS ENCONTRADOS ---\n";
                cout << "Nombre:   " << encontrado->full_name << endl;
                cout << "Carrera:  " << encontrado->career << endl;
                cout << "Promedio: " << encontrado->gpa << endl;
                cout << "-------------------------\n";
            } else cout << "No se encontro el estudiante.\n";

        } else if (opcion == 3) {
            int id;
            cout << "Ingrese ID a eliminar: "; cin >> id;
            if(miHash.eliminar(id)) cout << "Eliminado con exito.\n";
            else cout << "ID no encontrado.\n";

        } else if (opcion == 4) {
            miHash.mostrarTabla();

        } else if (opcion == 5) {
            miHash.mostrarEstadisticas();

        } else if (opcion == 6) {
            cout << "Cerrando sistema académico...\n";
        }
    } while (opcion != 6);

    return 0;
}
