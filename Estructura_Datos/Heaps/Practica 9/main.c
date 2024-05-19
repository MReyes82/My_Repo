#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

// TODO: Arreglar indice de eliminarEnPosicion
// TODO: Actualmente, toma el indice del arreglo en vez del arbol.

void test(Heap* colaImpresion) // * Funcion de prueba para no escribir tanto
{
    insertarNodo(colaImpresion, crearDocumento("Archivo1", 1));
    insertarNodo(colaImpresion, crearDocumento("Archivo2", 2));
    insertarNodo(colaImpresion, crearDocumento("Archivo3", 3));
    insertarNodo(colaImpresion, crearDocumento("Archivo11", 1));
    insertarNodo(colaImpresion, crearDocumento("Archivo5", 5));
    insertarNodo(colaImpresion, crearDocumento("Archivo33", 3));
    insertarNodo(colaImpresion, crearDocumento("Archivo22", 2));
    
    printf("Insertados.\n");

    return;
} 

int main (void)//(int argc, char* argv[])
{
    /*
    if (argc != 2)
    {
        return 1;
    }

    TipoDeHeap prioridadActual = atoi(argv[1]);

    if (prioridadActual != HEAP_MINIMO && prioridadActual != HEAP_MINIMO)
    {
        return 1;
    }
    */

    TipoDeHeap prioridadActual = HEAP_MINIMO;
    //int i; 
    int opcion;

    bool corre = true;
    Heap* colaImpresion = crearHeap(25, prioridadActual);
    Archivo* nuevo = null;

    test(colaImpresion);
 
    while (corre)
    {
        printf("\n------MENU------\n");
        printf("[0] CAMBIAR PRIORIDAD.\n");
        printf("[1] MOSTRAR COLA DE IMPRESION.\n");
        printf("[2] AGREGAR ARCHIVO.\n");
        printf("[3] ELIMINAR ARCHIVO.\n");
        printf("[4] ELIMINAR TODOS LOS ARCHIVOS.\n");
        printf("[5] PROCESAR/IMPRIMIR ARCHIVO.\n");
        printf("[6] TERMINAR PROGRAMA.\n");
        printf("\nIngrese una opcion > ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 0:
                printf("\n\n-----Cambiando prioridad------\n\n");

                prioridadActual = (prioridadActual == HEAP_MINIMO) ? HEAP_MAXIMO : HEAP_MINIMO;
                cambiarPrioridad(colaImpresion, prioridadActual);

                //printf("Nueva prioridad: %s\n", prioridadActual == HEAP_MAXIMO ?  "Mayor" : "Menor");

                break;
            
            case 1:
                printf("\n\n-----Mostrando cola de impresion------\n\n");

                imprimirColaImpresion(colaImpresion);

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
                corre = false;
                break;
            default:
                break;
        }
    }
    
    liberarHeap(colaImpresion);
    //free(colaImpresion->nodos);

    printf("\nADIOS PAPU\n"); // solo para checar que el programa termina sin problemas

    return 0;
}   