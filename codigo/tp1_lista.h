#ifndef TP1_LISTA_H_INCLUDED
#define TP1_LISTA_H_INCLUDED

#include "tp1_nodoLista.h"

/* Estructuras. */
struct lista {
	//Puntero al primer elemento de la lista
	nodoLista *primero; //private
	//Tamaño de la lista
	int tam;			//private
};

typedef struct lista Lista;

/* Constructor y destructor. */

/*
 *Pos: Crea una lista, inicializa
 *	   sus valores y la devuelve.
 */	
Lista* Lista_crearLista();
/*
 *Pre: Recibe una lista valida.
 *Pos: Libera los recursos de la lista,
 *	   y luego la destruye.
 */
void Lista_destruirLista(Lista *self);

/* Operaciones. */

/*
 *Pre: Recibe una lista valida, no nula.
 *Pos: Si la lista esta vacia, devuelve 
 *	   uno, caso contrario cero.
 */
int Lista_estaVacia(Lista *self);
/*
 *Pre: Recibe una lista valida.
 *Pos: Devuelve la cantidad de elementos
 *	   que tiene la lista.
 */
int Lista_obtenerTamanio(Lista *self);
/*
 *Pre: Se debe recibir una lista valida no null,
 *     y un puntero(dato) a Nodo valido.
 *Pos: Inserta un nodoLista al final de la lista,
 *     con el dato contenido dentro del nodoLista.
 */
void Lista_insertar(Lista *self, Nodo *unDato);
/*
 *Pre: Se recibe una posicion valida, y una lista valida.
 *Pos: Devuelve el dato que contiene el nodo de la posicion 
 *     'pos' de la lista.
 */
Nodo* Lista_obtenerDato(Lista *self, int pos);

#endif
