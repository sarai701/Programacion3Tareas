Priscila Sarai Guzmán Calgua
9941-23-450
Programación III Sección B

El programa demuestra el uso de memoria dinámica en C++ mediante la creación de una lista simplemente enlazada de productos.
Funcionamiento:
1. Estructuras: Se define un struct Producto para los datos y un struct Nodo para la autorreferencia.
2. Memoria Dinámica: Se utilizan 4 nodos creados con el operador new.
3. Interacción: El usuario ingresa código, nombre y precio para cada producto.
4. El programa recorre la lista una vez para imprimir los datos y acumular el precio total.
5.Gestión de Memoria: Se aplica el operador delete nodo por nodo para evitar fugas de memoria (Memory Leaks), siguiendo las reglas con punteros.
Pero se uso temp para borrar, porque el delete actual si lo usamos antes de movernos al siguiente, el programa perdería la dirección de memoria del resto de la lista (Memory Leak) o daría un error de sistema.