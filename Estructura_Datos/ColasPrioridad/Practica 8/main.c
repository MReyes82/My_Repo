#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int main (void)
{
    int i, opcion, prioridadActual = _MAX_; // la prioridad por defecto es para los elementos de mayor cantidad de paginas

    bool corre = true;
    ColaImpresion colaPrincipal = crearColaImpresion(prioridadActual);
    //ColaArchivos* colaPrincipal = crearColaArchivos(0);
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
        printf("[6] TERMINAR PROGRAMA.\n");
        printf("Ingrese una opcion > ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 0:
                break;
            case 1: // caso 1 listo
                printf("\n-----Mostrando cola de impresion------\n");

                imprimirColaImpresion(&colaPrincipal);
                //imprimirColaArchivos(colaPrincipal, prioridadActual);

                break;
                
            case 2: // caso 2 listo
                printf("\n-----Agregando archivo------\n");
                char* nombre = malloc(12 * sizeof(char));
                int paginas;

                printf("Ingrese el nombre del archivo > ");
                scanf("%s", nombre);
                printf("Ingrese el numero de paginas > ");
                scanf("%d", &paginas);
                
                nuevo = crearDocumento(nombre, paginas);
                encolarArchivoPrioridad(&colaPrincipal, nuevo, prioridadActual);

                break;

            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("\n-----Procesando archivo------\n");

                printf("Archivo procesado: \n");
                Archivo* archivo = procesarArchivoPrioridad(&colaPrincipal, prioridadActual);

                if (archivo == null) // evitar segfault
                {
                    printf("No hay archivos para procesar.\n");
                    break;
                }

                imprimirDocumento(archivo, -77);


                break;
            case 6:
                corre = false;
                break;
            default:
                break;
        }
    }
    vaciarColaImpresion(&colaPrincipal);

    i = 0;
    printf("\n%d\n", i); // solo para checar que el programa termina sin problemas

    return 0;
}   