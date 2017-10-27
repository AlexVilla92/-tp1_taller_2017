#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp1_parser.h" 

int main(int argc, char *argv[]) {
	if (!(strcmp(argv[1],"client"))) {
		return Parser_cliente(argc,argv);
	} else if (!(strcmp(argv[1],"server"))) {
		return Parser_server(argc,argv);
	} else {
		return ERROR;
	}
}
