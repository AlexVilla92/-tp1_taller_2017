#include "tp1_lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lista* Lista_crearLista() {
	Lista *unaLista = (Lista*)malloc(sizeof(Lista));
	unaLista->primero = NULL;
	unaLista->tam = 0;

	return unaLista;
}

void Lista_destruirLista(Lista *self) {
	if (self != NULL) {
		while (self->primero != NULL) {
			nodoLista *borro = self->primero;
			self->primero = nodoLista_obtenerSig(self->primero);
			nodoLista_destruirNodo(borro);
			self->tam--;
		}
		free(self);
	}
}

int Lista_estaVacia(Lista *self) {
	return (self->tam == 0);
}

int Lista_obtenerTamanio(Lista *self) {
	return (self->tam);
}

void Lista_insertar(Lista *self, Nodo *unDato) {
	nodoLista *nuevoNodo = nodoLista_crearNodo(unDato);
	nodoLista *nodoAux = self->primero;

	if (Lista_estaVacia(self)) {
		self->primero = nuevoNodo;

	} else {
		while (nodoLista_obtenerSig(nodoAux)) {
			nodoAux = nodoLista_obtenerSig(nodoAux);
		}
		nodoLista_setearSig(nodoAux,nuevoNodo);
	}
	self->tam++; 
}

Nodo* Lista_obtenerDato(Lista *self, int pos) {
	nodoLista *aux = self->primero;
	int i = 1;

	while ((i < pos) && (nodoLista_obtenerSig(aux))) {
		aux = nodoLista_obtenerSig(aux);
		i++;
	}
	return (nodoLista_obtenerDato(aux));
}
