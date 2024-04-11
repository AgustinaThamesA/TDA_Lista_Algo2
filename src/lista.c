#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

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

lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL){
		return NULL;
	}
	lista->nodo_inicio = NULL;
	lista->nodo_final = NULL;
	lista->espacios = 0;

	return lista;
}

nodo_t* nuevo_nodo(void* elemento){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(nodo == NULL)
		return NULL;
	
	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	return nodo;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if(lista == NULL)
		return NULL;
	nodo_t* nodo = nuevo_nodo(elemento);

	if (nodo == NULL)
		return NULL;

	if(lista->espacios == 0){
		lista->nodo_inicio = nodo;
		lista->nodo_final = nodo;
		lista->espacios = 1;
		return lista;
	}

	lista->nodo_final->siguiente = nodo;
	lista->nodo_final = nodo;
	(lista->espacios)+=1;

	return lista;
}

nodo_t* lista_nodo_en_posicion(lista_t* lista, size_t posicion){
	if (lista == NULL || lista->espacios == 0)
		return NULL;
	
	nodo_t* nodo = lista->nodo_inicio;
	int i = 0;

	while (i < posicion && i < (lista->espacios) && nodo->siguiente){
		nodo = nodo->siguiente;
		i++;
	}

	if (i == posicion)
		return nodo;
	
	return NULL;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (lista == NULL)
		return NULL;
	
	if (lista->espacios == 0 || posicion >= (lista->espacios))
		return lista_insertar(lista, elemento);
	
	nodo_t* nodo = nuevo_nodo(elemento);

	if (nodo == NULL)
		return NULL;
	
	if (posicion == 0){
		nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo;
	} else {
		nodo_t* nodo_anterior;
		nodo_anterior = lista_nodo_en_posicion(lista, posicion - 1);
		nodo->siguiente = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nodo;
	}
	
	(lista->espacios)++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	return NULL;
}

void *lista_ultimo(lista_t *lista)
{
	return NULL;
}

bool lista_vacia(lista_t *lista)
{
	return lista == false || lista->espacios == 0;
}

size_t lista_tamanio(lista_t *lista)
{
	return 0;
}

void lista_destruir_nodos(nodo_t* nodo){
	if (nodo){
		lista_destruir_nodos(nodo->siguiente);
		free(nodo);
	}
}

void lista_destruir(lista_t *lista)
{
	if(lista){
		lista_destruir_nodos(lista->nodo_inicio);
		free(lista);
	}
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
