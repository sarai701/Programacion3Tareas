Priscila Sarai Guzmán Calgua 9941-23-450
Este proyecto implementa un sistema de gestión de ranking académico utilizando una estructura de datos de Árbol AVL. El sistema permite almacenar perfiles de estudiantes y mantenerlos ordenados automáticamente por su skill_score, garantizando búsquedas y visualizaciones eficientes en todo momento.

Funcionalidades:
- Inserción Balanceada: los nodos se reordenan mediante rotaciones (LL, RR, LR, RL) para mantener una altura mínima.
- Ranking InOrden: despliega a los estudiantes de mayor a menor puntaje.
- Búsqueda: localiza estudiantes por su puntaje exacto en tiempo logarítmico.
- Regla de Desempate: si dos estudiantes poseen el mismo puntaje, el sistema utiliza el student_id como criterio de desempate.
- Estadísticas: visualización de la altura del árbol y el factor de balance de la raíz.

Estructura del Proyecto:
  - main.cpp: interfaz de usuario y menú principal.
  - AVL.h / AVL.cpp: lógica de la estructura balanceada y rotaciones.
  - Student.h: definición de la entidad estudiante y lógica de comparación.

¿Por qué AVL es mejor que un BST normal?

Para un sistema de Ranking Académico, la elección de un Árbol AVL sobre un Árbol Binario de Búsqueda (BST) convencional es crítica por las siguientes razones:

1. Garantía de Rendimiento (O \log n): en un ranking, es común que los datos ingresen de forma semi-ordenada (por ejemplo, los mejores promedios primero). En un BST normal, esto causaría que el árbol se incline hacia un lado, convirtiéndose prácticamente en una lista ligada, lo que eleva el tiempo de búsqueda a O(n). El AVL, al balancearse tras cada inserción, asegura que la altura del árbol sea siempre proporcional al logaritmo de los nodos, manteniendo la eficiencia máxima.

2. Consistencia en el Tiempo de Respuesta: independientemente del orden en que se registren los estudiantes, un AVL nunca se degradará. Aunque el sistema crezca a miles de registros, la visualización del ranking y la búsqueda de perfiles siempre sea instantánea.

3. Optimización de Recursos: al mantener el árbol compacto, se minimizan los niveles que el procesador debe recorrer para encontrar un dato, optimizando el uso de memoria.