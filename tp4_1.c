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
    struct Nodo* Siguiente;
}Nodo;

Nodo* crearListaVacia(){
    return NULL;
}

void crearTarea(Tarea* T, int contador){
    char descripcion[100];
    printf("\nIngrese una tarea pendiente:");
        fflush(stdin);
        gets(descripcion);
        int DescripLong = strlen(descripcion);
        T->Descripcion = (char *)malloc(sizeof(char) * DescripLong);
        strcpy(T->Descripcion, descripcion);
        T->TareaID = contador;
        T->Duracion = 10 + rand() % 91;
}

Nodo* crearNodo(Nodo* start, Tarea* T){

}
int main() {
    srand(time(NULL));
    char decision;
    int contador = 1000;
    Nodo* start;
    Tarea T;
    start = crearListaVacia();
    do {
        crearTarea(&T,contador);
        printf("\nSi desea ingresar una nueva tarea ingrese [1], caso contrario ingrese cualquier otro numero: ");
        scanf("%d", &decision);
        contador++;
        // printf("Descripcion: %s\n", T.Descripcion);
        // printf("Id: %d\n", T.TareaID);
        // printf("Duracion %d min\n", T.Duracion);
    } while(decision == 1);
    return 0;
}