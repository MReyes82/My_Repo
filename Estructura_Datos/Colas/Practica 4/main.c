#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define null NULL
#define NO_LIMIT 0

int main(void)
{
    int i, option, correPrograma, indice;
    bool verif = true, wasFuncCalled = false;

    correPrograma = true;

    Cola colaReproduccion;
    inicializarCola(&colaReproduccion, NO_LIMIT);
    //toggleBucle(&colaReproduccion);

    while(correPrograma)
    {
        //system("clear"); // POSIX
        printf("\n\r");

        if (colaReproduccion.cantidadElementos != 0)
        {
            verif = _estaEnBucle_(&colaReproduccion);
            if (verif) { toggleBucle(&colaReproduccion); }
            wasFuncCalled = true;
        }

        desplegarReproduccion(&colaReproduccion);
        printf("\n\r");
        printf("\n\r [0] BUCLE");
        printf("\n\r [1] ANTERIOR");
        printf("\n\r [2] SIGUIENTE");
        printf("\n\r [3] AGREGAR CANCION");
        printf("\n\r [4] MOSTRAR LISTA DE REPRODUCCION");
        printf("\n\r [5] QUITAR CANCION");
        printf("\n\r [6] REINICIAR REPRODUCCION");
        printf("\n\r [7] TERMINAR PROGRAMA");

        printf("\n\r Escoge opcion: ");
        scanf("%d",&option);
        switch(option)
        {
        case 0:
            printf("[0] BUCLE\n");

            toggleBucle(&colaReproduccion);

            sleep(1);

            break;

        case 1:
            printf("\n[1] ANTERIOR\n");

            if (colaReproduccion.actual != null && colaReproduccion.actual->anterior != null)
            {
                colaReproduccion.actual = colaReproduccion.actual->anterior;
            }

            sleep(1);

            break;
        case 2:
            printf("\n[2] SIGUIENTE\n");

            if (colaReproduccion.actual != null && colaReproduccion.actual->siguiente != null)
            {
                colaReproduccion.actual = colaReproduccion.actual->siguiente;
            }

            sleep(1);

            break;
        case 3:
            printf("\n[3] Agregar cancion\n");

            i = mostrarPlaylist();

            if (i < 0 || i > 15) { break; }

            printf("\nMostrando cola de reproduccion\n");
            mostrarColaReproduccion(&colaReproduccion);
            printf("\nEliga una posicion donde insertar la cancion\n> ");
            scanf("\n%d", &indice);

            //if (colaReproduccion.cantidadElementos > 0)
            //{
            //    verif = _estaEnBucle_(&colaReproduccion);
            //}

            enqueue(&colaReproduccion, &playlistOriginal[i], indice);

            //sleep(2);

            break;
        case 4:
            printf("\n[4] Mostrando cola de reproduccion\n");
            mostrarColaReproduccion(&colaReproduccion);

            sleep(6);

            break;
        case 5:
            printf("\n[5] Quitar cancion de la cola.\n");

            printf("\nMostrando cola de reproduccion\n");
            mostrarColaReproduccion(&colaReproduccion);
            printf("\nEliga una posicion para eliminar la cancion\n> ");
            scanf("\n%d", &indice);

            Cancion* out = dequeue(&colaReproduccion, indice);

            printf("\nCancion eliminada: %s\n", out->nombre);
            
            sleep(1);

            break;
        case 6:
            printf("\n[6] REINICIAR REPRODUCCION\n");

            if (colaReproduccion.inicio != null)
            {
                colaReproduccion.actual = colaReproduccion.inicio;
            }

            printf("\nReproducción reiniciada.\n");

            sleep(1);

            break;

        case 7:
            printf("\nAdios\n");
            correPrograma = false;
            break;

        default:
            break;
        }        
    }

    verif = _estaEnBucle_(&colaReproduccion);
    while (colaReproduccion.cantidadElementos > 0)
    {
        dequeue(&colaReproduccion, 0);
    }

    printf("\n\n\r");
    return 0;
}