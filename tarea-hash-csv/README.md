Priscila Guzmán 9941-23-450
Tablas Hash en C++ y en Java

1. Implementación en C++: diseñada de forma modular y manual utilizando un arreglo estático de punteros (buckets) y resolución de colisiones mediante encadenamiento separado (Separate Chaining) con listas enlazadas simples.
2. Implementación en Java: diseñada utilizando las herramientas nativas del lenguaje mediante la clase HashMap, analizando el comportamiento de las estructuras.

Instrucciones de ejecución y pruebas

Implementación en C++ (Code::Blocks)

La versión en C++ utiliza una tabla hash manual con manejo de archivos estructurado de forma modular.

Lectura del CSV:
   - El programa abre el archivo csv línea por línea.
   - Utiliza std::getline combinando delimitadores (comas) para separar los atributos de cada estudiante student_id  y limpiar los saltos de línea.

Direccionamiento Hash Manual:
   - Al recibir el student_id se procesa a través de una función hash.
   - Este resultado numérico determina el bucket exacto en el arreglo estático donde se intentará guardar al estudiante.

Manejo de Colisiones por Separate Chaining:
   - Si el bucket asignado está vacío, el estudiante se almacena como el nodo cabeza de esa posición.
   - Si el bucket ya contiene datos (Colisión), el programa crea un nuevo nodo dinámico y lo enlaza al inicio de la lista Node incrementando inmediatamente el contador global de total_collisions.

Monitoreo de Rendimiento:
   - Cada inserción actualiza el cálculo del factor de carga (\alpha), el cual mide la saturación de la tabla

Implementación en Java

Ubicación del CSV: Coloca el archivo csv en la raíz del proyecto de Java.
El programa solicita la clave al usuario y ejecuta mapa.containsKey(idBusca). Internamente, Java calcula el código hash del entero, localiza la cubeta (bucket) correspondiente de manera directa en memoria y recupera el objeto con mapa.get(idBusca) en un tiempo promedio constante O(1). Finalmente, el método sobreescrito .toString() se encarga de formatear la salida en pantalla de forma limpia.
Al ingresar una clave válida, se invoca mapa.remove(idBorra). El mapa rompe el enlace interno eliminando la correspondencia clave-valor y liberando ese espacio. Inmediatamente después, se actualiza el contador global llamando a mapa.size() para mostrar en tiempo real cuántos registros quedan activos en el sistema.

  