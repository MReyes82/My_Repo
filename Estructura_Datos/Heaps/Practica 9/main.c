#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

// TODO: Arreglar indice de eliminarEnPosicion
// & Arreglado, se imprime el array desorneado al eliminar en posicon.

void mostrarHeapBinario(Nodo* nodo, int nivel)
{
    int i;

    if (nodo != null)
    {
        printf(" %s", nodo->documento->nombre); 

        if(nodo->derecha != null)
        {
            printf("\n");

            for (i = 0 ; i < nivel + 1 ; i++)
            {
                if (i == nivel) { printf(" |____R "); }

                else { printf(" |      ");}
            }
            mostrarHeapBinario(nodo->derecha, nivel + 1);
        }

        if(nodo->izquierda != null)
        {
            printf("\n");

            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
            }

            printf("\n");

            for (i = 0 ; i < nivel + 1 ; i++)
            {
                if(i == nivel) { printf(" |____L "); }

                else { printf(" |      "); }
            }

            mostrarHeapBinario(nodo->izquierda, nivel + 1);
        }
    }
}

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    const short int HEAP_SIZE = atoi(argv[1]);

    if (HEAP_SIZE < 1 || HEAP_SIZE > 128) //* 128 es el maximo por temas practicos.
    {
        return 1;
    }

    int opcion;
    TipoDeHeap prioridadActual = HEAP_MINIMO; //* Por default, el heap es del tipo minimo.

    bool corre = true;
    Heap* colaImpresion = crearHeap(HEAP_SIZE, prioridadActual);
    Archivo* nuevo = null;
 
    while (corre)
    {
        printf("\n------MENU------\n");
        printf("[0] CAMBIAR PRIORIDAD.\n");
        printf("[1] MOSTRAR COLA DE IMPRESION.\n");
        printf("[2] AGREGAR ARCHIVO.\n");
        printf("[3] ELIMINAR ARCHIVO.\n");
        printf("[4] ELIMINAR TODOS LOS ARCHIVOS.\n");
        printf("[5] PROCESAR/IMPRIMIR ARCHIVO.\n");
        printf("[6] MOSTRAR ARBOL.\n");
        printf("[7] TERMINAR PROGRAMA.\n");
        printf("\nIngrese una opcion > ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 0:
                printf("\n\n-----Cambiando prioridad------\n\n");

                prioridadActual = (prioridadActual == HEAP_MINIMO) ? HEAP_MAXIMO : HEAP_MINIMO;
                cambiarPrioridad(colaImpresion, prioridadActual);

                break;
            
            case 1:
                printf("\n\n-----Mostrando cola de impresion------\n\n");

                imprimirColaImpresion(colaImpresion, true);

                break;
                
            case 2:
                printf("\n\n-----Agregando archivo------\n\n");
                
                char* nombre = malloc(12 * sizeof(char));
                int paginas;

                printf("Ingrese el nombre del archivo > ");
                scanf("\n%s", nombre);
                printf("Ingrese el numero de paginas > ");
                scanf("\n%d", &paginas);
                
                nuevo = crearDocumento(nombre, paginas);
                insertarNodo(colaImpresion, nuevo);

                break;

            case 3:
                printf("\n\n-----Eliminando archivo------\n\n");
                
                eliminarEnPosicion(colaImpresion);

                break;

            case 4:
                printf("\n\n-----Eliminando todos los archivos------\n\n");
                
                liberarHeap(colaImpresion);

                break;

            case 5:
                printf("\n\n-----Procesando archivo------\n\n");
                
                procesarArchivo(colaImpresion);
                
                break;

            case 6:
                printf("\n\n-----Mostrando arbol------\n\n");
                mostrarHeapBinario(colaImpresion->raiz, 0);
                printf("\n\n\n");

                break;

            case 7:
                corre = false;
                break;

            default:
                break;
        }
    }
    

    if (colaImpresion->cantidadNodos != 0)
    {
        liberarHeap(colaImpresion);
    }
    
    if (colaImpresion != null)
    {
        free(colaImpresion);
    }

    printf("\nADIOS PAPU\n"); // solo para checar que el programa termina sin problemas

    return 0;
}   