//Priscila Guzmán 9941-23-450
#include <iostream>
#include <string>
#include <limits>

using namespace std;
//Representa un estudiante en la lista enlazada
struct Nodo {
    string carne;
    string nombre;
    string apellido;
    string carrera;
    Nodo* siguiente;//Puntero de enlace hacia el siguiente elemento
};

//Funciones para las operaciones de la lista
void insertarInicio(Nodo*& head);
void insertarFinal(Nodo*& head);
void mostrarEstudiantes(Nodo* head);
void buscarEstudiante(Nodo* head);
void eliminarEstudiante(Nodo*& head);

int main() {
    Nodo* lista = NULL;//Inicialización de la cabeza de la lista como vacía
    int opcion;

    do {
        cout << "\n==========================================" << endl;
        cout << "   Estudiante: Priscila Sarai Guzmán Calgua" << endl;
        cout << "   Carne: 9941-23-450" << endl;
        cout << "==========================================" << endl;
        cout << "1. Insertar estudiante al inicio" << endl;
        cout << "2. Insertar estudiante al final" << endl;
        cout << "3. Mostrar estudiantes" << endl;
        cout << "4. Buscar estudiante por carne" << endl;
        cout << "5. Eliminar estudiante" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";

        // Si el usuario ingresa algo que no es un número
        if (!(cin >> opcion)) {
            cout << "Error: Ingrese un numero valido." << endl;
            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: insertarInicio(lista); break;
            case 2: insertarFinal(lista); break;
            case 3: mostrarEstudiantes(lista); break;
            case 4: buscarEstudiante(lista); break;
            case 5: eliminarEstudiante(lista); break;
            case 6: cout << "Saliendo del programa..." << endl; break;
            default: cout << "Opcion no valida." << endl;
        }
    } while (opcion != 6);

    return 0;
}

// 1. Insertar al inicio
//Coloca y crea un nuevo nodo antes de la actual cabeza
void insertarInicio(Nodo*& head) {
    Nodo* nuevo = new Nodo(); //Uso de memoria dinámica
    cout << "Ingrese Carne: "; getline(cin, nuevo->carne);
    cout << "Ingrese Nombre: "; getline(cin, nuevo->nombre);
    cout << "Ingrese Apellido: "; getline(cin, nuevo->apellido);
    cout << "Ingrese Carrera: "; getline(cin, nuevo->carrera);

    nuevo->siguiente = head; // Enlazar al inicio
    head = nuevo;
    cout << "Estudiante insertado con exito." << endl;
}

// 2. Insertar al final
//Recorre la lista hasta encontrar el ultimo nodo y enlaza el nuevo elemento
void insertarFinal(Nodo*& head) {
    Nodo* nuevo = new Nodo();
    cout << "Ingrese Carne: "; getline(cin, nuevo->carne);
    cout << "Ingrese Nombre: "; getline(cin, nuevo->nombre);
    cout << "Ingrese Apellido: "; getline(cin, nuevo->apellido);
    cout << "Ingrese Carrera: "; getline(cin, nuevo->carrera);
    nuevo->siguiente = NULL;

    if (head == NULL) {
        head = nuevo;
    } else {
        Nodo* actual = head; // Puntero auxiliar
        // Recorrer hasta el ultimo nodo
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;//Enlace del ultimo nodo actual con el nuevo nodo
    }
    cout << "Estudiante insertado con exito." << endl;
}

// 3. Mostrar todos
//Recorre la lista secuencialmente para imprimir la información
void mostrarEstudiantes(Nodo* head) {
    if (head == NULL) {
        cout << "La lista esta vacia." << endl;
        return;
    }
    //Puntero auxiliar para recorrer los nodos uno a uno
    Nodo* actual = head;
    while (actual != NULL) {
        cout << "\nCarne: " << actual->carne << endl;
        cout << "Nombre: " << actual->nombre << endl;
        cout << "Apellido: " << actual->apellido << endl;
        cout << "Carrera: " << actual->carrera << endl;
        cout << "-----------------------------" << endl;
        actual = actual->siguiente;
    }
}

// 4. Buscar por carné
void buscarEstudiante(Nodo* head) {
    string busqueda;
    cout << "Ingrese carne completo a buscar: ";
    getline(cin, busqueda);

    Nodo* actual = head;
    while (actual != NULL) {
        if (actual->carne == busqueda) {
            cout << "\nEstudiante encontrado:" << endl;
            cout << "Nombre: " << actual->nombre << endl;
            cout << "Apellido: " << actual->apellido << endl;
            cout << "Carrera: " << actual->carrera << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Estudiante no encontrado." << endl;
}

// 5. Eliminar por carné
//Ajusta los punteros para saltarlo y borrarlo
void eliminarEstudiante(Nodo*& head) {
    if (head == NULL) {
        cout << "La lista esta vacia." << endl;
        return;
    }
    string busqueda;
    cout << "Ingrese el carne del estudiante a eliminar: ";
    getline(cin, busqueda);

    Nodo* actual = head;
    Nodo* anterior = NULL;//Para reconectar la lista
    //Busqueda del nodo a eliminar manteniendo referencia al anterior
    while (actual != NULL && actual->carne != busqueda) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        cout << "Estudiante no encontrado." << endl;
        return;
    }
    // Ajuste de punteros
    if (anterior == NULL) { // Es el primer nodo
        head = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    delete actual;// Liberar memoria dinámica
    cout << "Registro eliminado exitosamente." << endl;
}
