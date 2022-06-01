#include "cola.h"
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"

ptrNodoCola ptrIzq = NULL;
ptrNodoCola ptrDer = NULL;
int cantIzq=0;
int cantDer=0;
int cantidadIzq;
int cantidadDer;
pthread_mutex_t llaveIzq;
pthread_mutex_t llaveDer;
char valor[7];


void *moverIzquierda(void *mover) { //funcion que utiliza el hilo para mover de izquierda a derecha
    char auto1[7], auto2[7], auto3[7], auto4[7], auto5[7];
    while(1) { //pasan los autos de izquierda 
      pthread_mutex_lock(&llaveIzq);//se bloquea el mutex creado para la cola de la izquierda
      if(cantIzq != 0) { //si todavia no pasaron todos los autos de la izquierda
        strcpy(auto1, retirar(&ptrIzq)); //se saca el primer auto de la cola de la izquierda
        cantIzq--; //un auto menos esperando en la cola de la izquierda
      } else { //ya no hay autos esperando en cola de la izquierda
        pthread_mutex_unlock(&llaveDer); //se desbloquea el mutex definido para la cola de la derecha, para que puedan comenzar a moverse
        break;
      }

      if(cantIzq != 0) { //si todavia no pasaron todos los autos
        strcpy(auto2, retirar(&ptrIzq)); //se saca el segundo auto que estaba esperando en la cola de la izquierda
        if (strcmp(auto2,"vacioo") == 0)
          strcpy(auto2, "======");
        cantIzq--; //un auto menos esperando en la cola de la izquierda
      } else //ya no hay autos esperando en la cola de la izquierda
        strcpy(auto2,"======");

      if(cantIzq != 0) { //si todavia no pasaron todos los autos de la cola de la izquierda
        strcpy(auto3, retirar(&ptrIzq));//se saca el siguiente auto que estaba esperando en la cola de la derecha
        if (strcmp(auto2,"vacioo") == 0)
          strcpy(auto2, "======");
        cantIzq--; //un auto menos esperando en la cola de la izquierda
      } else //ya no hay autos esperando en la cola de la izquierda
        strcpy(auto3,"======");
	
	if(cantIzq != 0) { //si todavia no pasaron todos los autos
        strcpy(auto4, retirar(&ptrIzq)); //se saca el segundo auto que estaba esperando en la cola de la izquierda
        if (strcmp(auto4,"vacioo") == 0)
          strcpy(auto4, "======");
        cantIzq--; //un auto menos esperando en la cola de la izquierda
      } else //ya no hay autos esperando en la cola de la izquierda
        strcpy(auto4,"======");

      if(cantIzq != 0) { //si todavia no pasaron todos los autos de la cola de la izquierda
        strcpy(auto5, retirar(&ptrIzq));//se saca el siguiente auto que estaba esperando en la cola de la derecha
        if (strcmp(auto5,"vacioo") == 0)
          strcpy(auto5, "======");
        cantIzq--; //un auto menos esperando en la cola de la izquierda
      } else //ya no hay autos esperando en la cola de la izquierda
        strcpy(auto5,"======");

      direccionIzquierda(auto1, auto2, auto3, auto4, auto5, ptrIzq, ptrDer, cantidadIzq, cantidadDer); //para efectos de la simulacion
      pthread_mutex_unlock(&llaveDer); //se desbloquea el mutex definido para la cola de la derecha, ya pueden moverse los de la derecha

    }
    pthread_mutex_unlock(&llaveIzq); //se desbloquea el mutex del puente

    return NULL;
}

void *moverDerecha(void *mover) { //funcion que utiliza el hilo para mover de derecha a izquierda
  char auto1[7], auto2[7], auto3[7], auto4[7], auto5[7];
  while(1) { //pasan los autos de derecha
  	pthread_mutex_lock(&llaveDer); //se bloquea el mutex creado para la cola de la derecha
    	if(cantDer != 0) { //si todavia no pasaron todos los autos de la derecha
		strcpy(auto1, retirar(&ptrDer)); //se saca el primer auto de la cola de la derecha 
      		cantDer--; //un auto menos esperando en la cola de la derecha
    	} else { //ya no hay autos esperando en cola de la derecha
      		pthread_mutex_unlock(&llaveIzq); // se desbloquea el mutex definido para la cola de la izquierda, para que puedan comenzar a moverse
      		break;
    	}

    	if(cantDer != 0) { //si todavia no pasaron todos los autos
    		strcpy(auto2, retirar(&ptrDer)); //se saca el segundo auto que estaba esperando en la cola de la cola de la derecha
      		if (strcmp(auto2,"vacioo") == 0) 
     	 		strcpy(auto2, "======");
      		cantDer--; //un auto menos esperando en la cola de la derecha
    	} else //ya no hay autos esperando en la cola de la derecha
      		strcpy(auto2,"======");

    	if(cantDer != 0) { //si todavia no pasaron todos los autos de la cola de la derecha
      		strcpy(auto3, retirar(&ptrDer));//se saca el siguiente auto que estaba esperando en la cola de la derecha
      		if (strcmp(auto2,"vacioo") == 0)
       	 		strcpy(auto2, "======");
      		cantDer--;//un auto menos esperando en la cola de la derecha
    	} else//ya no hay autos esperando en la cola de la derecha
      		strcpy(auto3,"======");
	if(cantDer != 0) { //si todavia no pasaron todos los autos
    		strcpy(auto4, retirar(&ptrDer)); //se saca el segundo auto que estaba esperando en la cola de la cola de la derecha
      		if (strcmp(auto4,"vacioo") == 0) 
     	 		strcpy(auto4, "======");
      		cantDer--; //un auto menos esperando en la cola de la derecha
    	} else //ya no hay autos esperando en la cola de la derecha
      		strcpy(auto4,"======");

    	if(cantDer != 0) { //si todavia no pasaron todos los autos de la cola de la derecha
      		strcpy(auto5, retirar(&ptrDer));//se saca el siguiente auto que estaba esperando en la cola de la derecha
      		if (strcmp(auto5,"vacioo") == 0)
       	 		strcpy(auto5, "======");
      		cantDer--;//un auto menos esperando en la cola de la derecha
    	} else//ya no hay autos esperando en la cola de la derecha
      		strcpy(auto5,"======");

    	direccionDerecha(auto1, auto2, auto3, auto4, auto5, ptrIzq, ptrDer, cantidadIzq, cantidadDer); //para efectos de la simulacion
    	if(ptrIzq == NULL)
        	pthread_mutex_unlock(&llaveDer); //se desbloquea el mutex definido para la cola de la derecha

    	pthread_mutex_unlock(&llaveIzq);//se desbloquea el mutex definido para la cola de la izquierda, ya pueden moverse los de la izquierda
  }
  pthread_mutex_unlock(&llaveDer); //se desbloquea el mutex del puente

  return NULL;
}

void cadena(char cmd[], int contador)
{
    char aux[3];
    char cero[]="0";
    char carro[7]="auto";
    char nombre[7];
    int longitud;
	if(strcmp(cmd,"car")!=0) //si en el comando no se encuentra la palabra car es invalida
		printf(RED"\nIngrese un comando valido!. car nombre izq/der\n"RESET);
	else{ //se ingreso un auto
		fflush(stdin);
    if(contador<10){
      strcat(carro,cero);
      sprintf(aux, "%d", contador); 
      strcat(carro,aux);

      fflush(stdin);
      scanf("%s",cmd); //se pide ingresar otro comando
      if(strcmp(cmd,"izq")!=0) //si no se va a agregar a la izquierda
      {
          if(strcmp(cmd,"der")!=0) //si tampoco se agrega a la derecha, el comando es invalido
              printf(RED"\nIngrese un comando valido!. car nombre izq/der\n"RESET);
          else{ // el comando indica que se debe agregar el auto en la cola de la izquierda
                agregar(&ptrIzq, carro); //se agrega en la cola de la izquierda
                cantIzq++; //aumenta la cantidad de autos esperando a la izquierda
          }
      }else{
            agregar(&ptrDer, carro); //se agrega a la cola de la derecha
              cantDer++; //aumenta la cantidad de autos esperando a la izquierda
      }
    
    }
    else{
      sprintf(aux, "%d", contador); 
      strcat(carro,aux);
      fflush(stdin);
      scanf("%s",cmd); //se pide ingresar otro comando
      if(strcmp(cmd,"izq")!=0) //si no se va a agregar a la izquierda
      {
          if(strcmp(cmd,"der")!=0) //si tampoco se agrega a la derecha, el comando es invalido
              printf(RED"\nIngrese un comando valido!. car nombre izq/der\n"RESET);
          else{ // el comando indica que se debe agregar el auto en la cola de la izquierda
                agregar(&ptrIzq, carro); //se agrega en la cola de la izquierda
                cantIzq++; //aumenta la cantidad de autos esperando a la izquierda
          }
      }else{
            agregar(&ptrDer, carro); //se agrega a la cola de la derecha
              cantDer++; //aumenta la cantidad de autos esperando a la izquierda
      }
    }
		/*scanf("%s",cmd);
        if(strlen(cmd)!=6) //el vehiculo ingresado no tiene 6 caracteres, es un comando invalido
        {
            printf(RED"\nEl nombre del vehiculo debe tener obligatoriamente 6 caracteres\n"RESET);
        }else{ //se ingreso un nombre de auto valido
            if(busquedaNombre(ptrDer,cmd)==0 || busquedaNombre(ptrIzq,cmd)==0){ //si el auto ya existe en la cola de la derecha o en la cola de la izquierda
                printf(RED"\nEl nombre del vehiculo ya existe, ingrese otro nombre\n"RESET);
            }
            else{ //el nombre del auto es valido y aun no existe en ninguna cola
                strcpy(nombre,cmd); //se guarda el comando ingresado en una variable auxiliar, el nombre del auto
                fflush(stdin);
                scanf("%s",cmd); //se pide ingresar otro comando
                if(strcmp(cmd,"izq")!=0) //si no se va a agregar a la izquierda
                {
                    if(strcmp(cmd,"der")!=0) //si tampoco se agrega a la derecha, el comando es invalido
                        printf(RED"\nIngrese un comando valido!. car nombre izq/der\n"RESET);
                    else{ // el comando indica que se debe agregar el auto en la cola de la izquierda
                        agregar(&ptrIzq, nombre); //se agrega en la cola de la izquierda
                       	cantIzq++; //aumenta la cantidad de autos esperando a la izquierda
                    }

                }else{
                        agregar(&ptrDer, nombre); //se agrega a la cola de la derecha
                        cantDer++; //aumenta la cantidad de autos esperando a la izquierda
                }
            }
        }*/
    }
}

int main(int argc, char  *argv[])
{
    pthread_t hilo1, hilo2;
    char s[4] = " \n\t";
    int contador=1;
    char cmd[1024];
	printf(">>");
	scanf("%s",cmd);
	while(1) 
	{
		if(strcmp(cmd,"exit")==0){
			return 0;
		}else if(strcmp(cmd, "start")==0){ //el comando fue start, inicia la simulacion
		 	cantidadIzq=cantIzq; //se actualiza la cantidad de autos en la cola de la izquierda luego del ultimo auto igresado
		 	cantidadDer=cantDer; //se actualiza la cantidad de autos en la cola de la derecha luego del ultimo auto igresado
		 	system("clear");
		 	pthread_mutex_lock(&llaveDer); //se bloquea el mutex creado para el puente
		 	pthread_create(&hilo1, NULL, moverIzquierda, NULL); //se inicia el hilo para mover los autos de izquierda a derecha
		 	pthread_create(&hilo2, NULL, moverDerecha, NULL); //se inicia el hilo para mover los autos de derecha a izquierda
		 	pthread_join(hilo1, NULL); //se espera a que el hilo de los autos de la izquierda termine
		 	pthread_join(hilo2, NULL); //se espera a que el hilo de los autos de la derecha termine
		 	gotoxy(1,8); //posiciona el cursor en x 1, y 8
		 	break; //todos los autos pasaron
		}else if(strcmp(cmd, "status")==0){
		      imprimirStatus(ptrIzq, ptrDer);
    		}else{
			cadena(cmd, contador); //se carga el auto, en la funcion se verifica si es un nombre valido o no
      contador=contador+1;
        }
		fflush(stdin);
		printf(">>");
		scanf("%s",cmd); //se solicita un nuevo comando
	}
    return 0;
}
