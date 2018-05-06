#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;

// La estructura que representa la cola de mensajes
struct MsgQueue
{
    long messageType;

    // Atributos de la escritura 
    int someNumber;
    char buff[100];	

};

// Bandera de la cola de mensajes
const int MSG_Q_KEY_FLAG = 0664;

// Canal de transmicion
const int MSG_Q_CHANNEL = 26;

int main()
{
    key_t key = -1;
    int msqid = -1;
    MsgQueue msg;

    // usamos un archivo y llave aleatorio para crear la cola y posteriormente vincular al cliente con esta llave
    key = ftok("/bin/ls", 'K');

    // Si la llave de la cola no se genero correctamente
    if(key < 0)
    {
        cerr<<"ftok errorn";
        exit(1);
    }	

    // Genera la cola en memoria y obtenemos su id
    msqid = msgget(key, MSG_Q_KEY_FLAG | IPC_CREAT);

    // Si la cola no se genero correctamente
    if(msqid < 0)
    {
        cerr<<"msgget errorn";
        exit(1);
    }

    // Mensaje de inicializacion de la cola
    cerr<<"\n El servidor esta en linea \n"
        <<"\n Esperando a que alguien conecte a esta cola con id #"<<msqid<<" y "
        <<"llave "<<key<<endl<<endl;
                
    // Recibimos 10 mensajes del cliente
    for(int x = 0; x < 10; ++x)
    {
        //Recibimos los mensajes que coincidan con el id de esta cola y canal
        if(msgrcv(msqid, &msg, sizeof(msg) - sizeof(long), MSG_Q_CHANNEL, 0) < 0)
        {
            cerr<<"msgrcv error\n";
            exit(1);
        }
        
        // Imprimimos el mensaje recibido del cliente
        cerr<< "Algun numero = "<<msg.someNumber<<" buff = "<<msg.buff<<endl;
    }

    // Al final liberamos la cola de mensajes
    if(msgctl(msqid, IPC_RMID, NULL) < 0)
    {
        cerr<<"msgctl error\n";
        exit(1);
    }
    
    cerr<<"\n El servidor esta offline \n";

    return 0;
}