//Priscila Guzmán 9941-23-450
#include <iostream>
#include <string>

using namespace std;

// Estructuras de datos

// Nodo estándar para estructuras lineales (Pila, Cola, Lista Simple)
struct Nodo {
    int dato;
    Nodo* siguiente; // Puntero al siguiente elemento
};

// Nodo para Lista Doblemente Enlazada (Historial)
// Permite navegación en ambas direcciones: adelante y atrás
struct NodoDoble {
    int dato;
    string tipo; // Almacena el nombre de la estructura original
    int orden;   // Registro del orden cronológico de ingreso
    NodoDoble* siguiente;
    NodoDoble* anterior;
};

// Nodo para Árbol
struct NodoArbol {
    int dato;
    NodoArbol* izquierdo; //Menores
    NodoArbol* derecho;   //Mayores
};

// Punteros globales
// Se inicializan en NULL para indicar que las estructuras están vacías
Nodo* pila = NULL;// Estructura LIFO para impares positivos
Nodo* colaFrente = NULL; // Inicio de FIFO para pares positivos
Nodo* colaFinal = NULL; // Final de la Cola para inserciones rápidas
Nodo* listaNegativos = NULL; // Lista simple para valores menores a 0
NodoDoble* historialInicio = NULL;
NodoDoble* historialFin = NULL;
NodoArbol* raizBST = NULL;

// Variables de control estadístico
int paresPos = 0, imparesPos = 0, negativosCount = 0, cerosRechazados = 0;
int totalValidos = 0, mayorVal = -99999, menorVal = 99999;
int contadorOrden = 1; // Contador para el historial

// Funciones de insercción
void pushPila(int valor) {
    Nodo* nuevo = new Nodo(); // Asignación de memoria dinámica
    nuevo->dato = valor;
    nuevo->siguiente = pila; // El nuevo nodo apunta al antiguo tope
    pila = nuevo;            // El tope ahora es el nuevo nodo
}

void enqueueCola(int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    if (colaFrente == NULL) { // Si la cola está vacía
        colaFrente = nuevo;
    } else {
        colaFinal->siguiente = nuevo; // Enlace al final de la fila
    }
    colaFinal = nuevo; // Actualización del puntero final
}

// Lista Simple: Inserción al inicio para optimizar tiempo O(1)
void insertarEnLista(Nodo*& cabeza, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

// Lista Doble (Historial): Mantiene el registro de todos los movimientos
void registrarHistorial(int valor, string tipo) {
    NodoDoble* nuevo = new NodoDoble();
    nuevo->dato = valor;
    nuevo->tipo = tipo;
    nuevo->orden = contadorOrden++;
    nuevo->siguiente = NULL;
    nuevo->anterior = historialFin; // Enlace al nodo previo

    if (historialInicio == NULL) {
        historialInicio = nuevo;
    } else {
        historialFin->siguiente = nuevo;
    }
    historialFin = nuevo;
}

// Funciones del árbol
NodoArbol* insertarBST(NodoArbol* raiz, int valor) {
    if (raiz == NULL) {
        NodoArbol* nuevo = new NodoArbol();
        nuevo->dato = valor;
        nuevo->izquierdo = nuevo->derecho = NULL;
        return nuevo;
    }
    if (valor < raiz->dato)
        raiz->izquierdo = insertarBST(raiz->izquierdo, valor);
    else if (valor > raiz->dato)
        raiz->derecho = insertarBST(raiz->derecho, valor);
    return raiz;
}

bool buscarEnBST(NodoArbol* raiz, int valor) {
    if (raiz == NULL) return false;
    if (raiz->dato == valor) return true;
    if (valor < raiz->dato) return buscarEnBST(raiz->izquierdo, valor);
    return buscarEnBST(raiz->derecho, valor);
}

// Recorridos
void inOrden(NodoArbol* raiz) { if(raiz){ inOrden(raiz->izquierdo); cout<<raiz->dato<<" "; inOrden(raiz->derecho); } }
void preOrden(NodoArbol* raiz) { if(raiz){ cout<<raiz->dato<<" "; preOrden(raiz->izquierdo); preOrden(raiz->derecho); } }
void postOrden(NodoArbol* raiz) { if(raiz){ postOrden(raiz->izquierdo); postOrden(raiz->derecho); cout<<raiz->dato<<" "; } }

void mostrarLista(Nodo* cabeza, string nombre) {
    if (cabeza == NULL) { cout << "\n[!] La lista de " << nombre << " esta vacia." << endl; return; }
    cout << "\n--- " << nombre << " ---" << endl;
    Nodo* temp = cabeza;
    while (temp) {
        cout << "[" << temp->dato << "] -> ";
        temp = temp->siguiente;
    }
    cout << "NULL" << endl;
}

// Vacía las estructuras dinámicas para transferir los datos a listas auxiliares
void reorganizar() {
    Nodo* auxPila = NULL;
    Nodo* auxCola = NULL;

    if (pila == NULL && colaFrente == NULL) {
        cout << "\nNo hay datos para reorganizar." << endl;
        return;
    }

    // Proceso de vaciado de Pila
    while (pila != NULL) {
        insertarEnLista(auxPila, pila->dato);
        Nodo* temp = pila;
        pila = pila->siguiente;
        delete temp; // Liberación de memoria del nodo original
    }
    mostrarLista(auxPila, "LISTA AUXILIAR 1 (EX-PILA)");

    // Proceso de vaciado de Cola
    while (colaFrente != NULL) {
        insertarEnLista(auxCola, colaFrente->dato);
        Nodo* temp = colaFrente;
        colaFrente = colaFrente->siguiente;
        if (colaFrente == NULL) colaFinal = NULL;
        delete temp; // Liberación de memoria
    }
    mostrarLista(auxCola, "LISTA AUXILIAR 2 (EX-COLA)");

    Nodo* reco = auxPila;
    while(reco){ raizBST = insertarBST(raizBST, reco->dato); reco = reco->siguiente; }
    reco = auxCola;
    while(reco){ raizBST = insertarBST(raizBST, reco->dato); reco = reco->siguiente; }

    cout << "\nEstructuras reorganizadas y BST actualizado." << endl;
}

void eliminarNegativos() {
    Nodo* actual = listaNegativos;
    Nodo* anterior = NULL;
    int eliminados = 0;
    while (actual) {
        if (actual->dato > -10) {
            Nodo* borrar = actual;
            if (anterior == NULL) listaNegativos = actual->siguiente;
            else anterior->siguiente = actual->siguiente;
            actual = actual->siguiente;
            delete borrar;
            eliminados++;
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
    cout << "\nNodos eliminados: " << eliminados << endl;
}

int main() {
    int opcion, n, num;

    do {
        cout << "\n========================================";
        cout << "\n PARCIAL II- PRISCILA GUZMAN 9941-23-450";
        cout << "\n========================================";
        cout << "\n1. Ingresar N numeros";
        cout << "\n2. Mostrar Pila (Impares +)";
        cout << "\n3. Mostrar Cola (Pares +)";
        cout << "\n4. Mostrar Lista de Negativos";
        cout << "\n5. Mostrar Historial (Lista Doble)";
        cout << "\n6. Construir y Mostrar BST";
        cout << "\n7. Eliminar negativos (Magnitud < 10)";
        cout << "\n8. Buscar valor en BST";
        cout << "\n9. Mostrar Estadisticas";
        cout << "\n10. Reorganizar estructuras";
        cout << "\n11. Salir";
        cout << "\nSeleccione opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingrese N numeros a insertar: "; cin >> n;
                for(int i = 0; i < n; i++) {
                    cout << "Ingrese valor: "; cin >> num;
                    if(num == 0) cerosRechazados++;
                    else {
                        totalValidos++;
                        if(num > mayorVal) mayorVal = num;
                        if(num < menorVal) menorVal = num;
                        if(num > 0) {
                            if(num % 2 == 0) {
                                enqueueCola(num);
                                registrarHistorial(num, "COLA");
                                paresPos++;
                            } else {
                                pushPila(num);
                                registrarHistorial(num, "PILA");
                                imparesPos++;
                            }
                        } else {
                            insertarEnLista(listaNegativos, num);
                            registrarHistorial(num, "LISTA SIMPLE");
                            negativosCount++;
                        }
                    }
                }
                break;
            case 2: mostrarLista(pila, "PILA"); break;
            case 3: mostrarLista(colaFrente, "COLA"); break;
            case 4: mostrarLista(listaNegativos, "LISTA DE NEGATIVOS"); break;
            case 5: // Visualización del historial (Lista Doble)
                {
                    NodoDoble* t = historialInicio;
                    if(!t) cout << "Historial vacio.";
                    while(t){
                        cout << t->orden << ": " << t->dato << " -> " << t->tipo << endl;
                        t = t->siguiente;
                    }
                }
                break;
            case 6: // Construcción del árbol
                raizBST = NULL;
                {
                    NodoDoble* t = historialInicio;
                    while(t){
                        if(t->dato > 0) raizBST = insertarBST(raizBST, t->dato);
                        t = t->siguiente;
                    }
                }
                cout << "\nInOrden: "; inOrden(raizBST);
                cout << "\nPreOrden: "; preOrden(raizBST);
                cout << "\nPostOrden: "; postOrden(raizBST);
                cout << endl;
                break;
            case 7: eliminarNegativos(); break;
            case 8:
                cout << "Valor a buscar: "; cin >> num;
                if(buscarEnBST(raizBST, num)) cout << "Valor encontrado.";
                else cout << "Valor no existe.";
                break;
            case 9:
                cout << "\n--- ESTADISTICAS ---";
                cout << "\nPares(+): " << paresPos << "\nImpares(+): " << imparesPos << "\nNegativos: " << negativosCount;
                cout << "\nCeros: " << cerosRechazados << "\nTotal validos: " << totalValidos;
                cout << "\nMayor: " << mayorVal << "\nMenor: " << menorVal << endl;
                break;
            case 10: reorganizar(); break;
        }
    } while(opcion != 11);

    return 0;
}
