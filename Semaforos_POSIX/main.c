#include <stdio.h>
#include <pthread.h>
#include <semaphore.h> //Clase de semaforos POSIX
#include <unistd.h>
 
sem_t mutex;

//Creamos la funcion hilo que regresa un apuntador vacio
void* thread(void* arg)
{
    //wait
    sem_wait(&mutex);

    printf("\nEntrando..\n");
 
    //critical section
    sleep(4);
     
    //signal
    printf("\nSaliendo...\n");
    sem_post(&mutex);
}
 
 
int main()
{
    //Inicializamos el semaforo
    sem_init(&mutex, 0, 1);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread,NULL);
    sleep(2);
    pthread_create(&t2,NULL,thread,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    return 0;
}
