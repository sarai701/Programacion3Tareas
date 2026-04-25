//Priscila Guzmán 9941-23-450
#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;
};

Nodo* crearNodo(int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == NULL) {
        return crearNodo(valor);
    }
    if (valor < raiz->dato) {
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    } else {
        raiz->derecho = insertar(raiz->derecho, valor);
    }
    return raiz;
}

void inOrden(Nodo* raiz) {
    if (raiz != NULL) {
        inOrden(raiz->izquierdo);
        cout << raiz->dato << " ";
        inOrden(raiz->derecho);
    }
}

void preOrden(Nodo* raiz) {
    if (raiz != NULL) {
        cout << raiz->dato << " ";
        preOrden(raiz->izquierdo);
        preOrden(raiz->derecho);
    }
}

void postOrden(Nodo* raiz) {
    if (raiz != NULL) {
        postOrden(raiz->izquierdo);
        postOrden(raiz->derecho);
        cout << raiz->dato << " ";
    }
}

int main() {
    Nodo* raiz = NULL;
    int opcion, valor;

    do {
        cout << "\n---Priscila Guzmán 9941-23-450---";
        cout << "\n--- MENU ---";
        cout << "\n1. Insertar valor";
        cout << "\n2. Mostrar InOrden";
        cout << "\n3. Mostrar PreOrden";
        cout << "\n4. Mostrar PostOrden";
        cout << "\n5. Mostrar todos los recorridos";
        cout << "\n6. Salir";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese valor: ";
                cin >> valor;
                raiz = insertar(raiz, valor);
                cout << "Valor insertado correctamente.\n";
                break;
            case 2:
                if (raiz == NULL) cout << "El arbol esta vacio.";
                else { cout << "InOrden: "; inOrden(raiz); }
                cout << endl;
                break;
            case 3:
                if (raiz == NULL) cout << "El arbol esta vacio.";
                else { cout << "PreOrden: "; preOrden(raiz); }
                cout << endl;
                break;
            case 4:
                if (raiz == NULL) cout << "El arbol esta vacio.";
                else { cout << "PostOrden: "; postOrden(raiz); }
                cout << endl;
                break;
            case 5:
                if (raiz == NULL) cout << "El arbol esta vacio.";
                else {
                    cout << "\nInOrden: "; inOrden(raiz);
                    cout << "\nPreOrden: "; preOrden(raiz);
                    cout << "\nPostOrden: "; postOrden(raiz);
                }
                cout << endl;
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 6);

    return 0;
}
