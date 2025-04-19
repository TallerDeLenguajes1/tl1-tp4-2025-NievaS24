#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea {
    int TareaID;        // Numérico autoincremental comenzando en 1000
    char *Descripcion;  //
    int Duracion;       // entre 10 – 100
} Tarea;
typedef struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *crearListaVacia() {
    return NULL;
}

void crearTarea(Tarea *T, int contador) {
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

Nodo *crearNodo(Tarea *T) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->T = *T;
    nuevo->Siguiente = NULL;
    return nuevo;
}

void insertarNodo(Nodo **start, Nodo *nodo) {
    nodo->Siguiente = *start;
    *start = nodo;
}

void mostrarLista(Nodo *start) {
    int i = 1;
    while (start != NULL) {
        printf("Tarea %d: %s\n", i, start->T.Descripcion);
        start = start->Siguiente;
        i++;
    }
}

void eliminarNodo(Nodo **start, int indice) {
    Nodo *aux = *start;
    if (indice == 1) {
        *start = (*start)->Siguiente;
        free(aux);
    } else {
        Nodo *previo;
        for (int i = 1; i < indice; i++) {
            if (aux != NULL) {
                previo = aux;
                aux = aux->Siguiente;
            }
        }
        if (aux != NULL) {
            previo->Siguiente = aux->Siguiente;
            free(aux);
        } else {
            printf("El nodo seleccionado no existe\n");
        }
    }
}

void moverNodo(Nodo **from, Nodo **to, int indice){
    Nodo *aux = *from;
    if (indice == 1) {
        *from = (*from)->Siguiente;
        aux->Siguiente = *to;
        *to = aux;
    } else {
        Nodo *previo;
        for (int i = 1; i < indice; i++) {
            if (aux != NULL) {
                previo = aux;
                aux = aux->Siguiente;
            }
        }
        if (aux != NULL) {
            previo->Siguiente = aux->Siguiente;
            aux->Siguiente = *to;
            *to = aux;
        } else {
            printf("El nodo seleccionado no existe\n");
        }
    }
}

// char *BuscarNombrePorPalabra(char *palabra, char *start) {
//     char *nombreEncontrado;
//     for (int i = 0; i < 5; i++) {
//         nombreEncontrado = strstr(*(V + i), palabra);
//         if (nombreEncontrado != NULL) return nombreEncontrado;
//     }
//     return nombreEncontrado;
// }

char *buscarTareaID(int num, Nodo *start) {
    if (num < 1000) {
        return NULL;
    }
    while (start != NULL){
        if(start->T.TareaID == num){
            char *TareaBuscada = (char *)malloc((sizeof(char)) * (strlen(start->T.Descripcion)));
            strcpy(TareaBuscada,start->T.Descripcion);
            return TareaBuscada;
        }
        start = start->Siguiente;
    }
    

}

int main() {
    srand(time(NULL));
    char decision;
    int contador = 1000;
    Nodo *startPendiente, *startRealizadas;
    Tarea T;
    // Ingresar nuevas tareas
    startPendiente = crearListaVacia();
    do {
        crearTarea(&T, contador);
        Nodo *nuevo = crearNodo(&T);
        insertarNodo(&startPendiente, nuevo);
        contador++;
        printf("\nPara continuar oprima [1]. Para finalizar oprima [0]\n");
        scanf(" %d", &decision);
    } while (decision == 1);
    printf("Tareas Pendientes\n");
    // Marcar tarea como realizada
    mostrarLista(startPendiente);
    int indice;
    printf("Ingrese [1] si desea marcar una tarea como realizada.\n");
    scanf("%d", &decision);
    startRealizadas = crearListaVacia();
    while (decision == 1) {
        do {
            printf("Ingrese el indice de la tarea que quieres marcar:\n");
            scanf(" %d", &indice);
        } while (indice <= 0);
        //eliminarNodo(&startPendiente, indice);
        moverNodo(&startPendiente,&startRealizadas,indice);
        printf("Tareas Pendientes\n");
        mostrarLista(startPendiente);
        printf("Tareas Realizadas\n");
        mostrarLista(startRealizadas);
        printf("Ingrese [1] si desea marcar una tarea como realizada.\n");
        scanf(" %d", &decision);
    }
    // Buscar por ID o por nombre
    printf("Desea Buscar por Nombre[1] o por ID [2]. Para Salir oprima [0]\n");
    scanf(" %d", &decision);
    while (decision == 1 || decision == 2){
        if (decision == 1){

        } else {
            printf("Ingrese el indice del nombre que quiere ver: \n");
            scanf("%d", &indice);
            char *tareBuscadoPorID = buscarTareaID(indice, startPendiente);
            if (tareBuscadoPorID == NULL) {
                tareBuscadoPorID = buscarTareaID(indice, startRealizadas);
                if (tareBuscadoPorID == NULL){
                    printf("No existe ese indice\n");
                }else {
                    printf("La tarea buscada es: %s y es una tarea Realizada\n", tareBuscadoPorID);
                }
            } else {
                printf("La tarea buscada es: %s y es una tarea Pendiente\n", tareBuscadoPorID);
            }
        }
        printf("Desea Buscar por Nombre[1] o por ID [2]. Para Salir oprima [0]\n");
        scanf(" %d", &decision);
    }
    return 0;
}