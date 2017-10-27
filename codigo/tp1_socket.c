#include "tp1_socket.h"

int socket_create(socket_t *self) {
	self->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (self->socket < 0) {
		return ERROR; 
	} else {
		return self->socket;
	}
}

int socket_destroy(socket_t *self) {
	return close(self->socket);
}

int socket_bind_and_listen(socket_t *self, unsigned short port) {
	int dato = 0;
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	dato = bind(self->socket, (struct sockaddr*) &server, sizeof(server));

	if (dato < 0) {
		return ERROR;
	} 
	listen(self->socket,1);
	return dato;
}

int socket_connect(socket_t *self, const char* host_name, unsigned short port) {
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(host_name);
	int dato = connect(self->socket, (struct sockaddr*) &server, sizeof(server));
	if (dato < 0) {
		return ERROR;
	}
	return dato;
}

int socket_accept(socket_t *self, socket_t* acceptSock) {
	struct sockaddr_in c;
	socklen_t tamClient = (socklen_t)sizeof(c);
	acceptSock->socket = accept(self->socket,(struct sockaddr*)&c,&tamClient);
	if (acceptSock->socket < 0) {
		return ERROR;
	}	
	return EXITO;
}

int socket_send(socket_t *self, const void* buffer, size_t length) {
	int s = 0, bytesEnviados = 0;
	while (length > bytesEnviados) { 
		s = send(self->socket, buffer, length, 0);
		if (s <= 0) { 
			return ERROR;
		} else {
			bytesEnviados += s;
		}
	}
	return s;
}

int socket_receive(socket_t *self, void* buffer, size_t length) {
	int s = 0, bytesRecibidos = 0;
	while (length > bytesRecibidos) {
		s = recv(self->socket,buffer,length,0);
		if (s <= 0) {
			return ERROR;
		} else {
			bytesRecibidos += s;
		}
	}
	return s;
}

void socket_shutdown(socket_t *self) {
	shutdown(self->socket, SHUT_RDWR);
}
