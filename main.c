#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    ListaDobEnlace listaUno, listaDos, listaTres;
    listaUno.inicio = NULL;
    listaUno.fin = NULL;
    listaUno.numeroNodos = 0;

    listaDos.inicio = NULL;
    listaDos.fin = NULL;
    listaDos.numeroNodos = 0;

    listaTres.inicio = NULL;
    listaTres.fin = NULL;
    listaTres.numeroNodos = 0;

    int opcion, inputBuffer, posicionBuffer;
    int listaAInsertar;

    insertarNodoPosicion(&listaTres, 5, 0);
    insertarNodoPosicion(&listaTres, 96, 1);
    insertarNodoPosicion(&listaTres, 17, 2);

    while (1)
    {
        printf("\n---------MENU--------\n");
        printf("[0] Agregar nodo a la lista uno.\n");
        printf("[1] Eliminar nodo de la lista uno.\n");
        printf("[2] Agregar nodo a la lista dos.\n");
        printf("[3] Eliminar nodo de la lista dos.\n");
        printf("[4] Insertar lista a la lista tres.\n");
        printf("[5] Mostrar listas.\n");
        printf("[6] Terminar programa.\n");
        printf("Selecciona opcion > ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 0:
            printf("En que posicion desea agregar el nodo? \n");
            scanf("%d", &posicionBuffer);
            printf("\nInserte el valor del nodo: \n");
            scanf("%d", &inputBuffer);
            insertarNodoPosicion(&listaUno, inputBuffer, posicionBuffer);

            break;

        case 1:
            printf("Que posicion desea eliminar? \n");
            scanf("%d", &posicionBuffer);
            eliminarNodoPosicion(&listaUno, posicionBuffer);

            break;
        
        case 2:
            printf("En que posicion desea agregar el nodo? \n");
            scanf("%d", &posicionBuffer);
            printf("\nInserte el valor del nodo: \n");
            scanf("%d", &inputBuffer);
            insertarNodoPosicion(&listaDos, inputBuffer, posicionBuffer);
            break;

        case 3:
            printf("Que posicion desea eliminar? \n");
            scanf("%d", &posicionBuffer);
            eliminarNodoPosicion(&listaDos, posicionBuffer);
            break;

        case 4:
            printf("Que lista desea insertar en la tercera? \n");
            scanf("%d", &listaAInsertar);

            if (!(listaAInsertar >= 1 && listaAInsertar <= 2))
            {
                printf("ERROR: opcion no valida.\n");
                break;
            }

            printf("A que posicion desea transferir los nodos?\n");
            scanf("%d", &posicionBuffer);

            if (listaAInsertar == 1)
            {
                transferirNodoALista(&listaUno, &listaTres, posicionBuffer);
            }

            if (listaAInsertar == 2)
            {
                transferirNodoALista(&listaDos, &listaTres, posicionBuffer);
            }

            break;
        case 5:
            printf("\nLista 1:\n");
            recorrerNodos(&listaUno);
            printf("\n\nLista 2:\n");
            recorrerNodos(&listaDos);
            printf("\n\nLista 3:\n\n");
            recorrerNodos(&listaTres);
            break;

        case 6:
            printf("\nTerminando programa...\n");
            liberarMemoriaLista(&listaUno);
            liberarMemoriaLista(&listaDos);
            liberarMemoriaLista(&listaTres);
            exit(EXIT_SUCCESS);

        default:
            printf("\nOpcion no valida.\n\n");
            break;
        }
    }

    return 0;
}