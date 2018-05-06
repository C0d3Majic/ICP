#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h> 

#define FILEKEY "/bin/cat"
#define KEY 1300
#define MAXBUF 10

int main () {
   /* Key to shared memory */
   int key = ftok(FILEKEY, KEY);
   if (key == -1) { 
      fprintf (stderr, "Error con la llave \n");
      return -1; 
   }

   /* Creamos la memoria compartida */
   int id_zone = shmget (key, sizeof(int)*MAXBUF, 0777 | IPC_CREAT);
   if (id_zone == -1) {
      fprintf (stderr, "Error con el id de la memoria compartida \n");
      return -1; 
   }

   printf ("ID de la zona de memoria compartida: %i\n", id_zone);

   int *buffer; /* memoria compartida */
   /* Declaramos la zona de memoria a compartir*/
   buffer = shmat (id_zone, (char *)0, 0);
   if (buffer == NULL) { 
      fprintf (stderr, "Error reservando la zona de memoria a compartir \n");
      return -1; 
   }
 
   printf ("Pointer buffer shared memory: %p\n", buffer);

   /* Escribimos la seccion de memoria compartida */
   int i;
   for (i = 0; i < MAXBUF; i++) 
      printf ("%i\n", buffer[i]);
   return 0;
}