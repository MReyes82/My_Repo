#include "header.h"
#include <stdio.h>
#include <stdlib.h>
//#define NOLIMIT 0

int main (void)
{
    
    int opcion, runs = 1, lenght, inputBuffer, posicion, i;
    printf("Tamaño de la cola (0 es sin limite)> ");
    scanf("\n%d", &lenght);

    if (lenght < 0 ) { return 1; }

    Queue mainQueue = initQueue(lenght);
    
    while (runs)
    {
        printf("\n----MENU---\n");
        printf("[0] Mostrar cola.\n");
        printf("[1] Agregar elementos.\n");
        printf("[2] Eliminar elemento.\n");
        printf("[3] Agregar elementos en posicion.\n");
        printf("[4] Terminar programa.\n");
        printf("Eliga una opcion > ");
        scanf("\n%d", &opcion);

        if (opcion == 4)
        {
            printf("\nHazta luego tilin.\n");
            runs = 0;
            break;

        }
    
        switch (opcion)
        {
        case 0:
            printf("\nMOSTRANDO COLA..\n");
            printQueue(&mainQueue);
            break;
        
        case 1: 
            printf("\nIngrese el valor: ");
            scanf("\n%d", &inputBuffer);
            enqueue(&mainQueue, inputBuffer);
            break;

        case 2:
            printf("\nEliminando...\n");
            Elemento *datoEliminando = dequeue(&mainQueue);

            printf("Dato eliminado: %d\n", datoEliminando->dato);
            free(datoEliminando);
            
            break;

        case 3:
            printf("\nInserte la posicion: ");
            scanf("\n%d", &posicion);
            printf("Ingrese el dato: ");
            scanf("\n%d", &inputBuffer);

            insertarPosicion(&mainQueue, inputBuffer, posicion);

            break;

        default:
            break;
        }
    }
    
    lenght = mainQueue.numeroElementos;
    for (i = 0 ; i < lenght ; i++)
    {
        Elemento *datoEliminado = dequeue(&mainQueue);
        free(datoEliminado);
    }
    
    return 0;
}