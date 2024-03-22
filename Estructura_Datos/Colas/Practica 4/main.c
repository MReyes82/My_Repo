#include "header.h"
#include <stdlib.h>
#include <stdio.h>

#define null NULL

int main(void)
{
    int i, option, correPrograma, indice;

    correPrograma = 1;

    Cola colaReproduccion;
    inicializarCola(&colaReproduccion);

    while(correPrograma)
    {
        //system("cls"); //WINDOWS
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
            //CAMBIA EL COMPORTAMIENTO DE LA COLA
            //SI NO ERA COLA CIRCULAR, LA HACE CIRCULAR
            //SI ERA COLA CIRCULAR, LA DESHACE
            printf("[0] BUCLE\n");

            if (colaReproduccion.inicio->anterior == colaReproduccion.final 
            &&
            colaReproduccion.final->siguiente == colaReproduccion.inicio)
            {
                colaReproduccion.inicio->anterior = null;
                colaReproduccion.final->siguiente = null;
                printf("\nBUCLE DESACTIVADO\n");
            }

            else
            {
                colaReproduccion.inicio->anterior = colaReproduccion.final;
                colaReproduccion.final->siguiente = colaReproduccion.inicio;
                printf("\nBUCLE ACTIVADO\n");
            }

            //system("pause");

            break;
        case 1:
            printf("\n[1] ANTERIOR\n");

            if (colaReproduccion.actual != NULL)
            {
                colaReproduccion.actual = colaReproduccion.actual->anterior;
                
            }

            //system("pause");

            break;
        case 2:
            printf("\n[2] SIGUIENTE\n");

            if (colaReproduccion.actual != NULL)
            {
                colaReproduccion.actual = colaReproduccion.actual->siguiente;
            }

            //system("pause");

            break;
        case 3:
            printf("\n[3] Agregar cancion\n");

            i = mostrarPlaylist();

            if (i < 0 || i > 15) { break; }

            printf("\nMostrando cola de reproduccion\n");
            mostrarColaReproduccion(&colaReproduccion);
            printf("\nEliga una posicion donde insertar la cancion\n> ");
            scanf("\n%d", &indice);
            //Cancion* temp = crearCancion(playlistOriginal[i].nombre, playlistOriginal[i].autor, playlistOriginal[i].fechaSalida);
            enqueue(&colaReproduccion, &playlistOriginal[i], indice);

            //system("pause");

            break;
        case 4:
            printf("\n[4] Mostrando cola de reproduccion\n");
            mostrarColaReproduccion(&colaReproduccion);

            //system("pause");

            break;
        case 5:
            printf("\n[5] Quitar cancion de la cola.\n");

            printf("\nMostrando cola de reproduccion\n");
            mostrarColaReproduccion(&colaReproduccion);
            printf("\nEliga una posicion para eliminar la cancion\n> ");
            scanf("\n%d", &indice);

            Cancion* out = dequeue(&colaReproduccion, indice);

            printf("\nCancion eliminada: %s\n", out->nombre);
            
            //system("pause");

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
    printf("\n\n\r");
    return 0;
}