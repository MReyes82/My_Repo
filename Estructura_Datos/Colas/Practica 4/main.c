#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    // TODO: CHECK LAST PROMPT ON CHATGPT
    int option, correPrograma;

    correPrograma = 1;

    Queue colaReproduccion = initQueue(0);

    while(correPrograma)
    {
        system("cls"); //WINDOWS
        printf("\n");
        desplegarReproduccion(&colaReproduccion);
        printf("\n");
        printf("\n [0] BUCLE");
        printf("\n [1] ANTERIOR");
        printf("\n [2] SIGUIENTE");
        printf("\n [3] AGREGAR CANCION");
        printf("\n [4] MOSTRAR LISTA DE REPRODUCCION");
        printf("\n [5] QUITAR CANCION");
        printf("\n [6] REINICIAR REPRODUCCION");
        printf("\n [7] TERMINAR PROGRAMA");

        printf("\n Escoge opcion: ");
        scanf("%d",&option);
        switch(option)
        {
        case 0:
                printf("\n");
                //CAMBIA EL COMPORTAMIENTO DE LA COLA
                //SI NO ERA COLA CIRCULAR, LA HACE CIRCULAR
                //SI ERA COLA CIRCULAR, LA DESHACE
                if (colaReproduccion.inicio != NULL && colaReproduccion.final != NULL)
                {
                    colaReproduccion.final->siguiente = 
                    (colaReproduccion.posicionActual == colaReproduccion.numeroElementos - 1) ? colaReproduccion.inicio : NULL;
                }

                system("pause");
                break;
        case 1:
                //ACTUALIZA EL APUNTADOR DE LA ELEMENTO ACTUAL EN REPRODUCCION AL ANTERIOR
                printf("\n");
                if (colaReproduccion.actual != NULL && colaReproduccion.actual->anterior != NULL)
                {
                    colaReproduccion.actual = colaReproduccion.actual->anterior;
                }
                system("pause");

                break;
        case 2:
                //ACTUALIZA EL APUNTADOR DE LA ELEMENTO ACTUAL EN REPRODUCCION AL SIGUIENTE
                printf("\n");
                if (colaReproduccion.actual != NULL && colaReproduccion.actual->siguiente != NULL)
                {
                    colaReproduccion.actual = colaReproduccion.actual->siguiente;
                }
                system("pause");

                break;
        case 3:
                printf("\n");
                //SE MUESTRA UN MENU CON LAS CANCIONES DISPONIBLES
                //SE SELECCIONA LA CANCION
                int seleccion, posicionIns;
                seleccion = printStaticQueue();

                if (seleccion < 0 && seleccion > 14) 
                { 
                    printf("Posicion no valida.\n");
                    break; 
                }
                
                Cancion* nuevaCancion = &listaPredefinina[seleccion];

                //SE MUESTRA LA COLA DE REPRODUCCION
                printf("\nMostrando lista de reproduccion...\n");
                printQueue(&colaReproduccion);

                //SE SELECCIONA EN QUE POSICION DE LA COLA SE AGREGARA
                printf("¿En que posicion desea insertar la cancion?\n> ");
                scanf("\n%d", &posicionIns);

                //SE AGREGA LA CANCION A LA COLA RESPETANDO FIFO DE LA COLA DE REPRODUCCION
                insertarPosicion(&colaReproduccion, nuevaCancion, posicionIns);
                system("pause");

                break;
        case 4:
                //SE MUESTRA LA COLA DE REPRODUCCION RESPETANDO FIFO
                printf("\nMostrando lista de reproduccion...\n");
                printQueue(&colaReproduccion);
                system("pause");

                break;
        case 5:
                //SE MUESTRA UN MENU CON LAS CANCIONES DE LA COLA DE REPRODUCCION RESPETANDO FIFO
                printf("\nMostrando lista de reproduccion...\n");
                printQueue(&colaReproduccion);

                int posicionDel;
                printf("¿Que posicion desea eliminar?\n> ");
                scanf("\n%d", &posicionDel);

                eliminarPosicion(&colaReproduccion, posicionDel);
                //SE SELECCIONA UNA OPCION Y SE ELIMINA, RESPETANDO FIFO
                system("pause");
                break;
        case 6:
                printf("\n");
                //LA POSICION ACTUAL CAMBIA AL INICIO DE LA COLA DE REPRODUCCION
                if (colaReproduccion.inicio != NULL)
                {
                    colaReproduccion.actual = colaReproduccion.inicio;
                }

                system("pause");
                break;
        case 7:
                printf("\n");
                correPrograma = 0;
                break;
        default:
                break;
        }

        // liberamos memoria
        while (!vacia(colaReproduccion))
        {
            eliminarPosicion(&colaReproduccion, 0);
        }
    }

    printf("\n\n");

    return 0;
}
