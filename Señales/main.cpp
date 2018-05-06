#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Definimos una funcion que termine el programa atrapando la señal que se genera al precionar Ctrl-c 
void signal_callback_handler(int signum)
{
   printf("Atrapamos la señal %d\n",signum);
   printf("Fin del proceso \n");
   // Terminamos el programa
   exit(signum);
}

int main()
{
   // Registramos la señal y el controlador de esta que es la funcion previamente definida
   signal(SIGINT, signal_callback_handler);

   while(1)
   {
      printf("Proceso activo ... \n");
      sleep(1);
   }
   return EXIT_SUCCESS;
}
