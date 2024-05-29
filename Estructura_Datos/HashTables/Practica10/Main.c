#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include <stdbool.h>

/*
! ULTIMA VERSION: REFACTOR TOTAL
TODO: 1 leak pendiente
*/

int main(void) 
{
    int id_counter = SIZE_DATA;

    HashTable* tablaHashIdentificadores = initHashTable(SIZE_DATA);
    HashTable* tablaHashNombres = initHashTable(SIZE_DATA * 4);

    create_movies(tablaHashIdentificadores, tablaHashNombres);

    int opcion;
    int id, year, rating;
    char nombre[NAME_SIZE];

    bool runs = true;

    while (runs) 
    {
        printf("\n\n----MENU----\n");
        printf("[0] MOSTRAR HASH ID\n");
        printf("[1] MOSTRAR HASH NOMBRE\n");
        printf("[2] BUSCAR PELICULA ID\n");
        printf("[3] BUSCAR PELICULA NOMBRE\n");
        printf("[4] AGREGAR PELICULA\n");
        printf("[5] ELIMINAR PELICULA\n");
        printf("[6] TERMINAR PROGRAMA\n");

        printf("\nElija una opcion > ");
        scanf("\n%d", &opcion);

        switch (opcion) 
        {
            case 0:
                printf("\n----Mostrando tabla hash de ID----\n\n");
                imprimirTablaHash(tablaHashIdentificadores);

                break;

            case 1:
                printf("\n----Mostrando tabla hash de nombres----\n\n");
                imprimirTablaHash(tablaHashNombres);

                break;

            case 2:
                printf("\n----Buscando pelicula por ID---\n");
                printf("Ingrese el ID de la pelicula: ");
                scanf("%d", &id);

                Movie* movie = buscarPeliculaPorID(tablaHashIdentificadores, id);

                if (movie == null) 
                {
                    printf("Pelicula no encontrada.\n");

                    break;
                }

                printMovie(movie);
                
                break;

            case 3:
                printf("\n----Buscando pelicula por nombre---\n");
                printf("Ingrese el nombre de la pelicula: ");
                scanf("\n%[^\n]s", nombre);

                bool seEncontro = buscarPeliculasNombre(tablaHashNombres, nombre);

                if (!seEncontro) 
                {
                    printf("Sin resultados.\n");
                }

                break;

            case 4:
                printf("\n----Agregando pelicula---\n");
                printf("Ingrese el nombre de la pelicula: ");
                scanf("\n%[^\n]s", nombre);
                printf("Ingrese el año de la pelicula: ");
                scanf("\n%d", &year);
                printf("Ingrese la calificación de la pelicula: ");
                scanf("\n%d", &rating);

                if (tablaHashNombres->lastIDdeleted == -1 && tablaHashIdentificadores->lastIDdeleted == -1)
                {
                    id = ++id_counter;

                } else {
                    if (tablaHashNombres->lastIDdeleted != -1)
                        id = tablaHashIdentificadores->lastIDdeleted;
                }

                insertarEnTablas(tablaHashIdentificadores, tablaHashNombres, id, nombre, year, rating);

                break;

            case 5:
                printf("\n----Eliminando pelicula---\n\n");
                int subOpcion;

                printf("[0] Eliminar por ID\n");
                printf("[1] Eliminar por nombre\n");
                printf("Eliga una opcion > ");
                
                scanf("\n%d", &subOpcion);

                if (subOpcion == 0) 
                {
                    printf("\nIngrese el ID de la pelicula > ");
                    scanf("\n%d", &id);
                    eliminarPorID(tablaHashIdentificadores, tablaHashNombres, id);

                } 
                else if (subOpcion == 1) 
                {
                    printf("\nIngrese el nombre de la pelicula > ");
                    scanf("\n%[^\n]s", nombre);
                    eliminarPorNombre(tablaHashNombres, tablaHashIdentificadores, nombre);
                }
                break;

            case 6:

                runs = false;
                break;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    }

    liberarTablaHash(tablaHashIdentificadores);
    liberarTablaHash(tablaHashNombres);

    printf("Adios papu\n");

    return 0;
}