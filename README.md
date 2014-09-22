POP3
====

Repositorio que contiene el repositorio para hacer el protocolo POP3

Hasta el momento solo se ha hecho la la conexion hacia el servidor de gmail mediante pop.gmail.com en el puerto 995
pero al momento de establecer la conexion se cierra inesperadamente sin recibir datos del servidor.

Se implementó el loggeo y se hizo una prueba con STAT de POP3.


Ejemplo de la salida:

miguel@miguel:~/POP3$ gcc -o client clientPOP.c 
miguel@miguel:~/POP3$ ./client localhost 110
Host localhost
Puerto 110
Conectando al servidor
+OK Hello there.

Enviando nombre de Usuario
+OK Password required.

Enviando password
+OK logged in.

Enviando STAT
STAT: +OK 2 1036
