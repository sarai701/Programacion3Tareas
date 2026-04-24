//Priscila Guzmán 9941-23-450
#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;
};

// Punteros de control global para la versión mejorada
Nodo* head = NULL;
Nodo* tail = NULL;

void insertarInicio(int valor) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = valor;
    nuevo->siguiente = head;
    nuevo->anterior = NULL;

    if (head != NULL) {
        head->anterior = nuevo;
    } else {
        tail = nuevo; // Si la lista estaba vacía, el nuevo es también el final
    }
    head = nuevo;
}

void insertarFinal(int valor) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    nuevo->anterior = tail; // Se conecta al actual tail

    if (tail != NULL) {
        tail->siguiente = nuevo;
    } else {
        head = nuevo; // Si estaba vacía, es el primero
    }
    tail = nuevo; // El nuevo nodo es ahora el tail
}

void mostrarAdelante() {
    if (head == NULL) { cout << "Lista vacia.\n"; return; }
    Nodo* temp = head;
    cout << "Lista (Head -> Tail): ";
    while (temp != NULL) {
        cout << "[" << temp->dato << "] <-> ";
        temp = temp->siguiente;
    }
    cout << "NULL" << endl;
}

void mostrarAtras() {
    if (tail == NULL) { cout << "Lista vacia.\n"; return; }
    Nodo* temp = tail; // Acceso directo al final gracias al puntero tail
    cout << "Lista (Tail -> Head): ";
    while (temp != NULL) {
        cout << "[" << temp->dato << "] <-> ";
        temp = temp->anterior;
    }
    cout << "NULL" << endl;
}

bool buscar(int valor) {
    Nodo* temp = head;
    while (temp != NULL) {
        if (temp->dato == valor) return true;
        temp = temp->siguiente;
    }
    return false;
}

void eliminar(int valor) {
    if (head == NULL) return;
    Nodo* actual = head;

    while (actual != NULL && actual->dato != valor) {
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        cout << "Valor " << valor << " no encontrado.\n";
        return;
    }

    // Ajuste de punteros
    if (actual->anterior != NULL)
        actual->anterior->siguiente = actual->siguiente;
    else
        head = actual->siguiente; // Era el head

    if (actual->siguiente != NULL)
        actual->siguiente->anterior = actual->anterior;
    else
        tail = actual->anterior; //Era el tail, actualizamos el puntero final

    delete actual;
    cout << "Nodo con valor " << valor << " eliminado correctamente.\n";
}

int contarNodos() {
    int contador = 0;
    Nodo* temp = head;
    while (temp != NULL) {
        contador++;
        temp = temp->siguiente;
    }
    return contador;
}

void liberarMemoria() {
    while (head != NULL) {
        Nodo* temp = head;
        head = head->siguiente;
        delete temp;
    }
    tail = NULL;
    cout << "Memoria liberada.\n";
}

int main() {
    int opcion, valor;
    string miNombre = "Priscila Guzmán 9941-23-450";

    do {
        cout << "\n========================================";
        cout << "\n   LISTA DOBLE CON TAIL - " << miNombre;
        cout << "\n========================================";
        cout << "\n1. Insertar al Inicio";
        cout << "\n2. Insertar al Final";
        cout << "\n3. Mostrar hacia Adelante";
        cout << "\n4. Mostrar hacia Atras";
        cout << "\n5. Buscar Valor";
        cout << "\n6. Eliminar Valor";
        cout << "\n7. Contar Nodos";
        cout << "\n8. Salir";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Valor: "; cin >> valor;
                insertarInicio(valor);
                break;
            case 2:
                cout << "Valor: "; cin >> valor;
                insertarFinal(valor);
                break;
            case 3: mostrarAdelante(); break;
            case 4: mostrarAtras(); break;
            case 5:
                cout << "Valor a buscar: "; cin >> valor;
                if(buscar(valor)) cout << "Resultado: El valor existe.\n";
                else cout << "Resultado: El valor NO existe.\n";
                break;
            case 6:
                cout << "Valor a eliminar: "; cin >> valor;
                eliminar(valor);
                break;
            case 7:
                cout << "Total de nodos: " << contarNodos() << endl;
                break;
            case 8:
                liberarMemoria();
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 8);

    return 0;
}
