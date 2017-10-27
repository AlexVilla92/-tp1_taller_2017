#ifndef TP1_ROPE_H
#define TP1_ROPE_H

#include "tp1_nodo.h"
#include "tp1_lista.h"
#define INSERT_IZQ 'i'
#define INSERT_DER 'd'

/* Estructuras. */
typedef struct rope {
	//Raiz del arbol
    Nodo* raiz;			//private
    //Valor de la raiz
    int valorRaiz;		//private
} Rope;

/* Constructor y destructor. */

/*
 *Pos: Crea un arbol rope, lo inicializa
 *	   y lo devuelve.
 */ 	
Rope* Rope_crearRope();
/*
 *Pre: Recibe un arbol rope valido.
 *Pos: Libera los recursos de dicho arbol,
 *	   y posteriormente lo destruye.
 */
void Rope_destruirRope(Rope* unArbol);

/* Operaciones. */

/*
 *Pre: Recibe dos arboles validos, sino devuelve null
 *Pos: Devuelve un nuevo arbol, que es la union
 *     de los otros dos, y ademas destruye y libera 
 *     la memoria de los 2 arboles recibidos.	
 */	   
Rope* Rope_concat(Rope* rope1, Rope* rope2);
/*
 *Pre: Debe recibir un arbol valido, cuya raiz no sea nula,
 *     y una posicion valida para el string,caso contrario 
 *     devuelve null.
 *Pos: Hace un split en el arbol pasado por parametro,
 *     segun la posicion 'pos', y devuelve un arbol nuevo
 *     que es una parte del split. El arbol original(parametro)
 *     tambien es modificado, ya que contiene la otra parte del 
 *     split.
 */
Rope* Rope_split(Rope *self, int pos);
/*
 *Pre: Recibe un arbol no null, una posicion valida
 *     para el arbol, y un texto no null.
 *Pos: Inserta el texto en la posicion del arbol,
 *     indicada por 'pos'.
 */
void Rope_insertar(Rope *self, int pos, char *unaPal);
/*
 *Pre: Recibe un arbol no null, y dos posiciones validas
 *     para el arbol.
 *Pos: Elimina del arbol, el texto que se encuentra
 *     entre las posciones indicadas.
 */
void Rope_delete(Rope *self, int posIn, int posFin);
/*
 *Pos: Debe recibir un arbol Rope con raiz no nula. 
 *Pre: Devuelve la palabra contenida en el arbol rope,
 *	   pero se debe liberar el puntero a char que devuelve 
 *     la funcion, en el contexto que se la invoque.
 */
char* Rope_obtenerPalabra(Rope *self);

#endif
