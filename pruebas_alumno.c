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

	lista_t* lista_pruebas = lista_insertar(NULL, prueba_1);
	pa2m_afirmar(lista_pruebas == NULL, "No inserta un elemento en una lista NULL.");

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

void inserta_elementos_en_posicion_i_lista(){
	lista_t* lista = lista_crear();
	char* prueba_1 = "prueba elemento 1";
	char* prueba_2 = "prueba elemento 2";
	char* prueba_2_1 = "prueba elemento 2.1";
	char* prueba_3 = "prueba elemento 3";
	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);
	lista_insertar(lista, prueba_3);
	lista_t* lista_pruebas = lista_insertar_en_posicion(lista, prueba_2_1, 0);

	pa2m_afirmar(lista_pruebas != NULL &&
		lista->nodo_inicio->elemento == prueba_2_1 &&
		lista_elemento_en_posicion(lista, 1) == prueba_1 &&
		lista_elemento_en_posicion(lista, 2) == prueba_2 &&
		lista_elemento_en_posicion(lista, 3) == prueba_3 &&
		lista->nodo_final->elemento == prueba_3 &&
		lista->espacios == 4, 
		"Se inserta un elemento correctamente en la posicion 0 de una lista no vacía.");


	lista_destruir(lista);
}

void quitar_elementos_en_lista(){
	lista_t* lista = lista_crear();
	char* prueba_1 = "prueba elemento 1";
	char* prueba_2 = "prueba elemento 2";

	lista_t* lista_pruebas = lista_quitar(NULL);
	pa2m_afirmar(lista_pruebas == NULL, "No se puede usar lista_quitar para una lista NULL.");

	lista_pruebas = lista_quitar(lista);
	pa2m_afirmar(lista_pruebas == NULL, "No se puede usar lista_quitar para una lista vacía.");

	lista_insertar(lista, prueba_1);
	lista_pruebas = lista_quitar(lista);
	pa2m_afirmar(lista_pruebas != NULL &&
		lista->nodo_inicio == NULL &&
		lista->nodo_final == NULL &&
		lista->espacios == 0, 
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

void quitar_elemento_en_posicion_i_en_lista(){
	lista_t* lista = lista_crear();
	char* prueba_1 = "prueba elemento 1";
	char* prueba_2 = "prueba elemento 2";

	lista_t* lista_pruebas = lista_quitar_de_posicion(NULL, 0);
	pa2m_afirmar(lista_pruebas == NULL, "No se puede usar lista_quitar_de_posicion para una lista NULL.");

	lista_pruebas = lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(lista_pruebas == NULL, "No se puede usar lista_quitar_de_posicion para una lista vacía.");

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
		"No se borra el elemento de la lista ya que se pasa una posición que no existe.");
	
	lista_destruir(lista);
}

bool mostrar_para_prueba_iterador_interno(void* elemento, void* contador){
    if(elemento && contador)
        (*(int*)contador)++;
    return true;
}

void iterador_interno_en_lista() {
	lista_t *lista = lista_crear();
	int cant_elementos_iterados = 0;
	char *prueba_1 = "prueba elemento 1";
	char *prueba_2 = "prueba elemento 2";

	// Prueba 1: Validar comportamiento cuando la función no existe
	size_t cantidad = lista_con_cada_elemento(NULL, mostrar_para_prueba_iterador_interno, &cant_elementos_iterados);
	pa2m_afirmar(cantidad == 0 && cant_elementos_iterados == 0, "Iterador interno con función NULL");

	// Prueba 2: Validar comportamiento con función NULL en la lista
	cantidad = lista_con_cada_elemento(lista, NULL, &cant_elementos_iterados);
	pa2m_afirmar(cantidad == 0 && cant_elementos_iterados == 0, "Iterador interno con función NULL en lista");

	// Prueba 3: Validar comportamiento con lista vacía
	cantidad = lista_con_cada_elemento(lista, mostrar_para_prueba_iterador_interno, &cant_elementos_iterados);
	pa2m_afirmar(cantidad == 0 && cant_elementos_iterados == 0, "Iterador interno con lista vacía");

	// Insertar elementos en la lista
	lista_insertar(lista, prueba_1);
	lista_insertar(lista, prueba_2);

	// Prueba 4: Validar iteración sobre lista con elementos
	cantidad = lista_con_cada_elemento(lista, mostrar_para_prueba_iterador_interno, &cant_elementos_iterados);
	pa2m_afirmar(cantidad == 2 && cant_elementos_iterados == 2, "Iterador interno con lista no vacía");

	// Prueba 5: Validar iteración sobre lista con elementos, contexto NULL
	cantidad = lista_con_cada_elemento(lista, mostrar_para_prueba_iterador_interno, NULL);
	pa2m_afirmar(cantidad == 2 && cant_elementos_iterados == 0, "Iterador interno con lista no vacía, contexto NULL");

	// Destruir la lista
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
	inserta_elementos_en_posicion_i_lista();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas eliminar elementos ========================");
	quitar_elementos_en_lista();
	quitar_elemento_en_posicion_i_en_lista();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas iterador interno ========================");
	iterador_interno_en_lista();

	return pa2m_mostrar_reporte();
}
