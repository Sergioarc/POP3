#include <stdio.h>
#include <stlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *mensaje){
  perror(mensaje);
  exit(0);
}


void conexion(){
  int sockt;
  int numPuerto = 110;
  struct sockaddr_in servidorAdd;
  struct hostent *server;
  char buffer[256];
  char* correo;
  char* password;
  if(){}
}
