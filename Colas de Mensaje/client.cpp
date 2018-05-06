#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;

// La estructura de la cola igual que en el servidor
struct MsgQueue
{
    long messageType;

    int someNumber;
    char buff[100];	

};

// Bandera de la cola
const int MSG_Q_KEY_FLAG = 0664;

// Canal de transmision de la cola
const int MSG_Q_CHANNEL = 26;

int main()
{
    
    key_t key = -1;
    int msqid = -1;
    MsgQueue msg;
        
    // llave y archivo aleatorio que es identico al creado en el server
    key = ftok("/bin/ls", 'K');

    // Si la llave de la cola no se genero correctamente
    if(key < 0)
    {
        cerr<<"ftok error\n";
        exit(1);
    }	

    // conectamos con la cola del servidor y obtenemos su id
    msqid = msgget(key, MSG_Q_KEY_FLAG);	

    // Si la cola se ubico correctamente
    if(msqid < 0)
    {
        cerr<<"msgget error\n";
        exit(1);	
    }	

    // Mostramos mensaje de conexion exitosa al server (Cola de mensajes)
    cerr<<"\n Conexion establecida con la cola de mensajes con id #"<<msqid<<" y "
        <<"llave "<<key
        <<"\n Enviando mensajes....";
                
    // Enviamos 10 mensajes al servidor
    for(int x = 0; x < 10; ++x)
    {
        msg.messageType = MSG_Q_CHANNEL;
        
        // creamos el mensaje a enviar en la estructura
        msg.someNumber = x;
        strncpy(msg.buff, "Mensaje del cliente", sizeof(msg.buff));
        
        // Enviamos los mensajes a la cola 
        if(msgsnd(msqid, &msg, sizeof(msg) - sizeof(long), 0) < 0)
        {
            cerr<<"msgsnd error \n";
            exit(1);
        }
    }
    
    cerr<<"\n Envio completo \n";

    return 0;
}