/*
 * Ejercicio 5 del TP FIFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h> 


#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;
   
   err=mkfifo(FIFO_PATH, 0777);
   if(err == -1){
   printf("Error al crear FIFO, ya existe\n");}
   else{
   printf("FIFO creada exitosamente\n");}
   
   fifo_d = open(FIFO_PATH, O_RDONLY);
   leido = read(fifo_d, buff, sizeof (buff));
   write(STDOUT_FILENO, buff, leido);
   close(fifo_d);
   
   return 0;
   
   }
