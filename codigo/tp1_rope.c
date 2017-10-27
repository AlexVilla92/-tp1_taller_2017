#include "tp1_rope.h"
#include "tp1_lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Firma de metodos privados
static Nodo* Rope_splitNodoHoja(Nodo *unaRaiz, int pos); 

static void Rope_recursivaPalabra(Nodo *unaRaiz, char* palabra);

static void Rope_splitRecursivo(Nodo *unaRaiz, Lista *unaLista, int pos);

static Rope* Rope_construirArbolSpliteado(Lista *unaLista);

static Rope* Rope_concatIterativo(Lista *unaLista, int tam);

static int Rope_recalcularPesosNodos(Nodo *unaRaiz);

static void Rope_concatenoPal(Nodo *unaRaiz, char *unaPal, char modo);

static void Rope_insertarAizq(Nodo *unaRaiz, char *unaPal);

static void Rope_insertarAder(Nodo *unaRaiz, char *unaPal);

static int Rope_obtenerTamanioPalabra(Nodo *unaRaiz);

static void Rope_destructorRecursivo(Nodo* unaRaiz); 

static void Rope_setValorRaiz(Rope *unRope, int nuevoValor);

//Implementacion de metodos
Rope* Rope_crearRope() {
	Rope* unRope = (Rope*)malloc(sizeof(Rope));
	unRope->raiz = NULL;
	unRope->valorRaiz = 0;
	return unRope;
}

void Rope_destruirRope(Rope *self) {
	if (self != NULL) {
		Rope_destructorRecursivo(self->raiz);
		free(self);
	}
}

static void Rope_destructorRecursivo(Nodo* unaRaiz) {
	if (unaRaiz == NULL) {
		return;
	}
	Rope_destructorRecursivo(unaRaiz->izq);
	Rope_destructorRecursivo(unaRaiz->der);
	Nodo_destruirNodo(unaRaiz);
}

Rope* Rope_concat(Rope* rope1, Rope* rope2) {
	if ((rope1 == NULL) || (rope2 == NULL)) {
		return NULL;
	}

	Rope* ropeUnion = Rope_crearRope();   
	Nodo* nodoUnion = Nodo_crearNodo(CARACTER_VACIO);

	ropeUnion->raiz = nodoUnion;
	ropeUnion->raiz->izq = rope1->raiz;   
	ropeUnion->raiz->der = rope2->raiz;   
	rope1->raiz = ropeUnion->raiz;
	ropeUnion->raiz = rope2->raiz = NULL;  
	     
	Rope_destruirRope(ropeUnion);
	Rope_destruirRope(rope2);
	int valor= Rope_recalcularPesosNodos(rope1->raiz);
	Rope_setValorRaiz(rope1,valor);
	return rope1;
}

void Rope_insertar(Rope* self, int pos, char *unaPal) { 
	int tam = Rope_obtenerTamanioPalabra(self->raiz);
	if (unaPal == NULL) { 
		return;  
	}
	if (pos < 0) { 
		pos = tam + 1 + pos;
	}
	int longitud;
	if (self->raiz == NULL) { 
		Nodo *unNodo = Nodo_crearNodo(unaPal);
		self->raiz = unNodo;
		return; 
	} else if (pos == 0) { 
		Rope_insertarAizq(self->raiz,unaPal);
		longitud = Rope_recalcularPesosNodos(self->raiz);
		Rope_setValorRaiz(self,longitud);
		return;
	} else if (pos == tam) {
		Rope_insertarAder(self->raiz,unaPal);
		longitud = Rope_recalcularPesosNodos(self->raiz);
		Rope_setValorRaiz(self,longitud);
		return;
	}
	Nodo *unNodo = Nodo_crearNodo(unaPal);
	Rope *t = Rope_crearRope();
	t->raiz = unNodo;
	Rope *r = Rope_split(self,pos);
	self = Rope_concat(self,t);
	self = Rope_concat(self,r);  
	return;
}

static void Rope_insertarAizq(Nodo *unaRaiz, char *unaPal) {
	if (Nodo_esHoja(unaRaiz)) {
		Rope_concatenoPal(unaRaiz, unaPal,INSERT_IZQ);
		return;
	} 
	Nodo *unaRama = Nodo_obtenerIzq(unaRaiz);

	if (unaRama != NULL) {
		Rope_insertarAizq(unaRama,unaPal);
		return;

	} else {
		unaRama = Nodo_obtenerDer(unaRaiz);
		Rope_insertarAizq(unaRama,unaPal);
		return;
	}
}

static void Rope_insertarAder(Nodo *unaRaiz, char *unaPal) {
	if (Nodo_esHoja(unaRaiz)) {
		Rope_concatenoPal(unaRaiz, unaPal,INSERT_DER);
		return;
	} 
	Nodo *unaRama = Nodo_obtenerDer(unaRaiz);

	if (unaRama != NULL) {
		Rope_insertarAder(unaRama,unaPal);
		return;

	} else {
		unaRama = Nodo_obtenerIzq(unaRaiz);
		Rope_insertarAder(unaRama,unaPal);
		return;
	}
}

void Rope_delete(Rope *self, int posIn, int posFin) {
	if (self->raiz == NULL)  {
		return;
	}
	int tam = Rope_obtenerTamanioPalabra(self->raiz);
	if (posFin == -1) {
		posFin = tam;
		
	} else if (posFin < 0) {
		posFin = tam + posFin;
		if (posIn < 0) {
			posIn = tam + posIn;
		}
	} 
	if (posIn < 0) {
		posIn = tam + posIn + 1;
	}
	Rope *borro = Rope_split(self, posIn);
	posIn = posFin - posIn;
	if (!((posFin == tam) && (posFin != 0))) {
		if (posIn < tam) {
			Rope *resto = Rope_split(borro, posIn);
			self = Rope_concat(self, resto);
		}
	} 
	Rope_destruirRope(borro);
}

Rope* Rope_split(Rope *self, int pos) { 
	if (self->raiz == NULL) { 
		return NULL; 
	}
	Lista *unaLista = Lista_crearLista(); 
	Rope_splitRecursivo(self->raiz,unaLista,pos);
	Rope *nuevoRope = Rope_construirArbolSpliteado(unaLista);
	int valorRaiz1 = Rope_recalcularPesosNodos(self->raiz);
	int valorRaiz2 = Rope_recalcularPesosNodos(nuevoRope->raiz);
	Rope_setValorRaiz(self,valorRaiz1);
	Rope_setValorRaiz(nuevoRope,valorRaiz2);
	Lista_destruirLista(unaLista);

	return nuevoRope;
}

static Rope* Rope_construirArbolSpliteado(Lista *unaLista) {
	int tam = Lista_obtenerTamanio(unaLista);
	if (tam == 1) {
		Rope *unRope = Rope_crearRope();
		Nodo *unNodo = Lista_obtenerDato(unaLista,tam);
		unRope->raiz = unNodo; 
		return unRope;
	} 

	if (tam == 2) {
		Nodo *nodoIzq = Lista_obtenerDato(unaLista,tam-1);
		Nodo *nodoDer = Lista_obtenerDato(unaLista,tam);
		Rope *unRope = Rope_crearRope();
		Rope *otroRope = Rope_crearRope();
		unRope->raiz = nodoIzq;
		otroRope->raiz = nodoDer;
		Rope *ropeUnion = Rope_concat(unRope, otroRope);
		return ropeUnion;

	} else { 
		Rope *unRope = Rope_concatIterativo(unaLista, tam);
		return unRope;
	}
}

static Rope* Rope_concatIterativo(Lista *unaLista, int tam) {
	Nodo *unaRama = Lista_obtenerDato(unaLista,tam);
	Rope *unRope = Rope_crearRope();
	unRope->raiz = unaRama;
	tam = tam - 1;
	Rope *rope1 = NULL;
	Rope *rope2 = NULL; 
	Rope *ropeUnion = NULL;

	for (int i = 1; i <= tam; i++) {
		unaRama = Lista_obtenerDato(unaLista,i);
		if (ropeUnion != NULL) {
			rope1 = Rope_crearRope();
			rope1->raiz = unaRama;
			ropeUnion = Rope_concat(ropeUnion,rope1);
			rope1 = NULL;
		} else if (rope1 == NULL) {
			rope1 = Rope_crearRope();
			rope1->raiz = unaRama;
		} else {
			rope2 = Rope_crearRope();
			rope2->raiz = unaRama;
			ropeUnion = Rope_concat(rope1, rope2);
			rope1 = rope2 = NULL;
		} 
	}
	Rope *ropeFinal = Rope_concat(ropeUnion,unRope);
	return ropeFinal;
}

static void Rope_splitRecursivo(Nodo *unaRaiz, Lista *unaLista, int pos) {
	int longitud = Nodo_obtenerLong(unaRaiz);

	if (pos == longitud) { 
		Nodo *ramaDer = Nodo_obtenerDer(unaRaiz);
		if (ramaDer != NULL) {
			Lista_insertar(unaLista,ramaDer);
			Nodo_setearDer(unaRaiz,NULL);
		}
		return;
	} 

	if (pos < longitud) {
		if (Nodo_esHoja(unaRaiz)) {
	 		Nodo *unNodo = Rope_splitNodoHoja(unaRaiz,pos);
	 		Lista_insertar(unaLista,unNodo);

	 	} else {
	 		Rope_splitRecursivo(Nodo_obtenerIzq(unaRaiz),unaLista,pos);
	 		Nodo *otraRama = Nodo_obtenerDer(unaRaiz);
	 		if (otraRama != NULL) {
	 			Lista_insertar(unaLista,otraRama);
				Nodo_setearDer(unaRaiz,NULL);
	 		}
	 	}
	 	return;

	} else {
		if (Nodo_esHoja(unaRaiz)) {
			Nodo *otroNodo = Rope_splitNodoHoja(unaRaiz,pos);
			Lista_insertar(unaLista,otroNodo);
			return;
		}
		pos = pos - longitud; 
		Rope_splitRecursivo(Nodo_obtenerDer(unaRaiz),unaLista,pos);
		return;
	}
}

static Nodo* Rope_splitNodoHoja(Nodo *unaRaiz, int pos) {
	char *pal = Nodo_obtenerString(unaRaiz); 
	char *string1 = (char*)malloc(sizeof(char)*(pos+1));
	string1[pos] = '\0';
	strncpy(string1, pal, pos);
	char *string2 = pal + pos;              
    Nodo *unNodo = Nodo_crearNodo(string2);
	Nodo_setearStringConMemoria(unaRaiz,string1);

	return unNodo;
}

static int Rope_recalcularPesosNodos(Nodo *unaRaiz) {
	int peso = 0;

	if (unaRaiz != NULL) {
		if (Nodo_esHoja(unaRaiz)) {
			return (Nodo_obtenerLong(unaRaiz));

		} else {
			peso += Rope_recalcularPesosNodos(Nodo_obtenerIzq(unaRaiz));
			Nodo_setearLong(unaRaiz,peso);
			if (Nodo_obtenerDer(unaRaiz) != NULL) {
				peso += Rope_recalcularPesosNodos(Nodo_obtenerDer(unaRaiz));
			}
			return peso;
		}
	}
	return peso;
}

static int Rope_obtenerTamanioPalabra(Nodo *unaRaiz) {
	int tam = 0;
	
	if (unaRaiz == NULL) {
		return 0;
	} 

	if (Nodo_esHoja(unaRaiz)) {
		return (Nodo_obtenerLong(unaRaiz));
	}

	tam += Rope_obtenerTamanioPalabra(unaRaiz->izq); 
	tam += Rope_obtenerTamanioPalabra(unaRaiz->der);

	return tam;
}


char* Rope_obtenerPalabra(Rope *self) { 									
	if (self->raiz == NULL) {
		return NULL;
	} 
	
	int tam = Rope_obtenerTamanioPalabra(self->raiz);
	char *palabra = (char *) malloc(tam + 1);
	palabra[0] = '\0';
	Rope_recursivaPalabra(self->raiz, palabra);
	return palabra; 
}

static void Rope_recursivaPalabra(Nodo *unaRaiz, char* palabra) {
	if (Nodo_esHoja(unaRaiz)) {
		char *texto = Nodo_obtenerString(unaRaiz);
		const size_t tam = strlen(texto);
		strncat(palabra,texto,tam);
		return;
	}
	if (unaRaiz->izq != NULL) {
		Rope_recursivaPalabra(unaRaiz->izq, palabra);
	}
	if (unaRaiz->der != NULL) {
		Rope_recursivaPalabra(unaRaiz->der, palabra);
	}
	return;
}

static void Rope_concatenoPal(Nodo *unaRaiz, char *unaPal, char modo) {
    int tam1 = strlen(unaPal);
    char *texto = Nodo_obtenerString(unaRaiz); 
    int tam2 = strlen(texto);
    int tam = tam1+tam2;
    char *palabra = (char*)malloc(tam+1);
    palabra[0] = '\0';
    if (modo == INSERT_IZQ) {
    	strncat(palabra,unaPal,tam1);
   		strncat(palabra,texto,tam2);
    } else {
    	strncat(palabra,texto,tam2);
    	strncat(palabra,unaPal,tam1);
    }
    Nodo_setearStringConMemoria(unaRaiz,palabra);
    return;
}

static void Rope_setValorRaiz(Rope *unRope, int nuevoValor) {
	unRope->valorRaiz = nuevoValor;
}
