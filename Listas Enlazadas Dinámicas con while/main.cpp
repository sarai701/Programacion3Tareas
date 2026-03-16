//Priscila Guzmán 9941-23-450
#include <iostream>
#include <iomanip>

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

int main() {
    // Variables de control de la lista
    Nodo* head = NULL;
    Nodo* ultimo = NULL;

    // Variables para datos y cálculos
    int valor;
    char opcion = 's';
    int contador = 0;
    float suma = 0;

    cout << "Estudiante:Priscila Sarai Guzmán Calgua" << endl << endl;

    while(opcion == 's' || opcion == 'S') {
        cout << "Ingrese un número: ";
        cin >> valor;

        //Crear el nodo dinámicamente
        Nodo* nuevo = new Nodo();
        nuevo->dato = valor;
        nuevo->siguiente = NULL;

        //Insertar el nodo en la lista
        if (head == NULL) {
            // Si la lista está vacía, el nuevo nodo es la cabeza
            head = nuevo;
            ultimo = nuevo;
        } else {
            // Si no está vacía, lo conectamos al final del último nodo
            ultimo->siguiente = nuevo;
            ultimo = nuevo; // El nuevo ahora es el último
        }

        contador++;
        suma += valor;

        cout << "Desea ingresar otro número? (s/n): ";
        cin >> opcion;
        cout << endl;
    }

    //Recorrer la lista para mostrar los datos
    cout << "Lista generada:" << endl;
    Nodo* actual = head;
    while (actual != NULL) {
        cout << actual->dato << " -> ";
        actual = actual->siguiente;
    }
    cout << "NULL" << endl << endl;

    if (contador > 0) {

        cout << "Cantidad de nodos: " << contador << endl;
        cout << "Suma de valores: " << suma << endl;
        cout << "Promedio: " << fixed << setprecision(2) << (suma / contador) << endl;
    }

    return 0;
}
