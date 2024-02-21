#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    ListaDobEnlace lista;
    lista.inicio = NULL;
    lista.fin = NULL;
    lista.numeroNodos = 0;

    int opcion, valorBuffer, posicionBuffer;

    while (1)
    {
        printf("\n--------MENU------\n");
        printf("[1] Insertar nuevo nodo.\n[2] Mostar lista.\n[3]Terminar programa.\n");
        printf("Inserte eleccion > ");
        scanf("\n%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Valor del nodo > ");
            scanf("\n%d", &valorBuffer);
            printf("Posicion del nodo > ");
            scanf("\n%d", &posicionBuffer);
            
            insertarNodoPosicion(&lista, valorBuffer, posicionBuffer);

            break;

        case 2:
            printf("\nMostrando lista...\n");
            recorrerNodos(&lista);
            break;

        case 3:
            printf("Terminando programa...\n");
            exit(EXIT_SUCCESS);

        default:
            printf("Opcion no valida.\n");
            break;
        }
    }

    return 0;
}