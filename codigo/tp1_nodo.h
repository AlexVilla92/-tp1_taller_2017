#ifndef TP1_NODO_H_INCLUDED
#define TP1_NODO_H_INCLUDED

#define MAX_CARACTER 30
#define CARACTER_VACIO ""

/* Estructuras. */
struct tNodo {
	//Longitud de la palabra almacenada en el nodo
    int bits;                //private
    //Texto almacenada en el nodo
    char *texto; 			 //private
    //Punteros a los nodos hijos
    struct tNodo *izq, *der; // private
};

typedef struct tNodo Nodo;

/*
 *Constructor y destructor. 
 *Pre: Recibe una palabra valida, no null.
 *Pos: Crea un nodo, inicializa sus atributos,
 * 	   y lo devuelve listo para ser utilizado.
 */
Nodo* Nodo_crearNodo(char *unaPal);
/*
 *Pre: Recibe un nodo valido, no null.
 *Pos: Libera todos los recursos del nodo,
 *	   y luego lo destruye. 
 */
void Nodo_destruirNodo(Nodo *self);
/*
 * Queries.
 *Pre: Recibe un puntero a nodo valido, no null.
 *Pos: Devuelve verdadero(valor 1) si el nodo
 *	   no tiene hijos, falso(valor 0) en caso
 *	   contrario.	
 */
int Nodo_esHoja(Nodo *self);
/* 
 * Getters y Setters
 * Pre: Recibe un puntero a nodo valido, no null.
 * Pos: Devuelve la longitud de la palabra,
 *		que esta almacenada en el nodo.
 */
int Nodo_obtenerLong(Nodo *self);
/*
 * Pre: Recibe un puntero a nodo valido 
 		y un entero >= 0.
 * Pos: Modifica el valor de la longitud, de la 
 *      palabra contenida en el nodo.
 */
void Nodo_setearLong(Nodo *self, int unDato);
/*
 * Pre: Recibe un puntero a nodo valido, no null.
 * Pos: Devuelve un puntero al nodo hijo,
 *		izquierdo.
 */
Nodo* Nodo_obtenerIzq(Nodo *self);
/*
 * Pre: Recibe dos punteros a nodos, self es no null
 * Pos: Se asigna una nueva referencia al nodo hijo
 *      izquierdo.
 */
void Nodo_setearIzq(Nodo *self,  Nodo* nuevoIzq);
/*
 * Pre: Recibe un puntero a nodo valido, no null
 * Pos: Devuelve un puntero al nodo hijo derecho
 */
Nodo* Nodo_obtenerDer(Nodo *self);
/*
 * Pre: Recibe dos punteros a nodos, self es no null
 * Pos: Se asigna una nueva referencia al nodo hijo
 *      derecho.
 */
void Nodo_setearDer(Nodo *self, Nodo* nuevoDer);
/*
 * Pre: Recibe un puntero a nodo valido, no null
 * Pos: Devuelve la palabra que se encuentra
 *      almacenada en el nodo.
 */
char* Nodo_obtenerString(Nodo *self);
/*
 * Pre: Recibe un puntero a nodo valido, no null
 *		y un puntero a una nueva cadena de caracteres
 * Pos: Se cambia el contenido de la palabra contenida
 *      en el nodo.
 */
void Nodo_setearString(Nodo *self, char *nuevoString);
/*
 * Pre: Recibe un puntero a nodo valido, no null
 *		y un puntero a una nueva cadena de caracteres,
 *		creada con memoria dinamica.
 * Pos: Se cambia el contenido de la palabra contenida
 *      en el nodo.
 */
void Nodo_setearStringConMemoria(Nodo *self, char *nuevoString);

#endif 
