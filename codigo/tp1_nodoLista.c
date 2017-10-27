#include "tp1_nodoLista.h"
#include <stdlib.h>

nodoLista* nodoLista_crearNodo(Nodo *unDato) {
	nodoLista* nuevoNodo = (nodoLista*)malloc(sizeof(nodoLista));
	nuevoNodo->dato = unDato;
	nuevoNodo->sig = NULL;
	
	return nuevoNodo;
}

void nodoLista_destruirNodo(nodoLista *self) {
	if (self != NULL) {
		self->dato = NULL;
		self->sig = NULL;
		free(self);
	}
}

Nodo* nodoLista_obtenerDato(nodoLista *self) {
	return (self->dato);
}

void nodoLista_setearDato(nodoLista *self, Nodo* nuevoDato) {
	self->dato = nuevoDato;
}

nodoLista* nodoLista_obtenerSig(nodoLista *self) {
	return (self->sig);
}

void nodoLista_setearSig(nodoLista *self, nodoLista *nuevoSig) {
	self->sig = nuevoSig;
}
