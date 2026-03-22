//Priscila Sarai Guzmán Calgua
//9959-23-450
#include <iostream>

using namespace std;

// 1. Definición de la estructura del Nodo
struct Nodo {
    int dato;
    Nodo* siguiente;
};

// Prototipos de funciones
void push(Nodo*&, int);
void pop(Nodo*&);
void peek(Nodo*);
void mostrarPila(Nodo*);
int contarElementos(Nodo*);
void buscarElemento(Nodo*, int);
void vaciarPila(Nodo*&);

int main() {
    Nodo* pila = nullptr;
    int opcion, valor;

    cout << "========================================" << endl;
    cout << "SISTEMA DE ACCIONES RECIENTES " << endl;
    cout << "Estudiante:Priscila Sarai Guzmán Calgua" << endl;
    cout << "========================================" << endl;

    do {
        cout << "\n--- MENU DE OPERACIONES ---" << endl;
        cout << "1. Insertar elemento (Push)" << endl;
        cout << "2. Eliminar tope (Pop)" << endl;
        cout << "3. Ver tope (Peek)" << endl;
        cout << "4. Mostrar toda la pila" << endl;
        cout << "5. Contar elementos" << endl;
        cout << "6. Buscar valor" << endl;
        cout << "7. Vaciar pila" << endl;
        cout << "8. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el valor a insertar: ";
                cin >> valor;
                push(pila, valor);
                break;
            case 2:
                pop(pila);
                break;
            case 3:
                peek(pila);
                break;
            case 4:
                mostrarPila(pila);
                break;
            case 5:
                cout << "Total de elementos: " << contarElementos(pila) << endl;
                break;
            case 6:
                if (pila == nullptr) {
                    cout << "Error: No se puede buscar en una pila vacia." << endl;
                } else {
                    cout << "Ingrese valor a buscar: ";
                    cin >> valor;
                    buscarElemento(pila, valor);
                }
                break;
            case 7:
                vaciarPila(pila);
                break;
            case 8:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 8);

    return 0;
}

//Implementación de Funciones

void push(Nodo*& tope, int n) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = n;
    nuevoNodo->siguiente = tope;
    tope = nuevoNodo;
    cout << "Valor " << n << " agregado correctamente." << endl;
}

void pop(Nodo*& tope) {
    if (tope == nullptr) {
        cout << "Error: La pila esta vacia. No se puede eliminar." << endl;
        return;
    }
    Nodo* aux = tope;
    int v = aux->dato;
    tope = aux->siguiente;
    delete aux;
    cout << "Elemento " << v << " eliminado." << endl;
}

void peek(Nodo* tope) {
    if (tope == nullptr) {
        cout << "La pila esta vacia (No hay tope)." << endl;
    } else {
        cout << "El elemento en el tope es: " << tope->dato << endl;
    }
}

void mostrarPila(Nodo* tope) {
    if (tope == nullptr) {
        cout << "La pila esta vacia." << endl;
        return;
    }
    Nodo* actual = tope;
    cout << "Contenido de la pila (Tope -> Fondo):" << endl;
    while (actual != nullptr) {
        cout << "[" << actual->dato << "]" << endl;
        actual = actual->siguiente;
    }
}

int contarElementos(Nodo* tope) {
    int contador = 0;
    Nodo* actual = tope;
    while (actual != nullptr) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

void buscarElemento(Nodo* tope, int n) {
    Nodo* actual = tope;
    int pos = 1;
    bool encontrado = false;
    while (actual != nullptr) {
        if (actual->dato == n) {
            cout << "Valor " << n << " encontrado en la posicion " << pos << " (desde el tope)." << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
        pos++;
    }
    if (!encontrado) cout << "El valor " << n << " no se encuentra en la pila." << endl;
}

void vaciarPila(Nodo*& tope) {
    if (tope == nullptr) {
        cout << "La pila ya esta vacia." << endl;
        return;
    }
    while (tope != nullptr) {
        pop(tope); // Reutilizamos pop para liberar memoria nodo a nodo
    }
    cout << "Pila vaciada con exito." << endl;
}
