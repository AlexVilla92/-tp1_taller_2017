#ifndef TP1_NODOLISTA_H_INCLUDED
#define TP1_NODOLISTA_H_INCLUDED

#include "tp1_nodo.h"

/* Estructuras. */
struct tNodoLista {
	//Dato almacenado en el nodoLista,
	//Es un puntero a Nodo
	Nodo *dato;				//private
	//Puntero al siguiente nodo de la lista
	struct tNodoLista *sig;  //private
};

typedef struct tNodoLista nodoLista;

/* Constructor y destructor. */

/*
 *Pre: Recibe un puntero a nodo valido.
 *Pos: Crea un nodoLista, inicializa sus 
 *     valores y lo devuelve.
 */	   
nodoLista* nodoLista_crearNodo(Nodo *unDato);
/*
 *Pre: Recibe un puntero a nodoLista valido.
 *Pos: Libera todos los recursos del nodoLista,
 *	   pasado por parametro y posteriormente
 *	   lo destruye.
 */	
void nodoLista_destruirNodo(nodoLista *self); 

/* Operaciones. */

/*
 *Pre: Recibe un puntero a nodoLista valido.
 *Pos: Devuelve el dato contenido en el nodoLista
 *     pasado por parametro.
 */
Nodo* nodoLista_obtenerDato(nodoLista *self);
/*
 *Pre: Recibe un puntero a nodoLista valido, no null
 *	   y un puntero a Nodo, valido tambien.
 *Pos: Setea al dato contenido en self, con el valor de
 *	   nuevoDato.
 */ 
void nodoLista_setearDato(nodoLista *self, Nodo *nuevoDato);
/*
 *Pre: Recibe un puntero a nodoLista valido.
 *Pos: Devuelve un puntero al siguiente nodo 
 *	   en la lista.
 */
nodoLista* nodoLista_obtenerSig(nodoLista *self);
/*
 *Pre: Recibe dos punteros a nodoLista validos no null,
 *Pos: Setea la referencia al siguiente elemento de la lista.
 */	 
void nodoLista_setearSig(nodoLista *self, nodoLista *nuevoSig);

#endif
