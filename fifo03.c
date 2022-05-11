/*
 * Ejercicio 4 del TP FIFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h> 

#define MENSAJE "HOLA PROCESO HIJO"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;

   unlink(FIFO_PATH);    //si la FIFO existe la borro                   

   // FIFO puede ser leida, escrita y ejecutada por: 
   err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
   if(err == -1) {
      write(STDOUT_FILENO, "\nError al crear FIFO, la FIFO ya existe", sizeof("\nError al crear FIFO, la FIFO ya existe"));
   }else {
      write(STDOUT_FILENO, "\nFIFO creado correctamente\n", sizeof("\nFIFO creado correctamente\n"));
   }


   switch (fork()){  //Se crea proceso Hijo
      
      case -1:      
         write(STDOUT_FILENO, "\nError al crear hijo", sizeof("\nError al crear hijo"));
         return -1;
      break;

      case 0: //Proceso Hijo

         write(STDOUT_FILENO, "\nEntrando proceso HIJO", sizeof("\nEntrando proceso HIJO"));

         sleep(5);
         
         fifo_d=open(FIFO_PATH, O_RDONLY); //Abre FIFO en modo lectura
         printf("HIJO: FIFO ABIERTO CORRECTAMENTE\n");
         leido= read(fifo_d, buff, sizeof buff);//Lee el contenido y lo guarda en buff
         write(STDOUT_FILENO, "HIJO: LEE... ", sizeof ("HIJO: LEE... "));
         write(STDOUT_FILENO, buff, leido-1);//Imprime en pantalla el contenido de buff
         close(fifo_d); //Cierra FIFO


         write(STDOUT_FILENO, "\nSaliendo proceso HIJO\n", sizeof("\nSaliendo proceso HIJO\n"));
         exit(0);
      break;

      default: //Proceso Padre
         write(STDOUT_FILENO, "\nEntrando proceso PADRE", sizeof("\nEntrando proceso PADRE"));

         fifo_d = open(FIFO_PATH, O_WRONLY, 0); //FIFO abierta en modo escritura
         if(fifo_d == -1){
            write(STDOUT_FILENO, "\nPADRE: Error al abrir FIFO ", sizeof("\nPADRE: Error al abrir FIFO "));
            return -1;
         }else {
            write(STDOUT_FILENO, "\nPADRE: FIFO abierto correctamente", sizeof("\nPADRE: FIFO abierto correctamente"));
         }

         // Se escribe en el FIFO
         err = write(fifo_d, MENSAJE, sizeof(MENSAJE)); //Se escribe MENSAJE en FIFO
         if(err == -1) {
            write(STDOUT_FILENO, "\nPADRE: Error al escribir en FIFO", sizeof("\nPADRE: Error al escribir en FIFO"));
         } else {
            write(STDOUT_FILENO, "\nPADRE: Escritos MENSAJE en FIFO\n", sizeof("\nPADRE: Escritos MENSAJE en FIFO"));
         }

         close(fifo_d); //Cierro FIFO

         wait(NULL);
         write(STDOUT_FILENO, "\nSaliendo proceso PADRE\n", sizeof("\nSaliendo proceso PADRE\n"));

      break;   
   }
   
   //Eliminación FIFO
   //if (unlink(FIFO_PATH) < 0) {
    //   printf("\nNo se puede borrar FIFO.\n");  }         

   exit(0);

}
