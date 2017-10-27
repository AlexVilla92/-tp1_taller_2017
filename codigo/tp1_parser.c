#include "tp1_parser.h"

//Firmas de metodos privados
static int Parser_definoOperacion(socket_t *sockCl, char op[], FILE *input);

static int Parser_operacionInsert(socket_t *socketClient, FILE *input);

static int Parser_operacionDelete(socket_t *socketClient, FILE *input);

static int Parser_operacionSpace(socket_t *socketClient, FILE *input);

static int Parser_operacionNewLine(socket_t *socketClient, FILE *input);

static int Parser_operacionPrint(socket_t *socketClient, FILE *input);

static int Parser_ejecutarOperacion(socket_t *clientSock, int op, Rope *rope);

static int Parser_ejecutarInsertar(socket_t *clientSocket, Rope *unRope);

static int Parser_ejecutarDelete(socket_t *clientSocket, Rope *unRope);

static int Parser_ejecutarSpace(socket_t *clientSocket, Rope *unRope);

static int Parser_ejecutarNewLine(socket_t *clientSocket, Rope *unRope);

static int Parser_ejecutarPrint(socket_t *clientSocket, Rope *unRope);

//Implementacion de metodos
int Parser_cliente(int argc, char *argv[]) {
	FILE *input;
	if (argv[4] == NULL) {
		input = stdin;	
	} else {
		input = fopen(argv[4], "r");
	}
    if (!input) {
    	return ERROR;
    } else {
    	int codigo;
    	socket_t socketClient;
    	codigo = socket_create(&socketClient);
    	codigo = socket_connect(&socketClient,argv[2],atoi(argv[3]));
    	char operacion[MAX_OPE];
    	while ((fscanf(input,"%s",operacion)) == 1) {
    		codigo = Parser_definoOperacion(&socketClient,operacion,input);
    	}
    	if (input != stdin) {
    		fclose(input);
    	}
    	socket_shutdown(&socketClient);
    	codigo = socket_destroy(&socketClient);
    	codigo = EXITO;
    	return codigo;
    }
}

static int Parser_definoOperacion(socket_t *sockCl, char op[], FILE *input) {
	if (!strcmp(op,"insert")) {
		return Parser_operacionInsert(sockCl,input);
	} else if (!strcmp(op,"delete")) {
		return Parser_operacionDelete(sockCl,input);
	} else if (!strcmp(op,"space")) {
		return Parser_operacionSpace(sockCl,input);
	} else if (!strcmp(op,"newline")) {
		return Parser_operacionNewLine(sockCl,input);
	} else if (!strcmp(op,"print")) {
		return Parser_operacionPrint(sockCl,input);
	} else {
		return ERROR;
	}
}

static int Parser_operacionInsert(socket_t *socketClient, FILE *input) {
	int posicion, codigo, opcode = 1;
	char texto[MAX_PAL];
	codigo = fscanf(input, "%d", &posicion);
	codigo = fscanf(input, "%s", texto);

	int ntOpcode = htonl(opcode);
	codigo = socket_send(socketClient,&ntOpcode,sizeof(int));

	int ntPosicion = htonl(posicion);
	codigo = socket_send(socketClient,&ntPosicion,sizeof(int));

	short int longitud = strlen(texto); 
	int tam = strlen(texto);
	short int ntLongitud = htons(longitud);
	codigo = socket_send(socketClient,&ntLongitud,sizeof(short int));
	
	for (int i = 0; i < tam; i++) {
		codigo = socket_send(socketClient,&texto[i],sizeof(char));
	}
	return codigo;
}

static int Parser_operacionDelete(socket_t *socketClient, FILE *input) {
	int codigo, posicionInicial, posicionFinal, opcode = 2;
	codigo = fscanf(input, "%d", &posicionInicial);
	codigo = fscanf(input, "%d", &posicionFinal);
	
	int ntOpcode = htonl(opcode);
	codigo = socket_send(socketClient,&ntOpcode,sizeof(int));

	int ntPosInicial = htonl(posicionInicial);
	codigo = socket_send(socketClient,&ntPosInicial,sizeof(int));

	int ntPosFinal = htonl(posicionFinal);
	codigo = socket_send(socketClient,&ntPosFinal,sizeof(int));
	return codigo;
}

static int Parser_operacionSpace(socket_t *socketClient, FILE *input) {
	int codigo, posicion, opcode = 3;
	codigo = fscanf(input, "%d", &posicion);
	int ntOpcode = htonl(opcode);
	int ntPosicion = htonl(posicion);
	codigo = socket_send(socketClient,&ntOpcode,sizeof(int));
	codigo = socket_send(socketClient,&ntPosicion,sizeof(int));
	return codigo;
}

static int Parser_operacionNewLine(socket_t *socketClient, FILE *input) {
	int codigo, posicion, opcode = 4;
	codigo = fscanf(input, "%d", &posicion);
	int ntOpcode = htonl(opcode);
	int ntPosicion = htonl(posicion);
	codigo = socket_send(socketClient,&ntOpcode,sizeof(int));
	codigo = socket_send(socketClient,&ntPosicion,sizeof(int));
	return codigo;
}

static int Parser_operacionPrint(socket_t *socketClient, FILE *input) {
	int longitud, codigo, opcode = 5;
	int ntOpcode = htonl(opcode);
	codigo = socket_send(socketClient,&ntOpcode,sizeof(int));
	codigo = socket_receive(socketClient,&longitud,sizeof(int));
	int tam = ntohl(longitud);
	char *palabra = (char*)malloc(sizeof(char)*(tam+1));
	palabra[tam] = '\0';
	for (int i = 0; i < tam; i++) {
		codigo = socket_receive(socketClient,&palabra[i],sizeof(char));
	}
	printf("%s", palabra);
	free(palabra);
	return codigo;
}

int Parser_server(int argc, char *argv[]) {
	int codigo;
	codigo = (argc == 3) ? 0:ERROR;
	if (codigo < 0) {
		return codigo;
	} else {
		int opcode;
		socket_t socketServer, clientSocket;
		Rope *unRope = Rope_crearRope();
		codigo = socket_create(&socketServer);
		codigo = socket_bind_and_listen(&socketServer,atoi(argv[2]));
		codigo = socket_accept(&socketServer,&clientSocket);
		while (socket_receive(&clientSocket,&opcode,sizeof(int)) == 4) {
			int ntOpcode = ntohl(opcode);
			codigo = Parser_ejecutarOperacion(&clientSocket,ntOpcode,unRope);
		}
		socket_shutdown(&socketServer);
		socket_shutdown(&clientSocket);
		codigo = socket_destroy(&socketServer);
		codigo = socket_destroy(&clientSocket);
		Rope_destruirRope(unRope);
		if (codigo >= 0) {
			codigo = EXITO;
		}
		return codigo;
	}
}

static int Parser_ejecutarOperacion(socket_t *clientSock, int op, Rope *rope) {
	if (op == 1) {
		return Parser_ejecutarInsertar(clientSock,rope);
	} else if (op == 2) {
		return Parser_ejecutarDelete(clientSock,rope);
	} else if (op == 3) {
		return Parser_ejecutarSpace(clientSock,rope);
	} else if (op == 4) {
		return Parser_ejecutarNewLine(clientSock,rope);
	} else if (op == 5) {
		return Parser_ejecutarPrint(clientSock,rope);
	} else {
		return ERROR;
	}
}

static int Parser_ejecutarInsertar(socket_t *clientSocket, Rope *unRope) {
	int posicion, codigo, tam;
	short int longitud;
	codigo = socket_receive(clientSocket,&posicion,sizeof(int)); 
	codigo = socket_receive(clientSocket,&longitud,sizeof(short int));
	int ntPosicion = ntohl(posicion);
	short int ntLongitud = ntohs(longitud);
	tam = (int)ntLongitud;
	char *palabra = (char*)malloc(sizeof(char)*(tam+1));
	palabra[tam] = '\0';
	for (int i = 0; i < tam; i++) {
		codigo = socket_receive(clientSocket,&palabra[i],sizeof(char));
	}
	Rope_insertar(unRope,ntPosicion,palabra);
	free(palabra);
	return codigo;
}

static int Parser_ejecutarDelete(socket_t *clientSocket, Rope *unRope) {
	int posIni, posFin, codigo;
	codigo = socket_receive(clientSocket,&posIni,sizeof(int)); 
	codigo = socket_receive(clientSocket,&posFin,sizeof(int));
	int ntPosIn = ntohl(posIni);
	int ntPosFin = ntohl(posFin);
	Rope_delete(unRope,ntPosIn,ntPosFin);
	return codigo;	
}

static int Parser_ejecutarSpace(socket_t *clientSocket, Rope *unRope) {
	int posicion, codigo;
	codigo = socket_receive(clientSocket,&posicion,sizeof(int)); 
	int ntPosicion = ntohl(posicion);
	Rope_insertar(unRope,ntPosicion," ");
	return codigo;	
}

static int Parser_ejecutarNewLine(socket_t *clientSocket, Rope *unRope) {
	int posicion, codigo;
	codigo = socket_receive(clientSocket,&posicion,sizeof(int)); 
	int ntPosicion = ntohl(posicion);
	Rope_insertar(unRope,ntPosicion,"\n");
	return codigo;
}

static int Parser_ejecutarPrint(socket_t *clientSocket, Rope *unRope) {
	char *palabra = Rope_obtenerPalabra(unRope);
	int codigo, tam = strlen(palabra);
	int ntTam = htonl(tam);
	codigo = socket_send(clientSocket,&ntTam,sizeof(int));
	char *texto = (char*)malloc(sizeof(char)*(tam+1));
	texto[tam] = '\0';
	strncpy(texto,palabra,tam);
	for (int i = 0; i < tam; i++) {
		codigo = socket_send(clientSocket,&texto[i],sizeof(char));
	}
	free(palabra);
	free(texto);
	return codigo;
}
