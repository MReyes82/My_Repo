#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Movie.h"
#include "Hash.h"

void imprimirArreglo(Movie **movies);
void liberarArreglo(Movie **movies);

int main(void)
{
    printf("It runs?\n");

    int i, opcion, subopcion;
    bool runs = true;

    HashTable tablaHashIdentificadores;
    HashTable tablaHashNombres;

    Movie **arregloPeliculas = NULL;
    arregloPeliculas = create_movies();

    initHashTable(&tablaHashIdentificadores, SIZE_DATA, getID);
    initHashTable(&tablaHashNombres, SIZE_DATA, calcularLlaveString);

    vaciarArregloEstatico(&tablaHashIdentificadores, arregloPeliculas);
    vaciarArregloEstatico(&tablaHashNombres, arregloPeliculas);

    liberarArreglo(arregloPeliculas);

    while (runs)
    {
        printf("\n----MENU----\n");
        printf("[0] MOSTRAR HASH ID\n");
        printf("[1] MOSTRAR HASH NOMBRE\n");
        printf("[2] BUSCAR PELICULA ID\n");
        printf("[3] BUSCAR PELICULA NOMBRE\n");
        printf("[4] AGREGAR PELICULA\n");
        printf("[5] ELIMINAR PELICULA ID\n");
        printf("[6] TERMINAR PROGRAMA\n");

        printf("Eliga una opcion > ");
        scanf("\n%d",&opcion);

        switch (opcion)
        {
        case 0:
            printf("\n----Mostrando tabla hash 1----\n");
            imprimirTabla(&tablaHashIdentificadores);

            break;

        case 1:
            printf("\n----Mostrando tabla hash 2----\n");
            imprimirTabla(&tablaHashNombres);

            break;
        
        case 2:
            printf("\n----Buscando pelicula por ID---\n");

            printf("Ingrese el ID de la pelicula > ");
            scanf("%d",&i);

            Movie *pelicula = buscarPeliculaID(&tablaHashIdentificadores, i);

            if (pelicula != null)
            {
                printMovie(pelicula);
                printf("\n");
                break;
            }

            printf("Pelicula no encontrada\n");

            break;

        case 3:
            printf("\n----Buscando pelicula por nombre---\n");
            //char* nombre = malloc(50 * sizeof(char));
            char nombre[50];

            printf("Ingrese el nombre de la pelicula > ");
            scanf("\n%[^\n]s",nombre);

            Movie* peliculaNombre = buscarPeliculaNombre(&tablaHashNombres, nombre);

            if (peliculaNombre != null)
            {
                printMovie(peliculaNombre);
                printf("\n");
                //free(nombre);

                break;
            }

            printf("Pelicula no encontrada\n");

            break;

        case 4:
            printf("\n----Agregando pelicula---\n");

            


            break;

        case 5:
            printf("\n----Eliminando pelicula---\n");

            printf("[0] Eliminar por ID\n");
            printf("[1] Eliminar por nombre\n");
            printf("Eliga una opcion > ");
            
            scanf("\n%d", &subopcion);

            if (subopcion == 0)
            {
                printf("Ingrese el ID de la pelicula > ");
                scanf("\n%d",&i);

                eliminarPeliculaID(&tablaHashIdentificadores, i);
                eliminarPeliculaID(&tablaHashNombres, i);

                break;
            }

            if (subopcion == 1)
            {
                //char* nombre = malloc(50 * sizeof(char));
                char nombre[50];

                printf("Ingrese el nombre de la pelicula > ");
                scanf("\n%[^\n]s", nombre);

                eliminarPeliculaNombre(&tablaHashIdentificadores, nombre);
                eliminarPeliculaNombre(&tablaHashNombres, nombre);

                break;
            }

            printf("Opcion no valida\n");

            break;

        case 6:
            runs = false;
            break;

        default:
            break;
        }
    }

    liberarArreglo(arregloPeliculas);
    liberarTabla(&tablaHashIdentificadores);
    liberarTabla(&tablaHashNombres);

    printf("Programa terminado\n");
    
    return 0;
}

void imprimirArreglo(Movie **movies)
{
    Movie *dataTemp = null;
    int i;
    for(i = 0 ; i < SIZE_DATA ; i++)
    {
        dataTemp = getMovie(movies,i);

        if(dataTemp)
        {
            printMovie(movies[i]);
            printf("\n");
        }
    }

    return;
}

void liberarArreglo(Movie **movies)
{
    Movie *dataTemp = null;
    int i;

    for(i = 0 ; i < SIZE_DATA ; i++)
    {
        dataTemp = getMovie(movies,i);

        if(dataTemp)
        {
            free(dataTemp);
            movies[i] = null;
        }
    }

    //free(movies);

    return;
}