//Priscila Guzmán
//Carné 9941-23-450
#include <iostream>
#include <limits>

using namespace std;

//Estructura base para los nodos
struct Nodo {
    int dato;
    Nodo* siguiente;
};

//Prototipos de funcioes
void push(Nodo*& pila, int n);
void pop(Nodo*& pila);
void enqueue(Nodo*& frente, Nodo*& fin, int n);
void dequeue(Nodo*& frente, Nodo*& fin);
void insertarLista(Nodo*& lista, int n);
void mostrarEstructura(Nodo* frente, string nombre);
void liberarMemoria(Nodo*& inicio);
void menu();

//Variables globales para estadísticas
int cantPares = 0, cantImpares = 0, cantNegativos = 0;

int main() {
    Nodo* pilaImpares = nullptr;
    Nodo* frenteColaPares = nullptr;
    Nodo* finColaPares = nullptr;
    Nodo* listaNegativos = nullptr;

    int opcion, numero;

    do {
        menu();
        while (!(cin >> opcion)) { //Validación de entrada no numérica
            cout << "Error: Ingrese una opcion valida: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (opcion) {
            case 1:
                cout << "Ingrese numeros (finalice con -1):" << endl;
                while (true) {
                    cout << " -> ";
                    if (!(cin >> numero)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    if (numero == -1) break;

                    if (numero < 0) {
                        insertarLista(listaNegativos, numero);
                        cantNegativos++;
                    } else if (numero % 2 == 0) {
                        enqueue(frenteColaPares, finColaPares, numero);
                        cantPares++;
                    } else {
                        push(pilaImpares, numero);
                        cantImpares++;
                    }
                }
                break;
            case 2: mostrarEstructura(pilaImpares, "Pila (Impares)"); break;
            case 3: mostrarEstructura(frenteColaPares, "Cola (Pares)"); break;
            case 4: mostrarEstructura(listaNegativos, "Lista (Negativos)"); break;
            case 5: pop(pilaImpares); break;
            case 6: dequeue(frenteColaPares, finColaPares); break;
            case 7:
                cout << "\n--- ESTADISTICAS FINALES ---" << endl;
                cout << "Pares: " << cantPares << " | Impares: " << cantImpares << " | Negativos: " << cantNegativos << endl;
                liberarMemoria(pilaImpares);
                liberarMemoria(frenteColaPares);
                liberarMemoria(listaNegativos);
                cout << "Memoria liberada. Saliendo..." << endl;
                break;
            default: cout << "Opcion no valida." << endl;
        }
    } while (opcion != 7);

    return 0;
}

//Funciones

void menu() {
    cout << "\n================================================" << endl;
    cout << "  Priscila Sarai Guzmán Calgua" << endl;
    cout << "  9941-23-450" << endl;
    cout << "================================================" << endl;
    cout << "\n======= SISTEMA DE ESTRUCTURAS DINAMICAS =======" << endl;
    cout << "1. Ingresar numeros" << endl;
    cout << "2. Mostrar Pila (Impares)" << endl;
    cout << "3. Mostrar Cola (Pares)" << endl;
    cout << "4. Mostrar Lista (Negativos)" << endl;
    cout << "5. Eliminar de Pila (Pop)" << endl;
    cout << "6. Eliminar de Cola (Dequeue)" << endl;
    cout << "7. Salir" << endl;
    cout << "Seleccione: ";
}

//Pila (LIFO)
void push(Nodo*& pila, int n) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = n;
    nuevoNodo->siguiente = pila;
    pila = nuevoNodo;
}

void pop(Nodo*& pila) {
    if (pila == nullptr) {
        cout << "[Error] Pila vacia." << endl;
        return;
    }
    Nodo* aux = pila;
    pila = aux->siguiente;
    delete aux;
    cout << "Elemento eliminado de la pila." << endl;
}

//Cola (FIFO)
void enqueue(Nodo*& frente, Nodo*& fin, int n) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = n;
    nuevoNodo->siguiente = nullptr;
    if (frente == nullptr) frente = nuevoNodo;
    else fin->siguiente = nuevoNodo;
    fin = nuevoNodo;
}

void dequeue(Nodo*& frente, Nodo*& fin) {
    if (frente == nullptr) {
        cout << "[Error] Cola vacia." << endl;
        return;
    }
    Nodo* aux = frente;
    if (frente == fin) {
        frente = nullptr;
        fin = nullptr;
    } else {
        frente = frente->siguiente;
    }
    delete aux;
    cout << "Elemento eliminado de la cola." << endl;
}

void insertarLista(Nodo*& lista, int n) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = n;
    nuevoNodo->siguiente = lista;
    lista = nuevoNodo;
}

void mostrarEstructura(Nodo* frente, string nombre) {
    cout << "\n" << nombre << ": ";
    if (frente == nullptr) {
        cout << "(vacia)";
    } else {
        Nodo* aux = frente;
        while (aux != nullptr) {
            cout << aux->dato << (aux->siguiente ? " -> " : "");
            aux = aux->siguiente;
        }
    }
    cout << endl;
}

//Limpieza de memoria
void liberarMemoria(Nodo*& inicio) {
    while (inicio != nullptr) {
        Nodo* aux = inicio;
        inicio = inicio->siguiente;
        delete aux;
    }
}
