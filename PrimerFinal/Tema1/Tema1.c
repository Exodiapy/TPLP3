#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


unsigned long factorial(int n)
{
    unsigned long fact = 1;

    for (int i = 1; i <= n; i++) {
        fact = fact * i;
    }

    return fact;
}

void *Ejecutar(void  *num) {
    int *numero;
	numero=(int *)num;
    printf("Factorial de %d es %lu\n",numero,factorial(numero));
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int *dato;
	int *posicion;
    pthread_t vectorHilos[argc];

    for (int i = 1; i < argc; ++i) {
		
        dato = atoi(argv[i]);

        pthread_create(&vectorHilos[i], NULL, Ejecutar, (void *)dato);
        pthread_join(vectorHilos[i],NULL);
    }

    return 0;
}