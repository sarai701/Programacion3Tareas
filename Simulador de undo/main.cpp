//Priscila Sarai Guzmán Calgua
//Carné 9941-23-450
#include <iostream>
#include <string>

using namespace std;

struct Nodo {
    string accion;//Dato que almacena la acción
    Nodo* siguiente;//Puntero que conecta con el nodo de abajo
};

//Funciones de pila
//Inserta un nuevo elemento al inicio de la pila (LIFO)
void push(Nodo*& tope, string valor) {
    Nodo* nuevoNodo = new Nodo();//Reservar memoria en el HEAP
    nuevoNodo->accion = valor;//Asigna el valor
    nuevoNodo->siguiente = tope;//Apuntar al antiguo tope
    tope = nuevoNodo;//Actualizar el tope de la pila
}

//Extrae el elemento superior y libera la memoria
string pop(Nodo*& tope) {
    if (tope == nullptr) return "";//Pila vacia

    Nodo* temporal = tope;
    string valor = temporal->accion;
    tope = tope->siguiente;
    delete temporal;
    return valor;
}

//Recorre la pila desde el tope hasta el fondo para mostrar datos
void mostrarPila(Nodo* tope, string nombrePila) {
    cout << "\n--- " << nombrePila << " ---" << endl;
    if (tope == nullptr) {
        cout << "[ Pila vacia ]" << endl;
        return;
    }

    Nodo* actual = tope;
    while (actual != nullptr) {
        cout << " -> " << actual->accion << endl;
        actual = actual->siguiente;
    }
}

//Vacía la pila completamente y libera memoria de todos los nodos
void limpiarPila(Nodo*& tope) {
    while (tope != nullptr) {
        pop(tope);//Reutilizar pop para eliminar uno a uno
    }
}

int main() {
    //Inicialización de pilas vacías
    Nodo* pilaAcciones = nullptr;
    Nodo* pilaRehacer = nullptr;
    int opcion;
    string nuevaAccion;

    cout << "========================================" << endl;
    cout << "   SIMULADOR UNDO/REDO - Priscila Guzman   " << endl;
    cout << "        Carne: 9941-23-450               " << endl;
    cout << "========================================" << endl;

    do {
        cout << "\n1. Realizar accion" << endl;
        cout << "2. Deshacer (Undo)" << endl;
        cout << "3. Rehacer (Redo)" << endl;
        cout << "4. Ver historial de acciones" << endl;
        cout << "5. Ver pila de rehacer" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Escriba la accion: ";
                getline(cin, nuevaAccion);
                push(pilaAcciones, nuevaAccion);
                //Si se hace algo nuevo, ya no se puede rehacer lo anterior
                limpiarPila(pilaRehacer);
                cout << ">> Accion guardada." << endl;
                break;

            case 2: //UNDO: De Pila Principal a Pila Rehacer
                if (pilaAcciones != nullptr) {
                    string deshecho = pop(pilaAcciones);
                    push(pilaRehacer, deshecho);
                    cout << ">> Se deshizo: " << deshecho << endl;
                } else {
                    cout << "!! Error: No hay acciones para deshacer." << endl;
                }
                break;

            case 3: //REDO: De Pila Rehacer a Pila Principal
                if (pilaRehacer != nullptr) {
                    string rehecho = pop(pilaRehacer);
                    push(pilaAcciones, rehecho);
                    cout << ">> Se rehizo: " << rehecho << endl;
                } else {
                    cout << "!! Error: No hay nada para rehacer." << endl;
                }
                break;

            case 4:
                mostrarPila(pilaAcciones, "HISTORIAL DE ACCIONES");
                break;

            case 5:
                mostrarPila(pilaRehacer, "PILA DE REHACER");
                break;

            case 6:
                cout << "Saliendo y liberando memoria..." << endl;
                limpiarPila(pilaAcciones);
                limpiarPila(pilaRehacer);
                break;

            default:
                cout << "!! Opcion invalida." << endl;
        }
    } while (opcion != 6);

    return 0;
}
