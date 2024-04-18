#include "cola.h"
#include "lista.h"

typedef struct nodo {
  void *elemento;
  struct nodo *siguiente;
} nodo_t;

struct _cola_t {
  lista_t *lista;
};

struct lista {
  nodo_t *nodo_inicio;
  nodo_t *nodo_final;
  size_t espacios;
};

cola_t *cola_crear() {
  lista_t *lista = lista_crear();
  cola_t *cola = malloc(sizeof(cola_t));
  if (cola == NULL)
    return NULL;
  cola->lista = lista;
  return cola;
}

cola_t *cola_encolar(cola_t *cola, void *elemento) {
  if (cola == NULL)
    return NULL;
  cola->lista = lista_insertar(cola->lista, elemento);
  return cola;
}

void *cola_desencolar(cola_t *cola) {
  if (cola == NULL || cola_tamanio(cola) == 0)
    return NULL;
  return lista_quitar_de_posicion(cola->lista, 0);
}

void *cola_frente(cola_t *cola) {
  if (cola == NULL || cola_tamanio(cola) == 0)
    return NULL;
  return cola->lista->nodo_inicio->elemento;
}

size_t cola_tamanio(cola_t *cola) {
  if (cola == NULL || cola->lista->espacios == 0)
    return 0;
  return cola->lista->espacios;
}

bool cola_vacia(cola_t *cola) { return (cola_tamanio(cola) == 0); }

void cola_destruir(cola_t *cola) {
  if (cola == NULL) {
    return;
  }
  lista_destruir(cola->lista);
  free(cola);
}