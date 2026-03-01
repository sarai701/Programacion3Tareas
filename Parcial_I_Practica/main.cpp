//Priscila Guzmán 9941-23-450
//Programación III Sección B
//Parcial I
#include <iostream>

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

int main() {
    cout << "Nombre: Priscila Sarai Guzmán Calgua" << endl;
    cout << "Carné:9941-23-450" << endl;
    cout << "------------------------------------------" << endl;

    //Los 3 nodos
    Nodo* primero = new Nodo;
    Nodo* segundo = new Nodo;
    Nodo* tercero = new Nodo;

    //Se solicita alusuario el ingresos de los valores de los nodos
    cout << "Ingrese el valor para el Nodo 1: ";
    cin >> primero->dato;

    cout << "Ingrese el valor para el Nodo 2: ";
    cin >> segundo->dato;

    cout << "Ingrese el valor para el Nodo 3: ";
    cin >> tercero->dato;

    //Enlace entre los nodos
    primero->siguiente = segundo;
    segundo->siguiente = tercero;
    tercero->siguiente = nullptr;// Finaliza la lista

    //Muestra valores mediante punteros
    cout << "\n--- Valores en la Lista ---" << endl;
    Nodo* auxiliar = primero; //Puntero auxiliar para el recorrido

    int i = 1;
    while (auxiliar != nullptr) {
        cout << "Nodo " << i << " [Dato: " << auxiliar->dato << "]" << endl;
        auxiliar = auxiliar->siguiente;
        i++;
    }

    //Liberación de memoria
    auxiliar = primero;
    while (auxiliar != nullptr) {
        Nodo* temporal = auxiliar;
        auxiliar = auxiliar->siguiente;
        delete temporal;
    }
    primero = nullptr;

    cout << "\nMemoria liberada exitosamente." << endl;

    return 0;
}
