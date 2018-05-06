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
 /* Llave para la memoria compartida */
   int key = ftok(FILEKEY, KEY);
   if (key == -1) {
      fprintf (stderr, "Error con la llave \n");
      return -1; 
   }    
   /* Creamos la seccion de memoria compartida*/
   int id_zone = shmget (key, sizeof(int)*MAXBUF, 0777 | IPC_CREAT);
   if (id_zone == -1) {
      fprintf (stderr, "Error con el id de la memoria \n");
      return -1; 
   } 
   printf ("ID de la memoria compartida: %i\n", id_zone);  
 
   int *buffer; /* memoria compartida */
   /* Declaramos la zona a compartir */
   buffer = shmat (id_zone, (char *)0, 0);
   if (buffer == NULL) {
      fprintf (stderr, "Error Reservando la zona de memoria a compartir \n");
      return -1; 
   }
 
   printf ("Apuntador al buffer de memoria compartida: %p\n", buffer); 
   int i;
   for (i = 0; i < MAXBUF; i++) 
      buffer[i] = i;
   /* El proceso se ejecuta hasta recibir un caracter*/
   char c;
   c = getchar();
 
   /* Liberamos la memoria */
   shmdt ((char *)buffer);
   shmctl (id_zone, IPC_RMID, (struct shmid_ds *)NULL);
   return 0;
}
