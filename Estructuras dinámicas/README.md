Priscila Guzmán 9941-23-450
Estructuras dinámicas 
Este programa es una solución integral desarrollada en C++ que utiliza estructuras de datos dinámicas para la clasificación y gestión de números enteros. El sistema permite al usuario ingresar una serie de números y los distribuye automáticamente en pilas, colas o listas enlazadas basándose en la lógica de su valor.
El sistema funciona ingresando cada número de la siguiente manera:
- Pares se insertan en una cola (FIFO).
- Impares se insertan en una pila (LIFO).
- Negativos se insertan en una lista enlazada.
El ingreso de datos finaliza cuando el usuario escribe -1.
- Memoria Dinámica: Uso estricto de new y delete para evitar memory leaks.
- Estructuras: Implementación manual de Nodos sin usar librerías externas de contenedores (como <list> o <stack>).
- Validaciones:Control de punteros nulos y manejo de estructuras vacías.
- Modularidad: Funciones separadas para cada operación (push, pop, enqueue, dequeue, etc.).
  
