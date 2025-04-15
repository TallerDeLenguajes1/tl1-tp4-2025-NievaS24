#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea{
    int TareaID;    //Numérico autoincremental comenzando en 1000
    char *Descripcion;  //
    int Duracion;   // entre 10 – 100
}Tarea;
typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

Nodo *crearListaVacia(){
    return NULL;
}

void crearTarea(Tarea *T, int contador){
    char descripcion[100];
    printf("\nIngrese una tarea pendiente: ");
        fflush(stdin);
        gets(descripcion);
        int DescripLong = strlen(descripcion);
        T->Descripcion = (char *)malloc(sizeof(char) * DescripLong);
        strcpy(T->Descripcion, descripcion);
        T->TareaID = contador;
        T->Duracion = 10 + rand() % 91;
}

Nodo *crearNodo(Tarea *T){
    Nodo *nuevo = (Nodo *) malloc(sizeof(Nodo));
    nuevo->T = *T;
    nuevo->Siguiente = NULL;
    return nuevo;
}

void insertarNodo(Nodo **start, Nodo *nodo){
    nodo->Siguiente = *start;
    *start = nodo;
}

void mostrarLista(Nodo *start){
    while(start){
        printf("Tarea: %s\n",start->T.Descripcion);
        start = start->Siguiente;
    }
}

int main() {
    srand(time(NULL));
    char decision;
    int contador = 1000;
    Nodo *startPendiente, *startRealizadas;
    Tarea T;
    startPendiente = crearListaVacia();
    do {
        crearTarea(&T,contador);
        Nodo *nuevo = crearNodo(&T);
        insertarNodo(&startPendiente, nuevo);
        contador++;
        printf("\nPara continuar oprima [1]. Para finalizar oprima [0]\n");
        scanf("%d", &decision);
    } while(decision == 1);
    mostrarLista(startPendiente);
    printf("Ingrese [1] si desea marcar una tarea como realizada.\n");
    scanf("%d", &decision);
    while (decision == 1) {
        printf("Ingrese el indice de la tarea que quieres marcar:\n");
        mostrarLista(startPendiente);
        printf("Ingrese [1] si desea marcar una tarea como realizada.\n");
        scanf("%d", &decision);
    }
    return 0;
}