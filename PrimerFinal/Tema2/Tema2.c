#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 20

int vectorBusqueda[MAX];
sem_t semaforo;

typedef struct
{
    int numeroHilo;
    int cantidadVectores;
    int dato;

} Hilo;


void *ejecutar(void* Informacion) {

    int numHilo = ((Hilo *)Informacion)->numeroHilo;
    int valor = ((Hilo *)Informacion)->dato;
    int cantVec = ((Hilo *)Informacion)->cantidadVectores;
    int sem_status;

    sem_getvalue(&semaforo,&sem_status);
	
    for (int i = numHilo * cantVec; i < (numHilo + 1) * cantVec; ++i) {

        if( sem_status == 1){
            if(vectorBusqueda[i] == valor){
                printf("En el Hilo %d se encontro el valor %d\n",numHilo+1,valor);
				printf("El numero %d se encuentra en la posicion %d del Vector\n",valor,i);
                sem_post(&semaforo);
                pthread_exit(NULL);

            }
        }else{
            pthread_exit(NULL);
        }

    }


    printf("En el Hilo %d NO se encontro el valor %d\n",numHilo+1,valor);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    sem_init(&semaforo, 0, 1);
	system("clear");
	printf("\t\t Vector\n");
	
	for(int j=0;j<40;j++){
		printf("_");	
	}
	printf("\n");
	printf("|");


    for (int i = 0; i < 20; ++i) {
        vectorBusqueda[i] = rand() % 10;
        printf("%d|",vectorBusqueda[i]);
    }
    printf("\n");
	
	for(int j=0;j<40;j++){
		printf("¯");	
	}
	
	printf("\n");
	
    int numberToFind = atoi(argv[1]);
    int numberThreads = atoi(argv[2]);


    Hilo *Informacion = (Hilo *)malloc(sizeof(Hilo));

    pthread_t threads[numberThreads];


    for (int i = 0; i < numberThreads; ++i) {
        Informacion->numeroHilo = i;
        Informacion->dato = numberToFind;
        Informacion->cantidadVectores = numberThreads;

        pthread_create(&threads[i], NULL, ejecutar,(void *) Informacion);
        pthread_join(threads[i],NULL);
    }

    sem_destroy(&semaforo);
    return 0;
}