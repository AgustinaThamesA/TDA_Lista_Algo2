#include "pa2m.h"
#include "src/cola.h"
#include "src/lista.h"
#include "src/pila.h"
#include <stdio.h>
#include <string.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t espacios;
};

struct lista_iterador {
	nodo_t *actual;
	lista_t *lista;
	nodo_t *anterior;
	int sarasa;
};

void crear_lista_devuelve_lista_con_nodos_null_y_espacios_en_0()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista->nodo_inicio == NULL && lista->nodo_final == NULL &&
			     lista->espacios == 0,
		     "Se crea una lista con nodos en NULL y espacios en 0.");

	lista_destruir(lista);
}

void crea_lista_vacia()
{
	lista_t *lista = lista_crear();
	bool lista_esta_vacia = lista_vacia(NULL);
	pa2m_afirmar(lista_esta_vacia == true,
		     "Lista NULL es una lista vacía.");

	lista_esta_vacia = lista_vacia(lista);
	pa2m_afirmar(lista_esta_vacia == true,
		     "Lista creada no tiene elementos (vacía).");

	lista_insertar(lista, "prueba_vacia1");
	lista_insertar(lista, "prueba_vacia2");
	lista_esta_vacia = lista_vacia(lista);
	pa2m_afirmar(lista_esta_vacia == false,
		     "Lista con elementos no está vacía.");

	lista_destruir(lista);
}

void inserta_elementos_en_lista()
{
	lista_t *lista = lista_crear();
	char *prueba_1 = "prueba elemento 1";
	char *prueba_2 = "prueba elemento 2";

	lista_t *lista_pruebas = lista_insertar(NULL, prueba_1);
	pa2m_afirmar(lista_pruebas == NULL,
		     "No inserta un elemento en una lista NULL.");

	lista_destruir(lista);

	lista = lista_crear();
	lista_insertar(lista, prueba_1);
	lista_pruebas = lista_insertar(lista, prueba_2);
	pa2m_afirmar(lista_pruebas != 0 &&
			     lista->nodo_inicio->elemento == prueba_1 &&
			     lista->nodo_final->elemento == prueba_2 &&
			     lista->espacios == 2,
		     "Inserción correcta de elementos en lista vacía.");

	lista_destruir(lista);
}

void inserta_elementos_en_posicion_i_lista()
{
	lista_t *lista = lista_crear();
	char *prueba_1 = "prueba elemento 1";
	char *prueba_2 = "prueba elemento 2";
	char *prueba_2_1 = "prueba elemento 2.1";
	char *prueba_3 = "prueba elemento 3";
	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);
	lista_insertar(lista, prueba_3);
	lista_t *lista_pruebas =
		lista_insertar_en_posicion(lista, prueba_2_1, 0);

	pa2m_afirmar(
		lista_pruebas != NULL &&
			lista->nodo_inicio->elemento == prueba_2_1 &&
			lista_elemento_en_posicion(lista, 1) == prueba_1 &&
			lista_elemento_en_posicion(lista, 2) == prueba_2 &&
			lista_elemento_en_posicion(lista, 3) == prueba_3 &&
			lista->nodo_final->elemento == prueba_3 &&
			lista->espacios == 4,
		"Se inserta un elemento correctamente en la posicion 0 de una lista no "
		"vacía.");

	lista_destruir(lista);
}

void quitar_elementos_en_lista()
{
	lista_t *lista = lista_crear();
	char *prueba_1 = "prueba elemento 1";
	char *prueba_2 = "prueba elemento 2";

	lista_t *lista_pruebas = lista_quitar(NULL);
	pa2m_afirmar(lista_pruebas == NULL,
		     "No se puede usar lista_quitar para una lista NULL.");

	lista_pruebas = lista_quitar(lista);
	pa2m_afirmar(lista_pruebas == NULL,
		     "No se puede usar lista_quitar para una lista vacía.");

	lista_insertar(lista, prueba_1);
	lista_pruebas = lista_quitar(lista);
	pa2m_afirmar(lista_pruebas != NULL && lista->nodo_inicio == NULL &&
			     lista->nodo_final == NULL && lista->espacios == 0,
		     "Se borra el único elemento de una lista, y queda vacía.");

	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);
	lista_pruebas = lista_quitar(lista);
	pa2m_afirmar(lista_pruebas != NULL &&
			     lista->nodo_inicio->elemento == prueba_1 &&
			     lista->nodo_final->elemento == prueba_1 &&
			     lista->espacios == 1,
		     "Se borra el último elemento de una lista correctamente.");

	lista_destruir(lista);
}

void quitar_elemento_en_posicion_i_en_lista()
{
	lista_t *lista = lista_crear();
	char *prueba_1 = "prueba elemento 1";
	char *prueba_2 = "prueba elemento 2";

	lista_t *lista_pruebas = lista_quitar_de_posicion(NULL, 0);
	pa2m_afirmar(
		lista_pruebas == NULL,
		"No se puede usar lista_quitar_de_posicion para una lista NULL.");

	lista_pruebas = lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(
		lista_pruebas == NULL,
		"No se puede usar lista_quitar_de_posicion para una lista vacía.");

	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);

	lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(lista != NULL &&
			     lista->nodo_inicio->elemento == prueba_2 &&
			     lista->nodo_final->elemento == prueba_2 &&
			     lista->espacios == 1,
		     "Se borra el primer elemento de la lista correctamente.");

	lista_quitar_de_posicion(lista, 8);
	pa2m_afirmar(lista != NULL &&
			     lista->nodo_inicio->elemento == prueba_2 &&
			     lista->nodo_final->elemento == prueba_2 &&
			     lista->espacios == 1,
		     "No se borra el elemento de la lista ya que se pasa una "
		     "posición que no existe.");

	lista_destruir(lista);
}

bool mostrar_para_prueba_iterador_interno(void *elemento, void *contador)
{
	if (elemento && contador)
		(*(int *)contador)++;
	return true;
}

void iterador_interno_en_lista()
{
	lista_t *lista = lista_crear();
	int cant_elementos_iterados = 0;
	char *prueba_1 = "prueba elemento 1";
	char *prueba_2 = "prueba elemento 2";

	size_t cantidad = lista_con_cada_elemento(
		NULL, mostrar_para_prueba_iterador_interno,
		&cant_elementos_iterados);
	pa2m_afirmar(cantidad == 0 && cant_elementos_iterados == 0,
		     "Iterador interno con función NULL");

	cantidad =
		lista_con_cada_elemento(lista, NULL, &cant_elementos_iterados);
	pa2m_afirmar(cantidad == 0 && cant_elementos_iterados == 0,
		     "Iterador interno con función NULL en lista");

	cantidad = lista_con_cada_elemento(lista,
					   mostrar_para_prueba_iterador_interno,
					   &cant_elementos_iterados);
	pa2m_afirmar(cantidad == 0 && cant_elementos_iterados == 0,
		     "Iterador interno con lista vacía");

	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);

	cantidad = lista_con_cada_elemento(lista,
					   mostrar_para_prueba_iterador_interno,
					   &cant_elementos_iterados);
	pa2m_afirmar(cantidad == 2 && cant_elementos_iterados == 2,
		     "Iterador interno con lista no vacía");

	cantidad = lista_con_cada_elemento(
		lista, mostrar_para_prueba_iterador_interno, NULL);
	pa2m_afirmar(cantidad == 2 && cant_elementos_iterados == 2,
		     "Iterador interno con lista no vacía, contexto NULL");

	lista_destruir(lista);
}

int comparar_cadenas(void *elemento, void *contexto)
{
	char *cadena_elemento = (char *)elemento;
	char *cadena_buscar = (char *)contexto;
	return strcmp(cadena_elemento, cadena_buscar);
}

int comparar_enteros(void *elemento, void *contexto)
{
	int valor_elemento = *(int *)elemento;
	int valor_buscar = *(int *)contexto;
	return (valor_elemento == valor_buscar) ? 0 : 1;
}

void buscar_elemento_en_lista()
{
	lista_t *lista = lista_crear();
	char *prueba_1 = "hola";
	char *prueba_2 = "mundo";
	int num_1 = 100;
	int num_2 = 200;

	void *buscador = NULL;

	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);
	lista_insertar(lista, &num_1);
	lista_insertar(lista, &num_2);

	buscador = lista_buscar_elemento(NULL, comparar_cadenas, prueba_2);
	pa2m_afirmar(buscador == NULL, "Buscador de lista NULL devuelve NULL.");

	buscador = lista_buscar_elemento(lista, NULL, prueba_2);
	pa2m_afirmar(buscador == NULL,
		     "Buscador de lista con comparador NULL devuelve NULL.");

	buscador = lista_buscar_elemento(lista, comparar_cadenas, prueba_2);
	pa2m_afirmar(
		buscador == prueba_2,
		"Buscador de un elemento (cadena de strings) que existe en la "
		"lista devuelve el elemento correcto.");

	buscador = lista_buscar_elemento(lista, comparar_cadenas, "no_existe");
	pa2m_afirmar(
		buscador == NULL,
		"Buscador de un elemento que no existe (cadena de strings) en "
		"la lista devuelve NULL.");

	buscador = lista_buscar_elemento(lista, comparar_enteros, &num_1);
	pa2m_afirmar(
		buscador == &num_1,
		"Buscador de un elemento (número entero) que existe en la lista "
		"devuelve el elemento correcto.");

	int prueba_entero = 9;
	buscador =
		lista_buscar_elemento(lista, comparar_cadenas, &prueba_entero);
	pa2m_afirmar(buscador == NULL,
		     "Buscador de un elemento que no existe "
		     "(número entero) en la lista devuelve NULL.");

	lista_destruir(lista);
}

void iterador_externo_en_lista()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = NULL;
	char *prueba_1 = "prueba elemento 1";
	char *prueba_2 = "prueba elemento 2";
	char *prueba_3 = "prueba elemento 3";

	iterador = lista_iterador_crear(NULL);
	pa2m_afirmar(iterador == NULL,
		     "No se crea un iterador de una lista NULL.");

	iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador->lista == lista &&
			     iterador->actual == lista->nodo_inicio,
		     "Se crea correctamente un iterador de una lista vacía.");
	lista_iterador_destruir(iterador);

	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);
	lista_insertar(lista, prueba_3);
	iterador = lista_iterador_crear(lista);
	pa2m_afirmar(
		iterador->lista == lista &&
			iterador->actual == lista->nodo_inicio,
		"El iterador inicialmente apunta al elemento correcto de la lista.");

	pa2m_afirmar(lista_iterador_tiene_siguiente(NULL) == false,
		     "Iterador no tiene siguiente en lista NULL.");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);

	lista = lista_crear();
	iterador = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == false,
		     "Iterador no tiene siguiente en lista vacía.");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);

	lista = lista_crear();
	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);
	iterador = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true,
		     "Iterador tiene siguiente en lista de elementos.");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);

	pa2m_afirmar(lista_iterador_avanzar(NULL) == false,
		     "Iterador no puede avanzar con una lista NULL.");

	lista = lista_crear();
	iterador = lista_iterador_crear(lista);
	bool puede_avanzar = lista_iterador_avanzar(iterador);
	pa2m_afirmar(puede_avanzar == false && iterador->actual == NULL,
		     "Iterador no puede avanzar con una lista vacía.");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);

	lista = lista_crear();
	lista_insertar(lista, prueba_1);
	iterador = lista_iterador_crear(lista);
	puede_avanzar = lista_iterador_avanzar(iterador);
	pa2m_afirmar(
		puede_avanzar == false && iterador->actual == NULL,
		"Iterador no puede avanzar con una lista de un sólo elemento.");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);

	lista = lista_crear();
	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);
	lista_insertar(lista, prueba_3);
	iterador = lista_iterador_crear(lista);
	puede_avanzar = lista_iterador_avanzar(iterador);
	pa2m_afirmar(puede_avanzar == true &&
			     iterador->actual == lista->nodo_inicio->siguiente,
		     "Iterador avanza una vez con una lista de 3 elementos.");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);

	lista = lista_crear();
	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);
	lista_insertar(lista, prueba_3);
	iterador = lista_iterador_crear(lista);
	puede_avanzar = lista_iterador_avanzar(iterador);
	puede_avanzar = lista_iterador_avanzar(iterador);
	pa2m_afirmar(
		puede_avanzar == true && iterador->actual == lista->nodo_final,
		"Iterador avanza hasta llegar al último elemento de una lista "
		"de 3 elementos.");

	puede_avanzar = lista_iterador_avanzar(iterador);
	pa2m_afirmar(
		puede_avanzar == false && iterador->actual == NULL,
		"Iterador avanza hasta que termina una lista de 3 elementos, y "
		"termina apuntando a NULL.");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void crea_pila_vacia()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila != NULL && pila_tamanio(pila) == 0,
		     "Se crea pila vacía correctamente.");
	pila_destruir(pila);
}

void apila_correctamente()
{
	pila_t *pila = pila_crear();
	int prueba_1 = 1;
	int prueba_2 = 2;
	int prueba_3 = 3;
	pila_t *apila = pila_apilar(NULL, &prueba_1);
	pa2m_afirmar(apila == NULL, "No apila con pila NULL.");

	apila = pila_apilar(pila, &prueba_1);

	pa2m_afirmar(apila != NULL && pila_tamanio(pila) == 1,
		     "Apila un elemento correctamente.");

	apila = pila_apilar(pila, &prueba_2);
	apila = pila_apilar(pila, &prueba_3);

	pa2m_afirmar(apila != NULL && pila_tamanio(pila) == 3,
		     "Apila tres elementos correctamente.");

	pila_destruir(pila);
}

void desapila_correctamente()
{
	pila_t *pila = pila_crear();
	int prueba_1 = 1;
	int prueba_2 = 2;
	int prueba_3 = 3;
	void *desapila = pila_desapilar(pila);
	pa2m_afirmar(pila_desapilar(NULL) == NULL,
		     "No desapila una pila NULL.");

	pa2m_afirmar(desapila == NULL, "No desapila una pila vacía.");

	pila_apilar(pila, &prueba_1);
	pila_apilar(pila, &prueba_2);
	pila_apilar(pila, &prueba_3);

	desapila = pila_desapilar(pila);

	pa2m_afirmar(desapila != NULL && pila_tamanio(pila) == 2,
		     "Desapila un elemento correctamente.");

	pila_destruir(pila);
}

void prueba_booleano_pila_vacia()
{
	pila_t *pila = pila_crear();
	int prueba_1 = 1;
	int prueba_2 = 2;
	int prueba_3 = 3;

	pa2m_afirmar(pila_vacia(NULL) == true,
		     "Pila NULL devuelve pila vacía true.");
	pa2m_afirmar(pila_vacia(pila) == true,
		     "Pila vacía devuelve pila vacía true.");

	pila_apilar(pila, &prueba_1);
	pila_apilar(pila, &prueba_2);
	pila_apilar(pila, &prueba_3);

	bool vacia = pila_vacia(pila);

	pa2m_afirmar(vacia == false,
		     "Pila no vacía devuelve pila vacía false.");

	pila_destruir(pila);
}

void tope_pila_correcto()
{
	pila_t *pila = pila_crear();
	int prueba_1 = 1;
	int prueba_2 = 2;
	int prueba_3 = 3;

	pa2m_afirmar(pila_tope(NULL) == NULL, "Tope NULL de pila NULL.");

	pa2m_afirmar(pila_tope(pila) == NULL, "Tope NULL de pila vacía.");

	pila_apilar(pila, &prueba_1);
	pila_apilar(pila, &prueba_2);
	pila_apilar(pila, &prueba_3);
	void *tope = pila_tope(pila);
	pa2m_afirmar(tope == &prueba_3,
		     "Devuelve tope correcto de pila con 3 elementos.");

	pila_destruir(pila);
}

void crea_cola_vacia()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL && cola_tamanio(cola) == 0,
		     "Se crea cola vacía correctamente.");
	cola_destruir(cola);
}

void prueba_booleano_cola_vacia()
{
	cola_t *cola = cola_crear();
	int prueba_1 = 1;
	int prueba_2 = 2;
	int prueba_3 = 3;

	pa2m_afirmar(cola_vacia(NULL) == true,
		     "Cola NULL devuelve cola vacía true.");
	pa2m_afirmar(cola_vacia(cola) == true,
		     "Cola vacía devuelve cola vacía true.");

	cola_encolar(cola, &prueba_1);
	cola_encolar(cola, &prueba_2);
	cola_encolar(cola, &prueba_3);

	bool vacia = cola_vacia(cola);

	pa2m_afirmar(vacia == false,
		     "Cola no vacía devuelve cola vacía false.");

	cola_destruir(cola);
}

void encola_correctamente()
{
	cola_t *cola = cola_crear();
	int prueba_1 = 1;
	int prueba_2 = 2;
	int prueba_3 = 3;
	cola_t *encola = cola_encolar(NULL, &prueba_1);
	pa2m_afirmar(encola == NULL, "No encola con cola NULL.");

	encola = cola_encolar(cola, &prueba_1);

	pa2m_afirmar(encola != NULL && cola_tamanio(cola) == 1,
		     "Encola un elemento correctamente.");

	encola = cola_encolar(cola, &prueba_2);
	encola = cola_encolar(cola, &prueba_3);

	pa2m_afirmar(encola != NULL && cola_tamanio(cola) == 3,
		     "Encola tres elementos correctamente.");

	cola_destruir(cola);
}

void desencola_correctamente()
{
	cola_t *cola = cola_crear();
	int prueba_1 = 1;
	int prueba_2 = 2;
	int prueba_3 = 3;
	void *desencola = cola_desencolar(cola);
	pa2m_afirmar(cola_desencolar(NULL) == NULL,
		     "No desencola una cola NULL.");

	pa2m_afirmar(desencola == NULL, "No desencola una cola vacía.");

	cola_encolar(cola, &prueba_1);
	cola_encolar(cola, &prueba_2);
	cola_encolar(cola, &prueba_3);

	desencola = cola_desencolar(cola);

	pa2m_afirmar(desencola != NULL && cola_tamanio(cola) == 2,
		     "Desencola un elemento correctamente.");

	cola_destruir(cola);
}

void cola_primero_correcto()
{
	cola_t *cola = cola_crear();
	int prueba_1 = 1;
	int prueba_2 = 2;
	int prueba_3 = 3;

	pa2m_afirmar(cola_frente(NULL) == NULL, "Tope NULL de cola NULL.");

	pa2m_afirmar(cola_frente(cola) == NULL, "Tope NULL de cola vacía.");

	cola_encolar(cola, &prueba_1);
	cola_encolar(cola, &prueba_2);
	cola_encolar(cola, &prueba_3);
	void *primero = cola_frente(cola);
	pa2m_afirmar(primero == &prueba_1,
		     "Devuelve primero correcto de cola con 3 elementos.");

	cola_destruir(cola);
}

void destruir_elemento(void *elemento)
{
	free(elemento);
}

void funcionalidad_lista_destruir_todo()
{
	lista_t *lista = lista_crear();
	int *elemento_1 = malloc(sizeof(int));
	*elemento_1 = 1;
	int *elemento_2 = malloc(sizeof(int));
	*elemento_2 = 2;

	lista_insertar(lista, elemento_1);
	lista_t *lista_pruebas = lista_insertar(lista, elemento_2);
	pa2m_afirmar(
		lista_pruebas != 0 &&
			lista->nodo_inicio->elemento == elemento_1 &&
			lista->nodo_final->elemento == elemento_2 &&
			lista->espacios == 2,
		"Inserción correcta de elementos que usan memoria en el heap en lista "
		"con 2 elementos int que ocupan memoria del stack.");

	lista_destruir_todo(lista, destruir_elemento);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Pruebas creación ========================");
	crear_lista_devuelve_lista_con_nodos_null_y_espacios_en_0();
	crea_lista_vacia();
	crea_pila_vacia();
	prueba_booleano_pila_vacia();
	crea_cola_vacia();
	prueba_booleano_cola_vacia();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas inserción elementos "
		"========================");
	inserta_elementos_en_lista();
	inserta_elementos_en_posicion_i_lista();
	apila_correctamente();
	encola_correctamente();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas eliminar elementos "
		"========================");
	quitar_elementos_en_lista();
	quitar_elemento_en_posicion_i_en_lista();
	desapila_correctamente();
	desencola_correctamente();

	pa2m_nuevo_grupo("\n======================== Pruebas iterador interno "
			 "========================");
	iterador_interno_en_lista();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas buscador elementos "
		"========================");
	buscar_elemento_en_lista();
	tope_pila_correcto();
	cola_primero_correcto();

	pa2m_nuevo_grupo("\n======================== Pruebas iterador externo "
			 "========================");
	iterador_externo_en_lista();

	pa2m_nuevo_grupo("\n======================== Prueba destruir todo "
			 "========================");
	funcionalidad_lista_destruir_todo();

	return pa2m_mostrar_reporte();
}
