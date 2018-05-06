#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <string.h>

#define MAX_BUF 1024
using namespace std;

/* Funcion simple que invierte el orden de una cadena */
char* strrev(char *str){
    int i = strlen(str)-1,j=0;

    char ch;
    while(i>j)
    {
        ch = str[i];
        str[i]= str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;

}

int main()
{
    int fd;
    char *myfifo = "/tmp/fifopipe"; //Nombre del archivo y ubicacion de escritura en el SO
    char buf[MAX_BUF];              //Creamos un buffer (Arreglo de caracteres)

    /* Abrimos el archivo FIFO como solo lectura */
    fd = open(myfifo, O_RDONLY);

    /* Leemos el contenido del archivo FIFO */
    read(fd, buf, MAX_BUF);

    /* Imprimimos el contenido del archivo */
    cout<<"Recibido: "<< buf<<endl;

    /* Usamos la funcion para invertir el orden y imprimimos el resultado */
    cout<<"La cadena invertida es: "<<strrev(buf)<<endl;

    /* Cerramos el archivo */
    close(fd);

    return 0;
}