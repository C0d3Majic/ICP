#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <string.h>
using namespace std;

int main()
{
    int fd;
    char * myfifo = "/tmp/fifopipe";  //Nombre del archivo y ubicacion de escritura en el SO

    /* Creamos la FIFO (named pipe) con permisos 0666*/
    mkfifo(myfifo, 0666);

    /* Abrimos el archivo FIFO como solo escritura*/
    fd = open(myfifo, O_WRONLY);

    /* Creamos un apuntador de caracteres (cadena) */
    char *msg;       

    /* Lo inicializamos con una cadena */       
    msg="Ana Karen"; 

    /* Escribimos esa cadena en el archivo */
    write(fd, msg, strlen(msg)+1);

    /* Cerramos la FIFO */
    close(fd);

    /* Eliminamos la FIFO */
    unlink(myfifo);

    return 0;
}