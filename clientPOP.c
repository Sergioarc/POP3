#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


/**
 *Funcion que imprime mensajes de error y despues
 *da un exit(0) para salir del programa
 */

void error(const char *mensaje){
  perror(mensaje);
  exit(0);
}


/**
 *Funcion que hace la conexion
 */

void conexion(int puerto, char *host){
  struct sockaddr_in servidorAdd;
  struct hostent *servidor;
  char user[205] = "USER ";
  char *usuario = (char*)malloc(100*sizeof(char*));
  char pass[205] = "PASS ";
  char *password = (char*)malloc(100*sizeof(char*));
  int opcionUno = 0;
  int opcionDos= 0;
  int popsocket;
  char recivido[256];
  char buffer[256];
  int respSocket;
  printf("Conectando al servidor\n");

  popsocket = socket(AF_INET, SOCK_STREAM, 0);
  
  if(popsocket < 0){
    error("Error al abrir el socket");
  }
  
  servidor = gethostbyname(host);
  if(servidor == NULL){
    error("No se encontro el sevidor");
  }
  
  bzero((char *) &servidorAdd, sizeof(servidorAdd));
  bcopy((char *)servidor -> h_addr,(char *) &servidorAdd.sin_addr.s_addr,servidor -> h_length);
  servidorAdd.sin_family = AF_INET;
  servidorAdd.sin_port = htons(puerto);
  
  do{
    printf("**********BIENVENIDO (Cliente POP3) by Cheko**************\n");
    printf("\nCliente POP3 que es orientado\na la recepcion y recuperacion \nde correos electronicos\n");
    printf("\nOpciones para comenzar\n");
    printf("0. Conectarme\n");
    printf("1. Salir\n");
    printf("Elige la opcion: ");
    scanf("%d",&opcionUno);
    switch(opcionUno){
    case 0:
      if(connect(popsocket, (struct sockaddr *)&servidorAdd, sizeof(servidorAdd)) < 0){
	error("Error al iniciar la conexion");
      }
  
      respSocket = recv(popsocket, recivido, 255,0);
      if(respSocket < 0)
	error("Error al recibir informacion");
      printf("%s\n", recivido);
      
      bzero(recivido,256);
      bzero(buffer, 256);
      printf("Dame el nombre de usuario");
      fgets(usuario,100,stdin);
      strcat(user,usuario);
      strcat(user,"\n");
      printf("Enviando nombre de Usuario\n");
      send(popsocket,user,strlen(user),0);
      respSocket = recv(popsocket, recivido, 255,0);
      if(respSocket < 0)
	error("Error al recibir informacion");
      printf("%s\n", recivido);
      
      bzero(recivido,256);
      bzero(buffer, 256);
      printf("Dame el nombre de usuario");
      fgets(password,100,stdin);
      strcat(pass,password);
      strcat(pass,"\n");
      printf("Enviando password\n");
      send(popsocket,pass,11,0);
      respSocket = recv(popsocket, recivido, 255,0);
      if(respSocket < 0)
	error("Error al recibir informacion");
      printf("%s\n", recivido);
    
      do{
	char numMsj[10];
	printf("\nOpciones de POP3\n");
	printf("\n0.STAT: Numero de correos y tamaño de bytes \n");
	printf("1.LIST: Lista de los mensajes con su tamaña de bytes y su numero");
	printf("2.RETR: Recuperar un mensaje");
	printf("3.DELE: Borra un mensaje ");
	printf("4. QUIT: Terminar sesion");
	printf("Elige Opcion");
	scanf("%d",&opcionDos);
	switch(opcionDos){
	case 0:
	  bzero(recivido,256);
	  bzero(buffer, 256);
	  printf("Enviando STAT");
	  send(popsocket,"STAT\n",6,0);
	  respSocket = recv(popsocket,recivido,255,0);
	  if(respSocket < 0)
	    error("\nError al recibir informacion");
	  printf("\nSTAT: %s\n", recivido);
	  break;
	case 1:
	  bzero(recivido,256);
	  bzero(buffer, 256);
	  printf("Enviando LIST");
	  send(popsocket, "LIST\n",6,0);
	  respSocket = recv(popsocket,recivido,255,0);
	  if(respSocket < 0)
	    error("\nError al recibir informacion");
	  printf("\nLIST: %s\n", recivido);
	  break;
	case 2:
	  bzero(recivido,256);
	  bzero(buffer, 256);
	  char retr[25] = "RETR ";
	  printf("Dame el numero de mensaje a mostrar");
	  fgets(numMsj,10,stdin);
	  strcat(retr,numMsj);
	  printf("Enviando RETR");
	  strcat(retr,"\n");
	  send(popsocket,retr,8,0);
	  respSocket = recv(popsocket,recivido,255,0);
	  if(respSocket < 0)
	    error("\nError al recibir informacion");
	  printf("\nRETR: %s\n", recivido);
	  break;
	case 3:
	  bzero(recivido,256);
	  bzero(buffer, 256);
	  char dele[25] = "DELE ";
	  printf("Dame el numero de mensaje a eliminar");
	  //scanf("%s",&numMsj);
	  fgets(numMsj,10,stdin);
	  strcat(dele,numMsj);
	  printf("Enviando DELE");
	  strcat(dele,"\n");
	  send(popsocket,retr,8,0);
	  respSocket = recv(popsocket,recivido,255,0);
	  if(respSocket < 0)
	    error("\nError al recibir informacion");
	  printf("\nDELE: %s\n", recivido);
	  break;
	case 4:
	  bzero(recivido,256);
	  bzero(buffer, 256);
	  printf("Enviando QUIT");
	  send(popsocket,"QUIT\n",6,0);
	  respSocket = recv(popsocket,recivido,255,0);
	  if(respSocket < 0)
	    error("\nError al recibir informacion");
	  printf("\nQUIT: %s\n", recivido);
	  break;
	default:
	  printf("\nOPCION INCORRECTA\n");
	}
      }while(opcionDos =! 4);
      break;
      
    case 1:
      printf("\nBYE\n");
      close(popsocket);
    }
  }while(opcionUno != 1);
  
  close(popsocket);
}

/**
 *Funcion main
 */
int main(int argc , char *argv[]){
  
  if(argc < 3){
    fprintf(stderr,"usando el puerto %s\n", argv[1]);
    exit(0);
  }
  //printf("Cero %s\n",argv[0]);
  printf("Host %s\n", argv[1]);
  printf("Puerto %s\n", argv[2]);

  int puerto = atoi(argv[2]);
  conexion(puerto, argv[1]);
}
