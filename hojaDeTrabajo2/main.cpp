//Priscila Guzmán 9941-23-450
//Programación III
//Semana IV-laboratorio producto
#include <iostream>
#include <string>

using namespace std;

//Paso1: definir las estructuras
struct Producto {
    int codigo;
    string nombre;
    double precio;
};

struct Nodo {
    Producto data;
    Nodo* siguiente; //Puntero
};

int main() {
    //Paso2: primer nodo
    Nodo* primero = new Nodo;
    primero->data.codigo = 101;
    primero->data.nombre = "Laptop";
    primero->data.precio = 5500.50;
    primero->siguiente = nullptr;

    //Paso3: segundo nodo
    Nodo* segundo = new Nodo;
    segundo->data.codigo = 102;
    segundo->data.nombre = "Mouse";
    segundo->data.precio = 150.75;
    segundo->siguiente = nullptr;

    //Se enlazan el nodo 1 al nodo 2
    primero->siguiente = segundo;

    //Paso4: tercer nodo
    Nodo* tercero = new Nodo;
    tercero->data.codigo = 103;
    tercero->data.nombre = "Teclado";
    tercero->data.precio = 300.00;
    tercero->siguiente = nullptr;

    //Se enlaza el nodo 2 al nodo 3
    segundo->siguiente = tercero;

    //Paso5: recorre e imprime lista
    //Se usa el puntero auxiliar que es actual
    Nodo* actual = primero;

    cout << "--- LISTA DE PRODUCTOS ---" << endl;
    while (actual != nullptr) {
        cout << "Codigo: " << actual->data.codigo << endl;
        cout << "Nombre: " << actual->data.nombre << endl;
        cout << "Precio: Q" << actual->data.precio << endl;
        cout << "--------------------------" << endl;

        actual = actual->siguiente; //Avanza al siguiente nodo
    }

    //Paso6: liberar memoria
    Nodo* actual = primero; //Se reinicia el puntero auxiliar al inicio de la lista
    while (actual != nullptr) {
        Nodo* temp = actual; //Se guarda el nodo actual
        actual = actual->siguiente;
        delete temp; //Se libera la memoria del nodo guardado
    }

    primero = nullptr; //Se evitan punteros colgantes
    cout << "Memoria liberada exitosamente." << endl;

    return 0;
}
