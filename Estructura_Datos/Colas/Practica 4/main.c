#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define null NULL
#define ACTIVAR 1
#define DESACTIVAR 0

int main(void)
{
    int i, option, correPrograma, indice;
    
    correPrograma = 1;

    Cola colaReproduccion;
    inicializarCola(&colaReproduccion);

    while(correPrograma)
    {
        system("clear"); 
        printf("\n\r");
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

            if (colaReproduccion.estaEnBucle)
            {
                toggleBucle(&colaReproduccion, DESACTIVAR);

            }else{
                toggleBucle(&colaReproduccion, ACTIVAR);
            }

            break;
        case 1:
            printf("\n[1] ANTERIOR\n");

            if (colaReproduccion.actual != NULL)
            {
                colaReproduccion.actual = colaReproduccion.actual->anterior;
                
            }

            break;
        case 2:
            printf("\n[2] SIGUIENTE\n");

            if (colaReproduccion.actual != NULL)
            {
                colaReproduccion.actual = colaReproduccion.actual->siguiente;
            }

            break;
        case 3:
            printf("\n[3] Agregar cancion\n");

            i = mostrarPlaylist();

            if (i < 0 || i > 15) { break; }

            printf("\nMostrando cola de reproduccion\n");
            mostrarColaReproduccion(&colaReproduccion);
            printf("\nEliga una posicion donde insertar la cancion\n> ");
            scanf("\n%d", &indice);

            enqueue(&colaReproduccion, &playlistOriginal[i], indice);

            if (colaReproduccion.estaEnPrimIter)
            {
                /*
                * esta validacion es para tener el bucle desactivado tras la primera iteracion
                * esto ya que nos interesa que el el modo circular no este activado
                * predeterminadamente
                */
                toggleBucle(&colaReproduccion, DESACTIVAR);
                colaReproduccion.estaEnPrimIter = false;
                break;
            }

            if (estaEnModoCircular(&colaReproduccion) && !colaReproduccion.estaEnBucle)
            {
                toggleBucle(&colaReproduccion, DESACTIVAR);
            }

            sleep(0.5);

            break;
        case 4:
            printf("\n[4] Mostrando cola de reproduccion\n");
            mostrarColaReproduccion(&colaReproduccion);

            sleep(4);

            break;
        case 5:
            printf("\n[5] Quitar cancion de la cola.\n");

            printf("\nMostrando cola de reproduccion\n");
            mostrarColaReproduccion(&colaReproduccion);
            printf("\nEliga una posicion para eliminar la cancion\n> ");
            scanf("\n%d", &indice);

            dequeue(&colaReproduccion, indice);

            if (estaEnModoCircular(&colaReproduccion) && !colaReproduccion.estaEnBucle)
            {
                toggleBucle(&colaReproduccion, DESACTIVAR);
            }

            sleep(0.5);

            break;
        case 6:
            printf("\n[6] REINICIAR REPRODUCCION\n");

            if (colaReproduccion.inicio != null)
            {
                colaReproduccion.actual = colaReproduccion.inicio;
            }

            printf("\nReproducción reiniciada.\n");

            //system("pause");

            break;
        case 7:
            printf("\nAdios\n");
            correPrograma = 0;
            break;
        default:
            break;
        }        
    }

    while (colaReproduccion.cantidadElementos > 0)
    {
        dequeue(&colaReproduccion, 0);
    }

    printf("\n\n\r");
    return 0;
}