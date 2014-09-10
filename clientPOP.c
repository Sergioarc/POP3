#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/*
Funcion que pide el correo al usurio y verifica que este bien escrito
return correo 
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
/*
Funcion que pide la contraseña a su correo al usuario 
return ps
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

void conexion(int puerto){
  struct sockaddr_in servidorAdd;
  struct hostent *servidor;
  int popsocket;
  char recivido[256];

  popsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  
  if(popsocket < 0){
    error("Error al abrir el socket");
  }
  
  servidor = gethostbyname("localhost");
  if(servidor == NULL){
    error("No se encontro el sevidor");
  }
  
  bzero((char *) &servidorAdd, sizeof(servidorAdd));
  servidorAdd.sin_family = AF_INET;
  bcopy((char *)servidor -> h_addr,(char *) &servidorAdd.sin_addr.s_addr,servidor -> h_length);
  servidorAdd.sin_port = htons(puerto);
  
  if(connect(popsocket, (struct sockaddr *)&servidorAdd, sizeof(servidorAdd)) < 0){
    error("Error al iniciar la conexion");
  }
  printf("Conectado al servidor");
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
  int puerto = atoi(argv[1]);
  conexion(puerto);
  
} 
