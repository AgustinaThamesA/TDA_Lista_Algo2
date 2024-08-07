<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA LISTA

## Alumno: Agustina Thames Alderete - 111287 - athames@fi.uba.ar

A la hora de correr el programa, yo utilicé la línea para compilar y la línea de ejecución con valgrind, ya que el makefile ya tenía incorporada una forma más eficiente de hacerlo.

- Para compilar:

```bash
touch pruebas_alumno.c
```

- Para ejecutar:

```bash
línea de ejecución
```

- Para ejecutar con valgrind:
```bash
make
```

---

##  Funcionamiento

### Funcionamiento general del programa:
1. **Lista**

- Se implementa una lista enlazada simple. Cada nodo de la lista contiene un puntero al elemento y un puntero al siguiente nodo.
- Se han implementado funciones para insertar elementos al final o en una posición específica, quitar elementos del final o de una posición específica, buscar elementos, obtener el primero y el último elemento, verificar si la lista está vacía, obtener el tamaño de la lista y destruir la lista.
- Para insertar elementos en una posición específica, se busca el nodo en esa posición y se ajustan los punteros para insertar el nuevo nodo en medio de la lista.
- Para quitar elementos de una posición específica, se ajustan los punteros del nodo anterior y del siguiente al nodo a eliminar.
- Se implementa un iterador para recorrer la lista.
  
2. **Pila**
- Se implementa una pila utilizando la lista enlazada implementada anteriormente.
- Se han implementado funciones para crear una pila, apilar elementos, desapilar elementos, obtener el tope de la pila, obtener el tamaño de la pila, verificar si la pila está vacía y destruir la pila.

3. **Cola**
- Se implementa una cola utilizando la lista enlazada implementada anteriormente.
- Se han implementado funciones para crear una cola, encolar elementos, desencolar elementos, obtener el frente de la cola, obtener el tamaño de la cola, verificar si la cola está vacía y destruir la cola.

### Funcionamiento específico del programa:
#### En `lista.c`:

- **`lista_t *lista_crear()`:** Esta función crea una nueva lista vacía. Reserva memoria para la estructura `lista_t` y la inicializa con valores predeterminados, como punteros a `NULL` y tamaño inicial de 0.

- **`lista_t *lista_insertar(lista_t *lista, void *elemento)`:** Inserta un nuevo elemento al final de la lista. Si la lista está vacía, crea un nuevo nodo y lo asigna tanto como el inicio como el final de la lista. Si la lista ya contiene elementos, agrega el nuevo nodo al final y actualiza el puntero al último nodo.

- **`lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento, size_t posicion)`:** Inserta un nuevo elemento en una posición específica de la lista. Si la posición especificada es igual al tamaño de la lista, el elemento se inserta al final. Si la posición es 0, se inserta al principio. En otro caso, se busca el nodo en la posición anterior a la especificada y se ajustan los punteros para insertar el nuevo nodo en medio de la lista.

- **`void *lista_quitar(lista_t *lista)`:** Elimina el último elemento de la lista y lo devuelve. Se ajustan los punteros para mantener la integridad de la lista y se libera la memoria del nodo eliminado.

- **`void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)`:** Elimina y devuelve el elemento en la posición especificada de la lista. Se ajustan los punteros para mantener la integridad de la lista y se libera la memoria del nodo eliminado.

- **`void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)`:** Retorna el elemento ubicado en la posición especificada en la lista. Itera sobre los nodos de la lista hasta alcanzar la posición deseada y devuelve el elemento asociado.

- **`void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *), void *contexto)`:** Busca un elemento que cumpla con cierta condición determinada por una función comparadora. Itera sobre los nodos de la lista y aplica la función comparadora a cada elemento hasta encontrar una coincidencia.

- **`void *lista_primero(lista_t *lista)`:** Retorna el primer elemento de la lista sin eliminarlo.

- **`void *lista_ultimo(lista_t *lista)`:** Retorna el último elemento de la lista sin eliminarlo.

- **`bool lista_vacia(lista_t *lista)`:** Verifica si la lista está vacía.

- **`size_t lista_tamanio(lista_t *lista)`:** Retorna la cantidad de elementos almacenados en la lista.

- **`void lista_destruir(lista_t *lista)`:** Libera la memoria reservada para la lista y sus nodos.

- **`void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))`:** Libera la memoria reservada para la lista y sus nodos, y aplica una función a cada elemento antes de eliminarlo.

- **`lista_iterador_t *lista_iterador_crear(lista_t *lista)`:** Crea un iterador para recorrer la lista.

- **`bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)`:** Verifica si el iterador tiene un siguiente elemento.

- **`bool lista_iterador_avanzar(lista_iterador_t *iterador)`:** Avanza el iterador al siguiente elemento de la lista.

- **`void *lista_iterador_elemento_actual(lista_iterador_t *iterador)`:** Retorna el elemento actual del iterador.

- **`void lista_iterador_destruir(lista_iterador_t *iterador)`:** Libera la memoria reservada para el iterador.

- **`size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *), void *contexto)`:** Itera sobre todos los elementos de la lista y aplica una función a cada uno de ellos. La iteración se detiene si la función devuelve `false`.

#### En `pila.c`:

- **`pila_t *pila_crear()`:** Crea una nueva pila vacía utilizando una lista enlazada. Simplemente crea una lista vacía utilizando la función `lista_crear()`.

- **`pila_t *pila_apilar(pila_t *pila, void *elemento)`:** Inserta un nuevo elemento en la parte superior de la pila. Utiliza la función `lista_insertar()` para agregar el elemento al final de la lista, que representa el tope de la pila.

- **`void *pila_desapilar(pila_t *pila)`:** Elimina y devuelve el elemento en la parte superior de la pila. Utiliza la función `lista_quitar()` para eliminar el último elemento de la lista, que representa el tope de la pila.

- **`void *pila_tope(pila_t *pila)`:** Retorna el elemento en la parte superior de la pila sin eliminarlo. Accede al último elemento de la lista, que representa el tope de la pila.

- **`size_t pila_tamanio(pila_t *pila)`:** Retorna la cantidad de elementos almacenados en la pila.

- **`bool pila_vacia(pila_t *pila)`:** Verifica si la pila está vacía.

- **`void pila_destruir(pila_t *pila)`:** Libera la memoria reservada para la pila y sus nodos.

#### En `cola.c`:

- **`cola_t *cola_crear()`:** Crea una nueva cola vacía utilizando una lista enlazada. Simplemente crea una lista vacía utilizando la función `lista_crear()`.

- **`cola_t *cola_encolar(cola_t *cola, void *elemento)`:** Encola un nuevo elemento al final de la cola. Utiliza la función `lista_insertar()` para agregar el elemento al final de la lista.

- **`void *cola_desencolar(cola_t *cola)`:** Desencola y devuelve el elemento en el frente de la cola. Utiliza la función `lista_quitar_de_posicion()` para eliminar el primer elemento de la lista, que representa el frente de la cola.

- **`void *cola_frente(cola_t *cola)`:** Retorna el elemento en el frente de la cola sin eliminarlo. Accede al primer elemento de la lista, que representa el frente de la cola.

- **`size_t cola_tamanio(cola_t *cola)`:** Retorna la cantidad de elementos almacenados en la cola.

- **`bool cola_vacia(cola_t *cola)`:** Verifica si la cola está vacía.

- **`void cola_destruir(cola_t *cola)`:** Libera la memoria reservada para la cola y sus nodos.


### Decisiones tomadas a lo largo del TP:
- Uso de listas enlazadas: se utilizó la implementación de nodos enlazados, ya que facilita el manejo de los mismos, en operaciones tales como inserción, búsqueda y eliminación.

- Manejo de memoria: se tuvo en cuenta la reserva de memoria (dinámica) en el heap mediante el uso de mallocs para la lista y para cada nodo por separado. A su vez, se libera la memoria una vez que ya no se requiera la misma.

- Verificaciones: se hacen validaciones de los datos enviados por parámetro en cada función.

### Diagramas relevantes:

A continuación se podrán ver los diagramas de funcionamiento de las operaciones básicas de los TDA de lista/pila/cola, entre ellos se encuentran: insertar, buscar, eliminar y destruir.

<div align="center">
<img width="45%" src="img/diagrama_flujo_insertar_lista.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/diagrama_flujo_apilar.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/diagrama_flujo_encolar.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/diagrama_flujo_buscar_lista.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/diagrama_flujo_quitar_lista.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/diagrama_flujo_desapilar.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/diagrama_flujo_desencolar.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/diagrama_flujo_destruir_lista.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/diagrama_flujo_destruir_pila.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/diagrama_flujo_destruir_cola.drawio.svg">
</div>

A su vez, el siguiente diagrama grafica el uso de memoria que se hace en las funciones lista_crear(), pila_crear(), nuevo_nodo(), cola_crear(), y las variables utilizadas en las pruebas.
<div align="center">
<img width="45%" src="img/stack_heap_diagrama.drawio.svg">
</div>


---

## Respuestas a las preguntas teóricas

**PUNTO 1:** ¿Qué es una lista/pila/cola? Explicar con diagramas.

### LISTA

Según lo definido por esta materia, la lista es un struct que cumple la función de agrupar elementos, teniendo en cuenta que los mismos tienen sucesor (excepto el último de la lista) y predecesor (excepto el primero de la lista). Más adelante, se definirán Pila y Cola, que son estructuras similares a la lista. En los tres casos, se pueden realizar las siguientes operaciones (que son las más generales):
- Crear (create).
- Insertar (insertAt) / Agregar.
- Vacía (isEmpty).
- Destruir (destroy).
- Eliminar (deleteAt) / Sacar.
- Ver elemento (find).

Las implementaciones vistas son de lista de nodos, o también nombrado como Nodos Enlazados. Los nodos se caracterizan por tener dos tipos de elementos, puntero/s y el elemento en el elemento.
Se clasifica en 4 tipos:
    - Simplemente enlazada: cada nodo tiene un elemento y un puntero que hace referencia al nodo siguiente. El último nodo de la lista apunta a NULL.
<div align="center">
<img width="45%" src="img/lista_s_e.drawio.svg">
</div>
    Para insertar un nodo al final de la lista, el puntero del último nodo ahora apunta al nodo que queremos agregar, y el puntero de éste debe apuntar a NULL.
<div align="center">
<img width="45%" src="img/insertar_final_s_e.drawio.svg">
</div>
    Si quiero insertar un elemento en cierta posición de la lista, primero tengo que hacer que el puntero del nuevo nodo apunte al nodo que estaba en la posición indicada, para luego hacer que el nodo de la posición anterior a la deseada apunte al nuevo nodo. De esta manera, no pierdo la dirección de memoria de ningún nodo.
<div align="center">
<img width="45%" src="img/inserto_posicion_s_e.drawio.svg">
</div>
    En el caso de querer eliminar un elemento en cierta posición de la lista, primero hago un nodo auxiliar que apunte al nodo a eliminar, después hago que el nodo del anterior tenga el puntero que estaba en el nodo a eliminar (para no perder la dirección del próximo nodo), y luego elimino el nodo deseado. Por último, se hace free a donde apunta el auxiliar.
<div align="center">
<img width="45%" src="img/elimino_posicion_s_e.drawio.svg">
</div>
    - Doblemente enlazada: cada nodo tiene un elemento, un puntero que hace referencia al nodo anterior y un puntero que hace referencia al nodo siguiente. El puntero al anterior del primer nodo apunta a NULL, al igual que el puntero al siguiente del último nodo.
<div align="center">
<img width="45%" src="img/lista_d_e.drawio.svg">
</div>
    Para insertar un elemento en cierta posición de la lista, primero tengo que guardar las direcciones de memoria del predecesor y sucesor del nodo que deseo agregar a la lista en los punteros del nuevo nodo. Luego completo los punteros (de predecesor y sucesor) con la dirección del nuevo nodo.
<div align="center">
<img width="45%" src="img/inserto_posicion_d_e.drawio.svg">
</div>
    En cambio, para eliminar un elemento en cierta posición, primero hago que un auxiliar apunte al nodo a eliminar, luego hago que el predecesor a la lista apunte al sucesor y viceversa. De esta manera, puedo eliminar el nodo deseado. Por último, se hace free del nodo eliminado y del auxiliar que se utilizó.
<div align="center">
<img width="45%" src="img/elimino_posicion_d_e.drawio.svg">
</div>
    - Circular simplemente enlazada: tiene una estructura similar a la simplemente enlazada, sólo que los punteros nunca apuntan a NULL. El puntero del último elemento, apunta al primero de la lista.
    Las operaciones (insertar y eliminar) se hacen de la misma manera que en el primer caso.
<div align="center">
<img width="45%" src="img/lista_circular_s_e.drawio.svg">
</div>
    - Circular doblemente enlazada:  tiene una estructura similar a la doblemente enlazada, sólo que los punteros nunca apuntan a NULL. El puntero sucesor del último elemento, apunta al primero de la lista; y el puntero predecesor del primero, apunta al último de la lista.
    Las operaciones (insertar y eliminar) se hacen de la misma manera que en el segundo caso.
<div align="center">
<img width="45%" src="img/lista_circular_d_e.drawio.svg">
</div>

### PILA
De acuerdo a lo explicado en clase, una pila es una estructura de datos que agrupa elemento bajo la política de salida LIFO "Last In, First Out". La única manera que tenemos para acceder a la pila es a través de su tope.
Además de las operaciones que tiene la lista, la pila tiene otras que se pueden realizar para manejarlas:
- Apilar (push).
- Tope (top).
- Desapilar (pop).

Hay 3 implementaciones de la pila que vimos en clase:
- Vector estático: en esta implementación, se debe tener en cuenta que cuando se llega al tope del vector estático, NO se puede agregar nada más.
        - Para apilar, debemos tener en cuenta que el tope sea distinto a la cantidad de 'casilleros' que tiene la pila.
        - Para ver si está vacía, el tope tiene que ser igual a 0.
        - Para desapilar, el tope tiene que ser distinto a 0.
- Vector dinámico:
        - Siempre se puede apilar, ya que cuando se llega al tope, se puede pedir más memoria (ya que es dinámico).
        - Para ver si está vacía, el tope tiene que ser igual a 0.
        - Para desapilar, el tope tiene que ser distinto a 0.
    En esta implementación, se debe tener en cuenta la REDIMENSIÓN del vector.
    Por ejemplo, si estoy apilando y el vector supera el 75% de su capacidad, debo hacer realloc al vector para pedirle más memoria.
    Pero en el caso de que esté desapilando, si la capacidad ocupada es del 25%, también debería hacer realloc del mismo.
- Pila como lista de nodos: en esta implementación, el puntero de la pila apunta al primer nodo de la misma. En este caso, los nodos se componen de un puntero al nodo anterior y un elemento.
<div align="center">
<img width="45%" src="img/pila.drawio.svg">
</div>
        - Para apilar, tengo que agregar el nuevo nodo al final de la pila, haciendo que el puntero del nuevo nodo apunte hacia el tope de la pila, y luego hago que el puntero de la pila apunte al nodo apilado.
<div align="center">
<img width="45%" src="img/apilar.drawio.svg">
</div>
        - Para desapilar, primero cambio el puntero de la pila al anteúltimo nodo de la pila, y después hago free del nodo que se quería eliminar (es decir, el último).
<div align="center">
<img width="45%" src="img/desapilar.drawio.svg">
</div>

### COLA

<div align="center">
<img width="45%" src="img/cola.drawio.svg">
</div>

En esta oportunidad, decimos que una cola es, también, una estructura de datos que agrupa elementos, pero que en este caso aplica la política FIFO "First In, First Out".
Al igual que la pila, tiene otras que se pueden realizar:
- Destruir
- Primero: devuelve qué elemento está adelante de todo.

Las implementaciones de la cola se dividen en las mismas categorías que la pila:
- Vector estático: en este caso, cuando el tope y el fin son iguales, no se pueden encolar más elementos.
        - Encolar: debemos tener en cuenta que el tope sea distinto al fin la cola.
<div align="center">
<img width="45%" src="img/encolar.drawio.svg">
</div>
        - Desencolar: se debe tener en cuenta que el tope tiene que ser distinto al principio. Además, cuando desencolo voy cambiando el principio y perdiendo espacios de memoria, por lo que se debe buscar una solución.
<div align="center">
<img width="45%" src="img/desencolar.drawio.svg">
</div>
            - Desplazando elementos: muevo todos los elementos un lugar más adelante para que el principio siempre esté en la posición 0.
<div align="center">
<img width="45%" src="img/desencolar_desplazando_elementos.drawio.svg">
</div>
            - Usando cola circular: se van haciendo 'trackeos' de los movimientos circulares, de manera tal que el tope siempre quede una posición antes que el principio.
<div align="center">
<img width="45%" src="img/desencolar_cola_circular.drawio.svg">
</div>
- Vector dinámico: encolar y desencolar funcionan de manera similar que con un vector estático. La diferencia es que, al encolar, puedo redimensionar el vector para no quedarme sin espacio.
- Nodos enlazados: en este caso, cada cola tiene un puntero al principio y otro al final de la misma.
<div align="center">
<img width="45%" src="img/cola_nodos_vacía.drawio.svg">
</div>
<div align="center">
<img width="45%" src="img/cola_nodos.drawio.svg">
</div>
        - Encolar: debo hacer que el puntero del último nodo de la cola apunte al nuevo nodo, y luego el puntero de este último debe apuntar a NULL. Después el puntero al final de la cola, debe apuntar al nuevo nodo.
<div align="center">
<img width="45%" src="img/encolar_nodos.drawio.svg">
</div>
        - Desencolar: hago que un nodo auxiliar apunte al primer nodo de la cola, después el puntero de este le 'pasa' la dirección al puntero del principio de la cola. Para finalizar, se le hace free al nodo desencolado.
<div align="center">
<img width="45%" src="img/desencolar_nodos.drawio.svg">
</div>

**PUNTO 2:** Explica y analiza las diferencias de complejidad entre las implementaciones de lista simplemente enlazada, doblemente enlazada y vector dinámico para las operaciones:
- Insertar/obtener/eliminar al inicio
- Insertar/obtener/eliminar al final
- Insertar/obtener/eliminar al medio

### Complejidades
#### Lista Simplemente Enlazada
##### Al inicio
- Insertar: O(1) -> se crea un nuevo nodo y se ajustan los punteros para que el nuevo nodo sea el primero.
- Obtener: O(1) -> se accede directamente al primer nodo.
- Eliminar: O(1) -> se ajustan los punteros para saltar el nodo que se desea eliminar y luego se libera la memoria del nodo.

##### Al final
- Insertar: O(n) -> (en el peor caso) -> se debe recorrer toda la lista para llegar al ùltimo nodo y luego realizar la inserción.
- Obtener: O(n) -> (en el peor caso) -> se debe recorrer toda la lista hasta el último nodo.
- Eliminar: O(n) -> (en el peor caso) -> se debe recorrer toda la lista hasta el anteúltimo nodo, para luego cambiar los punteros y liberar los espacios de memoria correspondientes.

##### Al medio
- Insertar: O(n) -> (en el peor caso) -> se debe recorrer toda la lista para llegar a la posición deseada.
- Obtener: O(n) -> (en el peor caso) -> se debe recorrrer toda la lista hasta llegar a la posición deseada.
- Eliminar: O(n) -> (en el peor caso) -> se debe recorrer la lista hasta llegar al nodo anterior al que se quiere eliminar.

#### Lista Doblemente Enlazada
##### Al inicio
- Insertar: O(1) -> se crea un nuevo nodo y se ajustan los punteros para que el nuevo nodo sea el primero.
- Obtener: O(1) -> se accede directamente al primer nodo.
- Eliminar: O(1) -> se ajustan los punteros para saltar el primer nodo y luego se libera la memoria del nodo.

##### Al final
- Insertar: O(1) ->se ajustan los punteros del último nodo.
- Obtener: O(1) -> se accede directamente al último nodo.
- Eliminar: O(1) -> se ajustan los punteros para saltar el último nodo y luego se libera la memoria del nodo.

##### Al medio
- Insertar: O(n) -> (en el peor caso) -> se debe recorrer toda la lista para llegar a la posición deseada.
- Obtener: O(n) -> (en el peor caso) -> se debe recorrrer toda la lista hasta llegar a la posición deseada.
- Eliminar: O(n) -> (en el peor caso) -> se debe recorrer la lista hasta llegar al nodo que se quiere eliminar.


#### Vector Dinámico
- En todos los casos, si se necesita redimensionar el vector, puede ser que el proceso lleve más tiempo de ejecución.

##### Al inicio
- Insertar: O(n) -> (en el peor caso) -> se deben mover todos los elementos actuales una posición más atrás para poner el nuevo elemento en la posición 0.
- Obtener y eliminar: O(1) -> acceso directo a cualquier posición del vector una vez que se conoce el índice.

##### Al final
- Insertar: O(1) -> si hay espacio disponible en el vector, la inserción al final es más sencilla. 
- Obtener y eliminar: O(1) -> acceso directo a cualquier posición del arreglo una vez que se conoce el índice.

##### Al medio
- Insertar: O(n) -> (en el peor caso) -> se deben mover todos los elementos actuales que estén después de la posición en la que se va a insertar, para poner el nuevo elemento en el lugar deseado.
- Obtener y eliminar: O(1) -> acceso directo a cualquier posición del arreglo una vez que se conoce el índice.


**PUNTO 3:** Explica la complejidad de las operaciones implementadas en tu trabajo para la pila y la cola.

Antes de analizar la complejidad de las operaciones implementadas en los archivos de pila y cola, se debe tneer en cuenta que, principalmente, se utilizan funciones de los archivos lista para facilitar la estructura del código. Es decir, se reutilizan funciones creadas para el TDA Lista, ya que Cola y Pila son estructuras de datos prácticamente basadas en Lista. Habiendo dejado eso en claro, paso al análisis de complejidad de cada operación:

#### Complejidades de pila.c
##### pila_crear()
Complejidad: O(1) 

##### pila_apilar()
Complejidad: O(1) 

##### pila_desapilar()
Complejidad: O(1) 

##### pila_tope()
Complejidad: O(1) 

##### pila_tamanio()
Complejidad: O(1) 

##### pila_vacia()
Complejidad: O(1) 

##### pila_destruir()
Complejidad: O(n) 

#### Complejidades de cola.c
##### cola_crear()
Complejidad: O(1) 

##### cola_encolar()
Complejidad: O(1) 

##### cola_desencolar()
Complejidad: O(1) 

##### cola_frente()
Complejidad: O(1) 

##### cola_tamanio()
Complejidad: O(1) 

##### cola_encolar()
Complejidad: O(1) 

##### cola_vacia()
Complejidad: O(1) 

##### cola_destruir()
Complejidad: O(n) 

##### A destacar:
Se debe tener en cuenta, que las operaciones con complejidad O(1), son operaciones que reutilizan funciones de la lista. En cambio, ambas funciones de destruir (que tienen complejidad O(n)), tiene que destruir la pila/cola utilizada, y además la lista que está dentro de su respectivo struct.
