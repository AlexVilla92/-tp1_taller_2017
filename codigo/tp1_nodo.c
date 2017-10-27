#include "tp1_nodo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo* Nodo_crearNodo(char *unaPal) {
	Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;
	if (unaPal != NULL) {
		int tam = strlen(unaPal); 
		nuevoNodo->texto = (char*)malloc(sizeof(char) * (tam + 1)); 
		nuevoNodo->texto[tam] = '\0';
		strncpy(nuevoNodo->texto,unaPal,tam);
		nuevoNodo->bits = tam;
	} 
	return nuevoNodo;
}

int Nodo_obtenerLong(Nodo *self) {
    return (self->bits);
}

void Nodo_setearLong(Nodo *self, int unDato) {
    self->bits = unDato;
}

void Nodo_destruirNodo(Nodo *self) {
	if (self != NULL) {
		self->izq = self->der = NULL;
		if (self->texto != NULL) {
			free(self->texto);
		}

		free(self);
	}
}

Nodo* Nodo_obtenerIzq(Nodo *self) {
	return (self->izq);
}

void Nodo_setearIzq(Nodo *self, Nodo* nuevoIzq) {
	self->izq = nuevoIzq;
}

Nodo* Nodo_obtenerDer(Nodo *self) {
	return (self->der);
}

void Nodo_setearDer(Nodo *self, Nodo* nuevoDer) {
	self->der = nuevoDer;
}

char* Nodo_obtenerString(Nodo *self) {
	return (self->texto);
}

void Nodo_setearString(Nodo *self, char *nuevoString) {
	free(self->texto);  
	if (nuevoString != NULL) {
		int tam = strlen(nuevoString); 
		self->texto = (char*)malloc(sizeof(char) * (tam + 1)); 
		self->texto[tam] = '\0';
		strncpy(self->texto,nuevoString,tam);
		Nodo_setearLong(self, tam);
	}
}

void Nodo_setearStringConMemoria(Nodo *self, char *nuevoString) {
	free(self->texto);
	int tam = strlen(nuevoString);
	self->texto = nuevoString;
	Nodo_setearLong(self, tam);
}

int Nodo_esHoja(Nodo *self) {
	int boolean = 0;
	if (self != NULL) {
		boolean = ((self->izq == NULL) && (self->der == NULL)) ? 1:0;
	}
	return boolean;
}

