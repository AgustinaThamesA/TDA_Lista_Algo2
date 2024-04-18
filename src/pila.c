#include "pila.h"
#include "lista.h"

typedef struct nodo {
  void *elemento;
  struct nodo *siguiente;
} nodo_t;

struct _pila_t {
  lista_t *lista;
};

struct lista {
  nodo_t *nodo_inicio;
  nodo_t *nodo_final;
  size_t espacios;
};

pila_t *pila_crear() {
  lista_t *lista = lista_crear();
  pila_t *pila = malloc(sizeof(pila_t));
  if (pila == NULL)
    return NULL;
  pila->lista = lista;
  return pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento) {
  if (pila == NULL)
    return NULL;
  pila->lista = lista_insertar(pila->lista, elemento);
  return pila;
}

void *pila_desapilar(pila_t *pila) {
  if (pila == NULL)
    return NULL;
  return lista_quitar(pila->lista);
}

void *pila_tope(pila_t *pila) {
  if (pila == NULL || pila->lista->espacios == 0)
    return NULL;
  return pila->lista->nodo_final->elemento;
}

size_t pila_tamanio(pila_t *pila) {
  if (pila == NULL || pila->lista->espacios == 0)
    return 0;
  return pila->lista->espacios;
}

bool pila_vacia(pila_t *pila) { return (pila_tamanio(pila) == 0); }

void pila_destruir(pila_t *pila) {
  if (pila == NULL)
    return;
  lista_destruir(pila->lista);
  free(pila);
}