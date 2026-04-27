Priscila Sarai Guzmán Calgua 9941-23-450
Descripción del Programa:
Este programa en C++ es una solución integral para el procesamiento de flujos de números       enteros. El sistema clasifica automáticamente los datos ingresados en diferentes estructuras  de datos dinámicas basándose en reglas lógicas (paridad y signo), permitiendo realizar operaciones avanzadas de búsqueda, eliminación y reorganización estructural de nivel exigente.
Estructuras utilizadas:
1. Pila: Utilizada para almacenar números impares positivos. Implementa LIFO (Last-In, First-Out).
2. Cola: Utilizada para números pares positivos. Implementa una política FIFO (First-In, First-Out) con punteros a inicio y fin para inserciones de tiempo constante O(1).
3. Lista Simple Enlazada: Utilizada para almacenar números negativos. Permite el recorrido secuencial y eliminación de nodos específicos.
4. Lista Doblemente Enlazada: Actúa como el historial general. Cada nodo conoce a su antecesor y sucesor, facilitando el seguimiento del orden de ingreso.
5. Árbol Binario de Búsqueda (BST): Estructura jerárquica para organizar los datos de manera que las búsquedas sean eficientes, manteniendo los menores a la izquierda y los mayores a la derecha.
Explicación de la lógica:
Al ingresar un número, el sistema evalúa:
Si es 0:Se rechaza (contador de ceros).
Si es Positivo Par: Se envía a la Cola.
Si es Positivo Impar: Se envía a la Pila.
Si es Negativo: Se envía a la Lista Simple.

Eliminación (Opción 7)
El programa recorre la lista de negativos y aplica una liberación de memoria dinámica (delete) únicamente a los nodos cuyo valor es mayor a -10 (es decir, magnitudes pequeñas como -1, -2... hasta -9).

Reorganización (Opción 10)
Es la operación más compleja del sistema:
1.  Se realiza un vaciado total de la Pila y la Cola.
2.  Los datos se transfieren a listas simples auxiliares.
3.  Se libera la memoria original para evitar memory leaks.
4.  Se reconstruye el Árbol (BST) utilizando los datos rescatados en las listas auxiliares.

Ejecución
Use la opción 1 para cargar datos (ej. 10, -5, 3, 0, 22).
2. Consulte las opciones 2, 3 y 4 para verificar la clasificación.
3. Use la opción 6 para generar la visualización jerárquica (InOrden, PreOrden, PostOrden).
4. Utilice la opción 10 cuando desee resetear las estructuras lineales y consolidar todo en el Árbol.