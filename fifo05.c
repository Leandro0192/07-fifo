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

#define MENSAJE "MENSAJE PARA EL PROCESO B\n"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;
   
   //unlink(FIFO_PATH);
   
   err=mkfifo(FIFO_PATH, 0777);
   
   if(err == -1){
   printf("Error al crear FIFO, ya existe\n");}
   else{
   printf("FIFO creada exitosamente\n");}
   
   fifo_d = open(FIFO_PATH, O_WRONLY);
   write(fifo_d, MENSAJE, sizeof (MENSAJE));
   write(0, "MENSAJE LEIDO POR EL PROCESO B\n", sizeof "MENSAJE LEIDO POR EL PROCESO B\n");
   close(fifo_d);
   
   return 0;
   
   }
   
   
   
