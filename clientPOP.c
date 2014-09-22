#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


/**
 *Funcion que pide el correo al usurio y verifica que este bien escrito
 *return correo 
*/
char *correo(){
 
  char *cadena = (char*)malloc(100*sizeof(char*));
  int i=0;
  char *token = NULL;
  
do{
 
  printf("Inserte su correo\n");
  fgets(cadena,100,stdin);
  token = strtok(cadena,"@");
  token = strtok(NULL,"@");
 
 if(token==NULL)                            //Falta el @
    printf("correo no valido \n");

   }while(token==NULL);
 
    return cadena;
}

/**
 *Funcion que pide la contraseña a su correo al usuario 
 *return ps
*/

char *contra(){
  char *ps = (char*)malloc(50*(sizeof(char*)));
  printf("Inserte su contraseña\n");
  fgets(ps,50,stdin);
  return ps;

}


/**
 *Funcion que imprime mensajes de error y despues
 *da un exit(0) para salir del programa
 */

void error(const char *mensaje){
  perror(mensaje);
  exit(0);
}


/**
 *FUncion que hace la conexion
 */

void conexion(int puerto, char *host){
  struct sockaddr_in servidorAdd;
  struct hostent *servidor;
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
  
  if(connect(popsocket, (struct sockaddr *)&servidorAdd, sizeof(servidorAdd)) < 0){
    error("Error al iniciar la conexion");
  }

  respSocket = recv(popsocket, recivido, 255,0);
  if(respSocket < 0)
    error("Error al recibir informacion");
  printf("%s\n", recivido);

  bzero(recivido,256);
  bzero(buffer, 256);
  printf("Enviando nombre de Usuario\n");
  send(popsocket,"USER user2\n",11,0);
  respSocket = recv(popsocket, recivido, 255,0);
  if(respSocket < 0)
    error("Error al recibir informacion");
  printf("%s\n", recivido);

  bzero(recivido,256);
  bzero(buffer, 256);
  printf("Enviando password\n");
  send(popsocket,"PASS user2\n",11,0);
  respSocket = recv(popsocket, recivido, 255,0);
  if(respSocket < 0)
    error("Error al recibir informacion");
  printf("%s\n", recivido);

  bzero(recivido,256);
  bzero(buffer, 256);
  printf("Enviando STAT");
  send(popsocket,"STAT\n",6,0);
  respSocket = recv(popsocket,recivido,255,0);
    if(respSocket < 0)
    error("\nError al recibir informacion");
  printf("\nSTAT: %s\n", recivido);
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