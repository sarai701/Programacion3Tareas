//Priscila Sarai Guzmán Calgua 9941-23-450
Proyecto Final – Red Social Académica con Estructuras de Datos
Descripción del Proyecto: Este proyecto consiste en el desarrollo de una Red Social Académica utilizando estructuras de datos implementadas manualmente en C++ y un benchmark comparativo desarrollado en Java utilizando las estructuras nativas del framework.
El sistema permite administrar estudiantes universitarios, sus proyectos académicos, conexiones sociales y rankings académicos.

Contiene el sistema principal desarrollado en C++.

Estructuras implementadas:

* Tabla Hash con Separate Chaining
* Árbol AVL
* Grafo No Dirigido
* Lista Enlazada de Proyectos
* Pila de Historial de Acciones

Archivos principales:

* Student.h
* HashTable.h
* AVL.h
* Graph.h
* CSVReader.h
* ActionStack.h
* Benchmark.h
* main.cpp

java-benchmark: Contiene el benchmark comparativo utilizando estructuras nativas de Java.
Estructuras utilizadas:
* HashMap
* TreeMap
* Grafo basado en HashMap + List
* BFS
Archivos:
* Estudiante.java
* BenchmarkMain.java

dataset:

Contiene el archivo:

* estudiantes.csv

Utilizado para cargar los registros académicos.

Evidencias

Contiene:

* Documento PDF de evidencias
* Capturas de funcionamiento
* Resultados de benchmark
* Comparación C++ vs Java

Funcionalidades Implementadas
Gestión de Estudiantes
* Carga masiva desde CSV
* Registro manual
* Búsqueda por ID
* Eliminación en cascada

Gestión de Proyectos
* Agregar proyecto
* Buscar proyecto
* Mostrar proyectos
* Eliminar proyecto

Grafo 
* Conectar estudiantes
* Verificar conexiones
* Mostrar conexiones
* BFS
* DFS

Ranking Académico
* Inserción AVL
* Ranking ordenado
* Altura del árbol

Estadísticas
* Total de estudiantes
* Total de proyectos
* Total de conexiones
* Colisiones Hash
* Factor de carga
* Altura AVL
* Tiempo de carga del dataset

Funcionalidad Avanzada: ruta más corta entre estudiantes utilizando BFS.

Benchmark C++
Genera automáticamente:
cpp_results.csv
Operaciones medidas:
* Inserción Hash
* Búsqueda Hash
* Inserción AVL
* Recorrido AVL
* BFS
* DFS

Benchmark Java
Genera automáticamente:
java_results.csv
Estructuras comparadas:
* HashMap
* TreeMap
* Grafo basado en colecciones nativas

Operaciones medidas:
* Inserción
* Búsqueda
* Recorridos

Conclusiones

El proyecto demuestra la implementación manual de estructuras de datos avanzadas en C++ y permite comparar su rendimiento con las estructuras optimizadas del framework de Java.

La comparación evidencia diferencias de rendimiento, facilidad de implementación y nivel de abstracción entre ambos lenguajes.
