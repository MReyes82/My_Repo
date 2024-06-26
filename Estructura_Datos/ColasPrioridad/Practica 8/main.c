#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    int prioridadActual = atoi(argv[1]);

    if (prioridadActual != _MIN_ && prioridadActual != _MAX_)
    {
        return 1;
    }

    int i, opcion; // la prioridad por defecto es para los elementos de mayor cantidad de paginas

    bool corre = true;
    ColaImpresion colaPrincipal = crearColaImpresion(prioridadActual);
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
        printf("\nIngrese una opcion > ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 0:
                printf("\n\n-----Cambiando prioridad------\n\n");

                cambiarPrioridad(&colaPrincipal, &prioridadActual);

                printf("Nueva prioridad: %s\n", prioridadActual == _MAX_ ?  "Mayor" : "Menor");

                break;
            
            case 1:
                printf("\n\n-----Mostrando cola de impresion------\n\n");

                imprimirColaImpresion(&colaPrincipal);

                break;
                
            case 2:
                printf("\n\n-----Agregando archivo------\n\n");

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
                printf("\n\n-----Eliminando archivo------\n\n");
                
                if (colaPrincipal.cantidadColas == 0)
                {
                    break;
                }
                imprimirColaImpresion(&colaPrincipal);
                printf("\nElige el archivo a eliminar > ");
                scanf("%d", &i);

                eliminarArchivoPos(&colaPrincipal, i);

                break;

            case 4:
                printf("\n\n-----Eliminando todos los archivos------\n\n");
                // 
                Archivo* tmp = procesarArchivoPrioridad(&colaPrincipal, prioridadActual);

                if (tmp == null)
                {
                    break;
                }

                i = 1;
                while (tmp != null)
                {
                    printf("Archivo eliminado: ");
                    imprimirDocumento(tmp, i);
                    free(tmp->nombre);
                    free(tmp);
                    i++;
                    tmp = procesarArchivoPrioridad(&colaPrincipal, prioridadActual);
                }

                break;

            case 5:
                printf("\n\n-----Procesando archivo------\n\n");

                printf("Archivo procesado: \n");
                Archivo* archivo = procesarArchivoPrioridad(&colaPrincipal, prioridadActual);

                if (archivo == null) // evitar segfault
                {
                    printf("No hay archivos para procesar.\n");
                    break;
                }

                imprimirDocumento(archivo, 0);
                free(archivo->nombre);
                free(archivo);

                break;

            case 6:
                corre = false;
                break;
            default:
                break;
        }
    }
    vaciarColaImpresion(&colaPrincipal);

    printf("\nADIOS PAPU\n"); // solo para checar que el programa termina sin problemas

    return 0;
}   