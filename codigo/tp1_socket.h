#ifndef TP1_SOCKET_H_INCLUDED
#define TP1_SOCKET_H_INCLUDED

#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#define ERROR -1
#define EXITO 0

typedef struct {
	int socket; //socket file descriptor
} socket_t;

/*
 *Pre: Self apunta a un sector válido de memoria. 
 *Pos: Crea e inicializa una estructura socket, 
 *	   y devuelve el valor del file descriptor,
 *     en caso de error se devuelve -1.
 */
int socket_create(socket_t *self);
/*
 *Pre: Se recibe un socket valido ya inicializado.
 *Pos: Libera los recursos del socket self, y luego
 *     lo destruye.
 */
int socket_destroy(socket_t *self);
/*
 *Pre: Se recibe un socket valido, 
 *	   que apunta a una direccion de memoria.
 *Pos: Se enlaza al socket a una direccion IP,
 *     y a un puerto. Ademas se establece un 
 *     maximo de conexiones y se deja el socket
 *     en estado de espera a que alguien se conecte,
 *	   en caso de error se devuelve -1, si todo
 *     salio bien se devuelve 0.
 */
int socket_bind_and_listen(socket_t *self, unsigned short port);
/*
 *Pre: Se recibe un socket valido.
 *Pos: Se establece una conexion a traves del port
 *     y la host_name, entre el socket self y el servidor,
 *     en caso de error se devuelve -1.
 */     
int socket_connect(socket_t *self, const char* host_name, unsigned short port);
/*
 *Pre: Se recibe un socket self valido.
 *Pos: El socket self, acepta la conexion con el 
 *     socket cliente, en caso de error se devuelve -1.
 */
int socket_accept(socket_t *self, socket_t* accepted_socket);
/*
 *Pre: Se recibe un socket self valido.
 *Pos: Se envia el contenido del buffer en bytes,
 *	   si se produjo un error o el socket se cierra se 
 *     devuelve -1, caso contrario se devuelve la cantidad
 *     de bytes enviados.
 */ 
int socket_send(socket_t *self, const void* buffer, size_t length);
/*
 *Pre: Se recibe un socket self valido.
 *Pos: Se reciben en bytes el contenido del buffer,
 *	   si se produce un error o el socket se cierra se 
 *     devuelve -1, caso contrario se devuelve la cantidad
 *     de bytes recibidos.
 */
int socket_receive(socket_t *self, void* buffer, size_t length);
/*
 *Pre: Se recibe un socket self valido.
 *Pos: Se cierran el canal, para poder enviar o recibir 
 *     datos.
 */
void socket_shutdown(socket_t *self);

#endif
