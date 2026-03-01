Nombre: Priscila Sarai Guzmán Calgua
Carné: 9941-23-450
Curso: Programación III 
Sección: B
Funcionamiento:
El programa utiliza memoria dinámica para gestionar una lista de 3 nodos.
- Se reservan espacios en el Heap usando new.
- Se utilizan punteros para enlazar cada nodo con el siguiente, formando una cadena.
- El recorrido se realiza con un puntero auxiliar para no perder la dirección del primer nodo.
- Se implementa un ciclo de liberación de memoria que utiliza un puntero temporal para borrar cada nodo de forma segura sin romper el enlace hacia el siguiente.