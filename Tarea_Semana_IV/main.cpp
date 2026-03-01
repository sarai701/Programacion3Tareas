//Priscila Guzmán 9941-23-450
//Programación III
//Tarea III
#include <iostream>
#include <string>

using namespace std;

struct Producto {
    int codigo;
    string nombre;
    double precio;
};

struct Nodo {
    Producto data;
    Nodo* siguiente;
};

int main() {
    cout << "Nombre: Priscila Sarai Guzmán Calgua" << endl;
    cout << "---------------------------------------" << endl << endl;

    //Nodos
    Nodo* primero = new Nodo;
    Nodo* segundo = new Nodo;
    Nodo* tercero = new Nodo;
    Nodo* cuarto = new Nodo;

    //Producto 1
    cout << "Ingrese datos del Producto 1:" << endl;
    cout << "Codigo: "; cin >> primero->data.codigo;
    cout << "Nombre: "; cin.ignore(); getline(cin, primero->data.nombre);
    cout << "Precio: Q"; cin >> primero->data.precio;
    primero->siguiente = segundo; //Enlace del primer al segundo nodo
    cout << "--------------------" << endl;

    //Producto 2
    cout << "Ingrese datos del Producto 2:" << endl;
    cout << "Codigo: "; cin >> segundo->data.codigo;
    cout << "Nombre: "; cin.ignore(); getline(cin, segundo->data.nombre);
    cout << "Precio: Q"; cin >> segundo->data.precio;
    segundo->siguiente = tercero; // Enlace del segundo al tercer nodo
    cout << "--------------------" << endl;

    //Producto 3
    cout << "Ingrese datos del Producto 3:" << endl;
    cout << "Codigo: "; cin >> tercero->data.codigo;
    cout << "Nombre: "; cin.ignore(); getline(cin, tercero->data.nombre);
    cout << "Precio: Q"; cin >> tercero->data.precio;
    tercero->siguiente = cuarto; // Enlace del tercer al cuarto nodo
    cout << "--------------------" << endl;

    //Producto 4
    cout << "Ingrese datos del Producto 4:" << endl;
    cout << "Codigo: "; cin >> cuarto->data.codigo;
    cout << "Nombre: "; cin.ignore(); getline(cin, cuarto->data.nombre);
    cout << "Precio: Q"; cin >> cuarto->data.precio;
    cuarto->siguiente = nullptr;
    cout << "--------------------" << endl;

    Nodo* actual = primero; //Puntero auxiliar
    double totalAcumulado = 0;

    cout << "\n--- Lista de productos ingresados ---" << endl;
    while (actual != nullptr) {
        cout << "Codigo: " << actual->data.codigo << endl;
        cout << "Nombre: " << actual->data.nombre << endl;
        cout << "Precio: Q" << actual->data.precio << endl;
        cout << "--------------------" << endl;

        totalAcumulado += actual->data.precio;
        actual = actual->siguiente;
    }

    cout << "Total: Q" << totalAcumulado << endl;

    //Liberar la memoria
    actual = primero;
    while (actual != nullptr) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp; //Liberar correctamente cada nodo
    }
    primero = nullptr;

    cout << "\nMemoria liberada correctamente." << endl;

    return 0;
}
