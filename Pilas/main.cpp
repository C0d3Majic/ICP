#include <iostream>
using namespace std;

#include <stdio.h>
#include <unistd.h>

int main()
{

    int status, pid, pipefds[2];
    char instring[20];

    //  Creamos la pipe y regresamos la descipcion (inicio, fin) de la pipa
    //  Esto con el objetivo de que los dos procesos conozcan la pipa con la que se comunicaran
    
    status = pipe(pipefds); //El estatus de creacion correcta es 0
    if (status == -1)
    {
        perror("Error");
        exit(1);
    }

    /*  Creamos el proceso hijo y validamos que tenga un id de proceso valido */
        pid = fork();
    if (pid == -1)           
    {
        perror("Error");
        exit(2);
    }else if (pid == 0) /* Proceso hijo : Envia mensaje al padre*/
    {
        /* Cerramos la seccion que no se usara de la pipa */
        /* Ya que este proceso solo se encarga de escribir*/
        close(pipefds[0]);

        /* Enviamos 10 caracteres al fin pipa*/
        cout << "Enviando el mensaje a la pipa: " << endl;
        write(pipefds[1], "Ana Karen!", 10);  
        close(pipefds[1]); //Cerramos la pipa
        exit(0);
    }
        else        /* Padre : recibe mensaje del hijo */
    {
        /* Cerramos el segmento de la pila que no se usa*/
        /* Ya que este proceso solo se encarga de leer */
        close(pipefds[1]);

        /* Leemos de la pipa */
                read(pipefds[0], instring, 10);
        cout << "Recibi el mensaje: " << instring << endl;

        close(pipefds[0]);
        exit(0);
    }
}