#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

void gotoxy(int x, int y) {
  printf("\033[%d;%df",y,x);
}

struct nodoCola {
  char dato[7];
  struct nodoCola *ptrSiguiente;
};

typedef struct nodoCola NodoCola;
typedef NodoCola *ptrNodoCola;

void agregar(ptrNodoCola *ptrCabeza, char valor[]);
char *retirar(ptrNodoCola *ptrCabeza);
int estaVacia(ptrNodoCola ptrCabeza);
void imprimirCola(ptrNodoCola ptrActual, int x, int y);
void direccionIzquierda(char auto1[], char auto2[], char auto3[], char auto4[], char auto5[], ptrNodoCola izq, ptrNodoCola der, int cizq, int cder);
void direccionDerecha(char auto1[], char auto2[], char auto3[], char auto4[], char auto5[],  ptrNodoCola izq, ptrNodoCola der, int cizq, int cder);
void limpiarAutos(int x, int y, int cantidad);
int imprimirAuto(ptrNodoCola ptrActual, int x, int y);

void agregar(ptrNodoCola *ptrCabeza, char valor[]) {
  ptrNodoCola ptrNuevo, ptrActual, ptrAnterior;

  ptrNuevo = malloc(sizeof(NodoCola));
  if (ptrNuevo != NULL) {
    strcpy(ptrNuevo->dato, valor);
    //ptrNuevo->dato = valor;
    ptrNuevo->ptrSiguiente = NULL;

    ptrAnterior = NULL;
    ptrActual = *ptrCabeza;

    while(ptrActual != NULL) {
        ptrAnterior = ptrActual;
        ptrActual = ptrActual->ptrSiguiente;
    }
    if(ptrAnterior == NULL) {
        ptrNuevo->ptrSiguiente = *ptrCabeza;
        *ptrCabeza = ptrNuevo;
    } else {
        ptrAnterior->ptrSiguiente = ptrNuevo;
        ptrNuevo->ptrSiguiente = ptrActual;
    }

  } else {
    printf("no se inserto %s No hay memoria disponible.\n", valor);
  }
}

char *retirar(ptrNodoCola *ptrCabeza) {
  char* valor = malloc(sizeof(7));
  ptrNodoCola tempPtr;

  if(estaVacia(*ptrCabeza)) {
    strcpy(valor, "vacioo");
    return valor;
  }
  strcpy(valor, (*ptrCabeza)->dato);
  //valor = (*ptrCabeza)->dato;
  tempPtr = *ptrCabeza;
  *ptrCabeza = (*ptrCabeza)->ptrSiguiente;
  free(tempPtr);

  return valor;
}

int estaVacia(ptrNodoCola ptrCabeza) {
  return ptrCabeza == NULL;
}

int busquedaNombre(ptrNodoCola ptrCabeza,char x[]){
    while(ptrCabeza !=NULL){
        if(strcmp(ptrCabeza->dato,x)==0){
            break;
        }
        ptrCabeza=ptrCabeza->ptrSiguiente;
    }
    if(ptrCabeza==NULL){
        return 1;
    }
    return 0;
}


void direccionIzquierda(char auto1[], char auto2[], char auto3[], char auto4[], char auto5[], ptrNodoCola izq, ptrNodoCola der, int cizq, int cder) {
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=========="RED">>>>>>>>>>"RESET"==================================================\n"
          "=========="RED">>%s>>"RESET"==================================================\n"
          "=========="RED">>>>>>>>>>"RESET"==================================================\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto1);
  if(der != NULL) {
    limpiarAutos(62,7,cder);
    imprimirAuto(der,62,7);
  }
  limpiarAutos(2,7,cizq);
  if(strcmp(auto2,"======") != 0) {
    gotoxy(2,7);printf("%s",auto2);
    gotoxy(2,8);printf("%s",auto3);
    imprimirAuto(izq,2,9);
  }else{
    imprimirAuto(izq,2,7);
  }
  sleep(1);
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=========="GREEN">>>>>>>>>>"RESET"=========="RED">>>>>>>>>>"RESET"==============================\n"
          "=========="GREEN">>%s>>"RESET"=========="RED">>%s>>"RESET"==============================\n"
          "=========="GREEN">>>>>>>>>>"RESET"=========="RED">>>>>>>>>>"RESET"==============================\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto2, auto1);
  limpiarAutos(2,7,cizq);
  if(strcmp(auto3,"======") != 0) {
    gotoxy(2,7);printf("%s",auto3);
    imprimirAuto(izq,2,8);
  }else{
    imprimirAuto(izq,2,7);
  }
  sleep(1);
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=========="BLUE">>>>>>>>>>"RESET"=========="GREEN">>>>>>>>>>"RESET"=========="RED">>>>>>>>>>"RESET"==========\n"
          "=========="BLUE">>%s>>"RESET"=========="GREEN">>%s>>"RESET"=========="RED">>%s>>"RESET"==========\n"
          "=========="BLUE">>>>>>>>>>"RESET"=========="GREEN">>>>>>>>>>"RESET"=========="RED">>>>>>>>>>"RESET"==========\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto3, auto2, auto1);
  limpiarAutos(2,7,cizq);
  imprimirAuto(izq,2,7);
  sleep(1);
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=========="BLUE">>>>>>>>>>"RESET"=========="GREEN">>>>>>>>>>"RESET"=========="RED">>>>>>>>>>"RESET"==========\n"
          "=========="BLUE">>%s>>"RESET"=========="GREEN">>%s>>"RESET"=========="RED">>%s>>"RESET"==========\n"
          "=========="BLUE">>>>>>>>>>"RESET"=========="GREEN">>>>>>>>>>"RESET"=========="RED">>>>>>>>>>"RESET"==========\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto4, auto3, auto2);
  limpiarAutos(2,7,cizq);
  imprimirAuto(izq,2,7);
  sleep(1);
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=========="BLUE">>>>>>>>>>"RESET"=========="GREEN">>>>>>>>>>"RESET"=========="RED">>>>>>>>>>"RESET"==========\n"
          "=========="BLUE">>%s>>"RESET"=========="GREEN">>%s>>"RESET"=========="RED">>%s>>"RESET"==========\n"
          "=========="BLUE">>>>>>>>>>"RESET"=========="GREEN">>>>>>>>>>"RESET"=========="RED">>>>>>>>>>"RESET"==========\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto5, auto4, auto3);
  limpiarAutos(2,7,cizq);
  imprimirAuto(izq,2,7);
  sleep(1);
  if(strcmp(auto4,"======") != 0) {
    gotoxy(1,1);
    printf( "======================================================================\n"
            "=============================="BLUE">>>>>>>>>>"RESET"=========="GREEN">>>>>>>>>>"RESET"==========\n"
            "=============================="BLUE">>%s>>"RESET"=========="GREEN">>%s>>"RESET"==========\n"
            "=============================="BLUE">>>>>>>>>>"RESET"=========="GREEN">>>>>>>>>>"RESET"==========\n"
            "======================================================================\n"
            ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto5, auto4);
    sleep(1);
    if(strcmp(auto5,"======") != 0) {
      gotoxy(1,1);
      printf( "======================================================================\n"
              "=================================================="BLUE">>>>>>>>>>"RESET"==========\n"
              "=================================================="BLUE">>%s>>"RESET"==========\n"
              "=================================================="BLUE">>>>>>>>>>"RESET"==========\n"
              "======================================================================\n"
              ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto5);
      sleep(1);
    }
  }
}

void direccionDerecha(char auto1[], char auto2[], char auto3[], char auto4[], char auto5[], ptrNodoCola izq, ptrNodoCola der, int cizq, int cder) {
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=================================================="GREEN"<<<<<<<<<<"RESET"==========\n"
          "=================================================="GREEN"<<%s<<"RESET"==========\n"
          "=================================================="GREEN"<<<<<<<<<<"RESET"==========\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto1);
  if(izq != NULL) {
    limpiarAutos(2,7,cizq);
    imprimirAuto(izq,2,7);
  }
  limpiarAutos(62,7,cder);
  if(strcmp(auto2,"======") != 0) {
    gotoxy(62,7);printf("%s",auto2);
    gotoxy(62,8);printf("%s",auto3);
    imprimirAuto(der,62,9);
  }else{
    imprimirAuto(der,62,7);
  }
  sleep(1);
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=============================="GREEN"<<<<<<<<<<"RESET"=========="RED"<<<<<<<<<<"RESET"==========\n"
          "=============================="GREEN"<<%s<<"RESET"=========="RED"<<%s<<"RESET"==========\n"
          "=============================="GREEN"<<<<<<<<<<"RESET"=========="RED"<<<<<<<<<<"RESET"==========\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto1, auto2);
  limpiarAutos(62,7,cder);
  if(strcmp(auto3,"======") != 0) {
    gotoxy(62,7);printf("%s",auto3);
    imprimirAuto(der,62,8);
  }else{
    imprimirAuto(der,62,7);
  }

  sleep(1);
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=========="GREEN"<<<<<<<<<<"RESET"=========="RED"<<<<<<<<<<"RESET"=========="BLUE"<<<<<<<<<<"RESET"==========\n"
          "=========="GREEN"<<%s<<"RESET"=========="RED"<<%s<<"RESET"=========="BLUE"<<%s<<"RESET"==========\n"
          "=========="GREEN"<<<<<<<<<<"RESET"=========="RED"<<<<<<<<<<"RESET"=========="BLUE"<<<<<<<<<<"RESET"==========\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto1, auto2, auto3);
  limpiarAutos(62,7,cder);
  imprimirAuto(der,62,7);
  sleep(1);
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=========="GREEN"<<<<<<<<<<"RESET"=========="RED"<<<<<<<<<<"RESET"=========="BLUE"<<<<<<<<<<"RESET"==========\n"
          "=========="GREEN"<<%s<<"RESET"=========="RED"<<%s<<"RESET"=========="BLUE"<<%s<<"RESET"==========\n"
          "=========="GREEN"<<<<<<<<<<"RESET"=========="RED"<<<<<<<<<<"RESET"=========="BLUE"<<<<<<<<<<"RESET"==========\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto2, auto3, auto4);
  limpiarAutos(62,7,cder);
  imprimirAuto(der,62,7);
  sleep(1);
  gotoxy(1,1);
  printf( "======================================================================\n"
          "=========="GREEN"<<<<<<<<<<"RESET"=========="RED"<<<<<<<<<<"RESET"=========="BLUE"<<<<<<<<<<"RESET"==========\n"
          "=========="GREEN"<<%s<<"RESET"=========="RED"<<%s<<"RESET"=========="BLUE"<<%s<<"RESET"==========\n"
          "=========="GREEN"<<<<<<<<<<"RESET"=========="RED"<<<<<<<<<<"RESET"=========="BLUE"<<<<<<<<<<"RESET"==========\n"
          "======================================================================\n"
          ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto3, auto4, auto5);
  limpiarAutos(62,7,cder);
  imprimirAuto(der,62,7);
  sleep(1);
  if(strcmp(auto4,"======") != 0) {
    gotoxy(1,1);
    printf( "======================================================================\n"
            "=========="RED"<<<<<<<<<<"RESET"=========="BLUE"<<<<<<<<<<"RESET"==============================\n"
            "=========="RED"<<%s<<"RESET"=========="BLUE"<<%s<<"RESET"==============================\n"
            "=========="RED"<<<<<<<<<<"RESET"=========="BLUE"<<<<<<<<<<"RESET"==============================\n"
            "======================================================================\n"
            ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto4, auto5);
    sleep(1);
    if(strcmp(auto5,"======") != 0) {
      gotoxy(1,1);
      printf( "======================================================================\n"
              "=========="BLUE"<<<<<<<<<<"RESET"==================================================\n"
              "=========="BLUE"<<%s<<"RESET"==================================================\n"
              "=========="BLUE"<<<<<<<<<<"RESET"==================================================\n"
              "======================================================================\n"
              ""YELLOW">> Cola Der>>                                                  << Cola Izq<<"RESET"\n", auto5);
      sleep(1);
    }
  }
}

void limpiarAutos(int x, int y, int cantidad){
  while(cantidad != 0) {
    gotoxy(x,y++);
    printf("      ");
    cantidad--;
  }
}

int imprimirAuto(ptrNodoCola ptrActual, int x, int y) {
  while (ptrActual != NULL) {
    gotoxy(x,y++);
    printf("%s\n", ptrActual->dato);
    ptrActual = ptrActual->ptrSiguiente;
  }
  return y;
}

void imprimirStatus(ptrNodoCola izq, ptrNodoCola der){
  int pos1, pos2;
  system("clear");
  gotoxy(1,1);
  printf("Lista Izquierda\n");
  gotoxy(20,1);
  printf("Lista Derecha\n");
  pos1= imprimirAuto(der,1,2);
  pos2= imprimirAuto(izq,21,2);
  if (pos1>pos2){
    gotoxy(1,pos1);
  }else{
    gotoxy(1,pos2);
  }
}
