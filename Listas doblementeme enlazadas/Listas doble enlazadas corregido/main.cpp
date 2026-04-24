//Priscila Guzmán 9941-23-450
#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;
};

void insertarInicio(Nodo* &head, int valor) {
    Nodo* nuevo = new Nodo; // Error corregido: No existía struct Nodos
    nuevo->dato = valor;
    nuevo->siguiente = head;
    nuevo->anterior = NULL;

    if (head != NULL) {
        head->anterior = nuevo; // Error corregido: Tenia == y solo tiene que estar =
    }
    head = nuevo;
}

void insertarFinal(Nodo* &head, int valor) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    if (head == NULL) { // Error corregido: Tenia solo = y tiene qeu ser ==
        nuevo->anterior = NULL;
        head = nuevo;
        return;
    }

    Nodo* temp = head;
    while (temp->siguiente != NULL) {
        temp = temp->siguiente;
    }

    temp->siguiente = nuevo;
    nuevo->anterior = temp; // Error corregido: Apuntaba a head, debe ser a temp
}

void mostrarAdelante(Nodo* head) {
    if (head == NULL) {
        cout << "Lista vacia\n";
        return;
    }
    Nodo* temp = head;
    cout << "\nLista hacia adelante: ";
    while (temp != NULL) {
        cout << temp->dato << " <-> ";
        temp = temp->siguiente; // Error corregido: Era temp->anterior
    }
    cout << "NULL\n";
}

void mostrarAtras(Nodo* head) {
    if (head == NULL) {
        cout << "Lista vacia\n";
        return;
    }
    Nodo* temp = head;
    while (temp->siguiente != NULL) { // Error corregido: Recorrer hasta el último
        temp = temp->siguiente;
    }
    cout << "\nLista hacia atras: ";
    while (temp != NULL) {
        cout << temp->dato << " <-> ";
        temp = temp->anterior;
    }
    cout << "NULL\n";
}

bool buscar(Nodo* head, int valor) {
    Nodo* temp = head;
    while (temp != NULL) {
        if (temp->dato == valor) return true; // Error corregido: Solo tenia = y es ==
        temp = temp->siguiente;
    }
    return false;
}

void eliminar(Nodo* &head, int valor) {
    if (head == NULL) return;
    Nodo* actual = head;

    while (actual != NULL && actual->dato != valor) {
        actual = actual->siguiente;
    }

    if (actual == NULL) return;

    if (actual->anterior != NULL)
        actual->anterior->siguiente = actual->siguiente;
    else
        head = actual->siguiente;

    if (actual->siguiente != NULL)
        actual->siguiente->anterior = actual->anterior;

    delete actual;
}

int contarNodos(Nodo* head) {
    int contador = 0; // Error corregido: Iniciaba en 1
    Nodo* temp = head;
    while (temp != NULL) {
        contador++;
        temp = temp->siguiente;
    }
    return contador;
}

void liberarLista(Nodo* &head) {
    while (head != NULL) {
        Nodo* temp = head;
        head = head->siguiente;
        delete temp;
    }
}

int main() {
    Nodo* head = NULL; // Error corregido: Tenia == y es =
    int opcion, valor;
    string nombre = "Priscila Guzmán 9941-23-450";

    do {
        cout << "\n--- ESTUDIANTE: " << nombre << " ---\n";
        cout << "1. Insertar Inicio\n2. Insertar Final\n3. Mostrar Adelante\n";
        cout << "4. Mostrar Atras\n5. Buscar\n6. Eliminar\n7. Contar\n8. Salir\nOpcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: cin >> valor; insertarInicio(head, valor); break;
            case 2: cin >> valor; insertarFinal(head, valor); break;
            case 3: mostrarAdelante(head); break;
            case 4: mostrarAtras(head); break;
            case 5: cin >> valor; cout << (buscar(head, valor) ? "Existe" : "No existe") << endl; break;
            case 6: cin >> valor; eliminar(head, valor); break;
            case 7: cout << "Total: " << contarNodos(head) << endl; break;
        }
    } while (opcion != 8);

    liberarLista(head);
    return 0;
}
