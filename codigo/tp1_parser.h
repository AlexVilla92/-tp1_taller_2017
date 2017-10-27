#ifndef TP1_PARSER_H_INCLUDED
#define TP1_PARSER_H_INCLUDED
#include "tp1_socket.h"
#include "tp1_rope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAL 100
#define MAX_OPE 20

/*
 *Pre: Recibe como minimo 4 parametros, pero pueden 
 *     ser 5.
 *Pos: Obtiene los datos desde el archivo o desde
 *     la entrada estandar y se los envia al server, 
 *     usando la interface de sockets, para que este 
 *     ejecute las operaciones sobre la estructura rope
 *     y asi poder modificar el documento de texto.
 */
int Parser_cliente(int argc, char *argv[]);
/*
 *Pre: Recibe 3 parametros validos.
 *Pos: Recibe datos del cliente y ejecuta las
 *     operaciones correspondientes sobre la estructura
 *     rope, para modificar el documento de texto.
 */ 
int Parser_server(int argc, char *argv[]);

#endif

