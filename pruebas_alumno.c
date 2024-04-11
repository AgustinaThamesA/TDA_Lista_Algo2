#include "pa2m.h"
#include "src/lista.h"
#include <stdio.h>

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

void crear_lista_devuelve_lista_con_nodos_null_y_espacios_en_0(){
	lista_t* lista = lista_crear();
	pa2m_afirmar(
		lista->nodo_inicio == NULL && 
		lista->nodo_final == NULL && 
		lista->espacios == 0, 
		"Se crea una lista con nodos en NULL y espacios en 0.");

	lista_destruir(lista);
}

void crea_lista_vacia(){
	lista_t* lista = lista_crear();
	bool lista_esta_vacia = lista_vacia(NULL);
	pa2m_afirmar(lista_esta_vacia == true, "Lista NULL es una lista vacía.");

	lista_esta_vacia = lista_vacia(lista);
	pa2m_afirmar(lista_esta_vacia == true, "Lista creada no tiene elementos (vacía).");

	lista_insertar(lista, "prueba_vacia1");
	lista_insertar(lista, "prueba_vacia2");
	lista_esta_vacia = lista_vacia(lista);
	pa2m_afirmar(lista_esta_vacia == false, "Lista con elementos no está vacía.");

	lista_destruir(lista);
}

void inserta_elementos_en_lista(){
	lista_t* lista = lista_crear();
	char* prueba_1 = "prueba elemento 1";
	char* prueba_2 = "prueba elemento 2";

	lista_t* lista_con_elementos = lista_insertar(NULL, prueba_1);
	pa2m_afirmar(lista_con_elementos == NULL, "No inserta un elemento en una lista NULL.");



	lista_destruir(lista);

	lista = lista_crear();
	lista_insertar(lista, prueba_1);
	lista_con_elementos = lista_insertar(lista, prueba_2);
	pa2m_afirmar(lista_con_elementos == 0 && 
		lista->nodo_inicio->elemento == prueba_1 && 
		lista->nodo_final->elemento == prueba_2 && 
		lista->espacios == 2, 
		"Inserción correcta de elementos en lista vacía.");


	lista_destruir(lista);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Pruebas creación ========================");
	crear_lista_devuelve_lista_con_nodos_null_y_espacios_en_0();
	crea_lista_vacia();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas inserción elementos ========================");
	inserta_elementos_en_lista();

	return pa2m_mostrar_reporte();
}
