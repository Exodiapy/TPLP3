#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct
{
    int numeroHilo;
    int fila;
	int columna;
	int filafinal;
	int columnafinal;
	int c1;

} DatosHilo;

int Mat1[10][10];
int Mat2[10][10];
int Mat3[10][10];


void *makeProcess(void* argument) {
    int numerodeProceso = ((DatosHilo *)argument)->numeroHilo;
    int fila = ((DatosHilo *)argument)->fila;
	int columna = ((DatosHilo *)argument)->columna;
	int filafinal = ((DatosHilo *)argument)->filafinal;
	int columnafinal = ((DatosHilo *)argument)->columnafinal;
	int c1 = ((DatosHilo *)argument)->c1;
    printf("Hilo numero %d -> [%d,%d] = ",numerodeProceso,fila,columna);
	
	for (int a = columna; a < columnafinal; a++) {
    
    for (int i=fila; i < filafinal; i++) {
        int suma = 0;
        
        for (int j = 0; j <c1 ; j++) {
            
            suma += Mat1[i][j] * Mat2[j][a];
			printf("%d x %d ",Mat1[i][j],Mat2[j][a]);
			if(j<c1-1){
				printf("+ ");
			}
			
        }
       
        Mat3[i][a] = suma;
		printf(" = %d",suma);
		break;
		}
		break;
	}
	printf("\n");
	
    pthread_exit(NULL);
} 

int main(int argc, char *argv[]) {
	int Fila1 = atoi(argv[1]);
	int Fila2 = atoi(argv[2]);
	int Columna1 = atoi(argv[3]);
	int Columna2 = atoi(argv[4]);

    pthread_t threads[Fila1*Columna2];
	int i,j;
	
	
	printf("Matriz 1\n");
	for(i=0;i<Fila1;i++)
    {
      for (j=0;j<Columna1;j++)
    {
      Mat1[i][j]= rand() % 11;
	  printf("%d ",Mat1[i][j]);

    }
		printf("\n");
    }
	printf("\nMatriz 2\n");
	for(i=0;i<Fila2;i++)
    {
      for (j=0;j<Columna2;j++)
    {
      Mat2[i][j]= rand() % 11;
	  printf("%d ",Mat2[i][j]);

    }
		printf("\n");
    }
	
        DatosHilo *argument= (DatosHilo *)malloc(sizeof(DatosHilo));
	
    i=0;
		for(j=0;j<Fila1;j++){
			for(int k=0;k<Columna2;k++){
				argument->numeroHilo = i+1;
				argument->fila = j; 
				argument->columna = k; 
				argument->filafinal = Fila1; 
				argument->columnafinal = Columna2; 
				argument->c1 = Columna1; 

				pthread_create(&threads[i], NULL, makeProcess, (void *) argument);
				pthread_join(threads[i],NULL);
				i=i+1;
			}
		}
		
	printf("\nMatriz 3\n");
	for(i=0;i<Fila1;i++){
		for(j=0;j<Columna2;j++){
			printf("%d ",Mat3[i][j]);
		}
			printf("\n");
	}

    return 0;
}
