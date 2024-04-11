<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA LISTA

## Alumno: Agustina Thames Alderete - 111287 - athames@fi.uba.ar

- Para compilar:

```bash
línea de compilación
```

- Para ejecutar:

```bash
línea de ejecución
```

- Para ejecutar con valgrind:
```bash
línea con valgrind
```

---

##  Funcionamiento

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluír **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas

###LISTA

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
<img width="70%" src="img/lista_s_e.drawio.svg">
</div>
    Para insertar un nodo al final de la lista, el puntero del último nodo ahora apunta al nodo que queremos agregar, y el puntero de éste debe apuntar a NULL.
<div align="center">
<img width="70%" src="img/insertar_final_s_e.drawio.svg">
</div>
    Si quiero insertar un elemento en cierta posición de la lista, primero tengo que hacer que el puntero del nuevo nodo apunte al nodo que estaba en la posición indicada, para luego hacer que el nodo de la posición anterior a la deseada apunte al nuevo nodo. De esta manera, no pierdo la dirección de memoria de ningún nodo.
<div align="center">
<img width="70%" src="img/inserto_posicion_s_e.drawio.svg">
</div>
    En el caso de querer eliminar un elemento en cierta posición de la lista, primero hago un nodo auxiliar que apunte al nodo a eliminar, después hago que el nodo del anterior tenga el puntero que estaba en el nodo a eliminar (para no perder la dirección del próximo nodo), y luego elimino el nodo deseado. Por último, se hace free a donde apunta el auxiliar.
<div align="center">
<img width="70%" src="img/elimino_posicion_s_e.drawio.svg">
</div>
    - Doblemente enlazada: cada nodo tiene un elemento, un puntero que hace referencia al nodo anterior y un puntero que hace referencia al nodo siguiente. El puntero al anterior del primer nodo apunta a NULL, al igual que el puntero al siguiente del último nodo.
<div align="center">
<img width="70%" src="img/lista_d_e.drawio.svg">
</div>
    Para insertar un elemento en cierta posición de la lista, primero tengo que guardar las direcciones de memoria del predecesor y sucesor del nodo que deseo agregar a la lista en los punteros del nuevo nodo. Luego completo los punteros (de predecesor y sucesor) con la dirección del nuevo nodo.
<div align="center">
<img width="70%" src="img/inserto_posicion_d_e.drawio.svg">
</div>
    En cambio, para eliminar un elemento en cierta posición, primero hago que un auxiliar apunte al nodo a eliminar, luego hago que el predecesor a la lista apunte al sucesor y viceversa. De esta manera, puedo eliminar el nodo deseado. Por último, se hace free del nodo eliminado y del auxiliar que se utilizó.
<div align="center">
<img width="70%" src="img/elimino_posicion_d_e.drawio.svg">
</div>
    - Circular simplemente enlazada: tiene una estructura similar a la simplemente enlazada, sólo que los punteros nunca apuntan a NULL. El puntero del último elemento, apunta al primero de la lista.
    Las operaciones (insertar y eliminar) se hacen de la misma manera que en el primer caso.
<div align="center">
<img width="70%" src="img/lista_circular_s_e.drawio.svg">
</div>
    - Circular doblemente enlazada:  tiene una estructura similar a la doblemente enlazada, sólo que los punteros nunca apuntan a NULL. El puntero sucesor del último elemento, apunta al primero de la lista; y el puntero predecesor del primero, apunta al último de la lista.
    Las operaciones (insertar y eliminar) se hacen de la misma manera que en el segundo caso.
<div align="center">
<img width="70%" src="img/lista_circular_d_e.drawio.svg">
</div>

###PILA

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
<img width="70%" src="img/pila.drawio.svg">
</div>
        - Para apilar, tengo que agregar el nuevo nodo al final de la pila, haciendo que el puntero del nuevo nodo apunte hacia el tope de la pila, y luego hago que el puntero de la pila apunte al nodo apilado.
<div align="center">
<img width="70%" src="img/apilar.drawio.svg">
</div>
        - Para desapilar, primero cambio el puntero de la pila al anteúltimo nodo de la pila, y después hago free del nodo que se quería eliminar (es decir, el último).
<div align="center">
<img width="70%" src="img/desapilar.drawio.svg">
</div>
------------------------------------------------------------------------------------------------------------------------

COLA

<div align="center">
<img width="70%" src="img/cola.drawio.svg">
</div>

En esta oportunidad, decimos que una cola es, también, una estructura de datos que agrupa elementos, pero que en este caso aplica la política FIFO "First In, First Out".
Al igual que la pila, tiene otras que se pueden realizar:
    - Destruir
    - Primero: devuelve qué elemento está adelante de todo.

Las implementaciones de la cola se dividen en las mismas categorías que la pila:
    - Vector estático: en este caso, cuando el tope y el fin son iguales, no se pueden encolar más elementos.
        - Encolar: debemos tener en cuenta que el tope sea distinto al fin la cola.
<div align="center">
<img width="70%" src="img/encolar.drawio.svg">
</div>
        - Desencolar: se debe tener en cuenta que el tope tiene que ser distinto al principio. Además, cuando desencolo voy cambiando el principio y perdiendo espacios de memoria, por lo que se debe buscar una solución.
<div align="center">
<img width="70%" src="img/desencolar.drawio.svg">
</div>
            - Desplazando elementos: muevo todos los elementos un lugar más adelante para que el principio siempre esté en la posición 0.
<div align="center">
<img width="70%" src="img/desencolar_desplazando_elementos.drawio.svg">
</div>
            - Usando cola circular: se van haciendo 'trackeos' de los movimientos circulares, de manera tal que el tope siempre quede una posición antes que el principio.
<div align="center">
<img width="70%" src="img/desencolar_cola_circular.drawio.svg">
</div>
    - Vector dinámico: encolar y desencolar funcionan de manera similar que con un vector estático. La diferencia es que, al encolar, puedo redimensionar el vector para no quedarme sin espacio.
    - Nodos enlazados: en este caso, cada cola tiene un puntero al principio y otro al final de la misma.
<div align="center">
<img width="70%" src="img/cola_nodos_vacía.drawio.svg">
</div>
<div align="center">
<img width="70%" src="img/cola_nodos.drawio.svg">
</div>
        - Encolar: debo hacer que el puntero del último nodo de la cola apunte al nuevo nodo, y luego el puntero de este último debe apuntar a NULL. Después el puntero al final de la cola, debe apuntar al nuevo nodo.
<div align="center">
<img width="70%" src="img/encolar_nodos.drawio.svg">
</div>
        - Desencolar: hago que un nodo auxiliar apunte al primer nodo de la cola, después el puntero de este le 'pasa' la dirección al puntero del principio de la cola. Para finalizar, se le hace free al nodo desencolado.
<div align="center">
<img width="70%" src="img/desencolar_nodos.drawio.svg">
</div>