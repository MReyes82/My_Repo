#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int main (void)
{
    int i, opcion, prioridadActual = _MAX_;

    bool corre = true;
    ColaImpresion colaPrincipal = crearColaImpresion(prioridadActual);

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
        printf("Ingrese una opcion > ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 0:
                break;
            case 1:
                printf("\n-----Mostrando cola de impresion------\n");

                imprimirColaImpresion(&colaPrincipal);

                break;
                
            case 2:
                printf("\n-----Agregando archivo------\n");
                char nombre[32];
                int paginas;

                printf("Ingrese el nombre del archivo > ");
                scanf("%s", nombre);
                printf("Ingrese el numero de paginas > ");
                scanf("%d", &paginas);
                
                Archivo* doc = crearDocumento(nombre, paginas);

                encolarArchivoPrioridad(&colaPrincipal, doc, prioridadActual);
                /*
                colaPrincipal.inicio = crearColaArchivos();
                encolarArchivo(colaPrincipal.inicio, doc);
                */

                break;

            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                corre = false;
                break;
            default:
                break;
        }
    }
    
    i = 0;
    printf("%d\n", i);
    
    vaciarColaImpresion(&colaPrincipal);

    return 0;
}   